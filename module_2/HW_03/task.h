#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>

using UnixTS = unsigned int;

const unsigned short TRANSACTION_COL_N = 6;
const unsigned short ACCOUNT_COL_N = 3;

struct Transaction {
    std::string id;
    UnixTS date;
    std::string type;
    std::string from;
    std::string to;
    double amount;
    bool operator<(const Transaction& other) const;
};

struct Account {
    Account();
    Account(const std::string& id, const std::string& name, UnixTS validity_dt = UINT_MAX);
    void addTransaction(const Transaction& transaction);
    double getBalance(UnixTS = UINT_MAX) const;
    void printInfo() const;
    size_t getTransactionsCount() const;

    std::string id;
    std::string name;
    std::set<Transaction> transactions;
    UnixTS validity_dt;
};

void Account::printInfo() const
{
    std::cout << "--------------------------------\n"
              << "id: " << id << '\n'
              << "name: " << name << '\n'
              << "validity datetime: " << validity_dt << '\n'
              << "--------------------------------\n";
}

size_t Account::getTransactionsCount() const
{
    return transactions.size();
}

Account::Account()
{
    id = "00000000-0000-0000-0000-000000000000";
    name = "Noname";
    validity_dt = 0;
}

Account::Account(const std::string& id,
                 const std::string& name,
                 UnixTS validity_dt)
{
    this->id = id;
    this->name = name;
    this->validity_dt = validity_dt;
}

bool Transaction::operator<(const Transaction& other) const
{
    if (date != other.date) {
        return date < other.date;
    }

    if (type == other.type) {
        return id < other.id;
    }

    if (type == "deposit") return true;
    if (type == "withdraw" && other.type == "transfer") return true;

    return false;
}

void Account::addTransaction(const Transaction& transaction)
{
    transactions.insert(transaction);
}

double Account::getBalance(UnixTS timestamp) const
{
    double balance = 0.0;

    for (const auto& trans : transactions) {
        if (trans.date <= timestamp) {
            if (trans.type == "deposit") {
                if (trans.to == id) {
                    balance += trans.amount;
                }
            } else if (trans.type == "withdraw") {
                if (trans.from == id) {
                    balance -= trans.amount;
                }
            } else if (trans.type == "transfer") {
                if (trans.from == id) {
                    balance -= trans.amount;
                }
                if (trans.to == id) {
                    balance += trans.amount;
                }
            }
        }
    }

    return balance;
}

using AccountContainer = std::unordered_map<std::string, Account>;
using TransactionContainer = std::set<Transaction>;

TransactionContainer readTransactions(std::ifstream& fileStream)
{
    TransactionContainer transactions;
    std::string line;

    std::getline(fileStream, line);
    int trans_count = std::stoi(line);

    std::getline(fileStream, line);

    for (int i = 0; i < trans_count; ++i) {
        if (!std::getline(fileStream, line)) break;

        std::stringstream ss(line);
        std::string field;
        Transaction t;

        std::getline(ss, field, ',');
        t.id = field;

        std::getline(ss, field, ',');
        t.date = std::stoul(field);

        std::getline(ss, field, ',');
        t.type = field;

        std::getline(ss, field, ',');
        t.from = (field == "None") ? "" : field;

        std::getline(ss, field, ',');
        t.to = (field == "None") ? "" : field;

        std::getline(ss, field, ',');
        t.amount = std::stod(field);

        transactions.insert(t);
    }

    return transactions;
}
AccountContainer readAccounts(std::ifstream& fileStream)
{
    AccountContainer accounts;
    std::string line;

    std::getline(fileStream, line);
    int acc_count = std::stoi(line);

    std::getline(fileStream, line);

    for (int i = 0; i < acc_count; ++i) {
        if (!std::getline(fileStream, line)) break;

        std::stringstream ss(line);
        std::string id, name, valid_str;

        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, valid_str, ',');

        UnixTS valid = UINT_MAX;
        if (valid_str != "None") {
            valid = std::stoul(valid_str);
        }

        accounts[id] = Account(id, name, valid);
    }

    return accounts;
}

void fillAccounts(AccountContainer& accounts, const TransactionContainer& transactions)
{
    for (const auto& trans : transactions) {
        if (trans.type == "deposit" && !trans.to.empty()) {
            auto it = accounts.find(trans.to);
            if (it != accounts.end()) {
                it->second.addTransaction(trans);
            }
        } else if (trans.type == "withdraw" && !trans.from.empty()) {
            auto it = accounts.find(trans.from);
            if (it != accounts.end()) {
                it->second.addTransaction(trans);
            }
        } else if (trans.type == "transfer") {
            if (!trans.from.empty()) {
                auto it = accounts.find(trans.from);
                if (it != accounts.end()) {
                    it->second.addTransaction(trans);
                }
            }
            if (!trans.to.empty()) {
                auto it = accounts.find(trans.to);
                if (it != accounts.end()) {
                    it->second.addTransaction(trans);
                }
            }
        }
    }
}

#endif