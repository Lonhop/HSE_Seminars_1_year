#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

enum class Statuses{
    None = 1,
    Created = 2,
    Paid = 4,
    Processing = 8,
    Shipped = 16,
    Delivered = 32,
    Cancelled = 64
};

Statuses operator|(Statuses per_1, Statuses per_2) {
    return (Statuses)((int) (per_1) | (int) (per_2));
}

Statuses operator&(Statuses per_1, Statuses per_2) {
    return (Statuses)((int) (per_1) & (int) (per_2));
}

Statuses operator~(Statuses per_1) {
    return (Statuses)(~(int) (per_1));
}


struct Order {
    int id;
    std::string name;
    Statuses ord;
};

std::vector<Order> filter(std::vector<Order>& orders, Statuses const status) {
    std::vector<Order> answer;
    for (auto order : orders) {
        if ((order.ord & status) == status)
        answer.push_back(order);
    }
    return answer;
}

void ChangeByIndex(std::vector<Order>& orders, int index, Statuses replacement) {
    if (index < 0 || index >= orders.size()) {
        std::cout << "Wrong Index";
    }
    else {
        orders[index].ord = replacement;
    }
}

void printStatus(const std::vector<Order>& orders) {
    for (auto order : orders) {
        std::cout << order.id << ' ' << order.name << ":\t";
        switch (order.ord) {
            case Statuses::Created :
                std::cout << "Created\t";
            case Statuses::Delivered:
                std::cout << "Delivered\t";
            case Statuses::Cancelled :
                std::cout << "Cancelled\t";
            case Statuses::Paid :
                std::cout << "Paid\t";
            case Statuses::Processing :
                std::cout << "Processing\t";
            case Statuses::Shipped:
                std::cout << "Shipped\t";
            default:
                std::cout << "None\t";

        }
        std::cout << '\n';
    }
}


int main() {
    std::vector<Order> orders {
        {2,"Egor",Statuses::Created},
        {4,"Alex",Statuses::Processing},
        {3,"Lena",Statuses::Created},
        {1,"Andrew",Statuses::None},};
    printStatus(orders);
    std::cout << '\n';
    std::vector<Order> filter_order = filter(orders, Statuses::Created);
    printStatus(filter_order);
    std::cout << '\n';
    ChangeByIndex(orders,1, Statuses::Paid);
    ChangeByIndex(orders,2, Statuses::Shipped);
    printStatus(orders);
    return 0;
}