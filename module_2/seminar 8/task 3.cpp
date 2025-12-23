#include <iostream>
#include <string>
#include <vector>

class Reportable {
public:
    virtual void printShortReport() const = 0;
protected:
    virtual  ~Reportable() = default;
};

class Employee : Reportable{
protected:
    std::string name;
    int id;
public:
    Employee(std::string name, int id) : name(name), id(id) {}

    virtual ~Employee() = default;

    virtual double calculatePay() const = 0;
    virtual std::string getRole() const = 0;

    virtual void printInfo() const {
        std::cout << "Name: " << name << "\n" << "ID: " << id;
    }
    virtual bool isManager() const {
        return false;
    }
    void printShortReport() const override {
        std::cout << "Report: " << name << " \nID: " << id
                  << "\nRole: " << getRole() << "\n\n";
    }
};

class SalariedEmployee : public Employee {
protected:
    double monthlySalary;

public:
    SalariedEmployee(const std::string& name, int id, double salary) : Employee(name, id), monthlySalary(salary) {}

    double calculatePay() const override {
        return monthlySalary;
    }

    std::string getRole() const override {
        return "Employee month";
    }

    void printInfo() const override {
        Employee::printInfo();
        std::cout << "\nMonthly Salary: " << monthlySalary
                  << "\nPay: " << calculatePay() << "\n\n";
    }
};

class HourlyEmployee final : public Employee {
protected:
    double hourlyRate;
    double hoursWorked;

public:
    HourlyEmployee(const std::string& name, int id, double rate, double hours) : Employee(name, id), hourlyRate(rate), hoursWorked(hours) {}

    double calculatePay() const override {
        return hourlyRate * hoursWorked;
    }

    std::string getRole() const override {
        return "Employee hours";
    }

    void printInfo() const override {
        Employee::printInfo();
        std::cout << "\nHourly Rate: " << hourlyRate
                  << "\nHours Worked: " << hoursWorked
                  << "\nPay: " << calculatePay() << "\n";
    }
};

class Manager final : public SalariedEmployee {
protected:
    double bonus;

public:
    Manager(const std::string& name, int id, double salary, double managerBonus) : SalariedEmployee(name, id, salary), bonus(managerBonus) {}

    double calculatePay() const override {
        return monthlySalary + bonus;
    }

    std::string getRole() const override {
        return "Manager";
    }

    void printInfo() const override {
        SalariedEmployee::printInfo();
        std::cout << "ID: " << id << "\nName: " << name
                  << "\nRole: " << getRole()
                  << "\nBase Salary: " << monthlySalary
                  << "\nBonus: " << bonus
                  << "\nTotal Pay: " << calculatePay() << '\n';
    }

    bool isManager() const override {
        return true;
    }
};

class Company {
private:
    std::vector<Employee*> employees;

public:
    ~Company() {
        for (auto emp : employees) {
            delete emp;
        }
    }

    void addEmployee(Employee* e) {
        employees.push_back(e);
    }

    void printAllEmployees() const {
        std::cout << "ALL EMPLOYEES\n";
        for (const auto emp : employees) {
            emp->printInfo();
        }
    }

    void printAllShortReports() const {
        std::cout << "SHORT REPORTS\n";
        for (const auto emp : employees) {
            emp->printShortReport();
        }
    }

    double calculateTotalPayroll() const {
        double total = 0.0;
        for (const auto emp : employees) {
            total += emp->calculatePay();
        }
        return total;
    }

    int countManagers() const {
        int managerCount = 0;
        for (const auto emp : employees) {
            if (emp->isManager()) {
                managerCount++;
            }
        }
        return managerCount;
    }
};

int main() {
    Company company;

    company.addEmployee(new SalariedEmployee("Egor",1,5000));
    company.addEmployee(new SalariedEmployee("Andrew",2,6000));
    company.addEmployee(new HourlyEmployee("Sam",3,500,100));
    company.addEmployee(new HourlyEmployee("Bane",4,300,150));
    company.addEmployee(new Manager("Jane",5,15000,50));
    company.addEmployee(new Manager("Peter",6,20000,100));
    company.printAllEmployees();
    std::cout << '\n';
    company.printAllShortReports();
    std::cout << '\n';
    std::cout << company.calculateTotalPayroll() << '\n' << company.countManagers();
    return 0;
}
