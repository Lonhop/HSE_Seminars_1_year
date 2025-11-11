#include<iostream>
#include<string>
#include<vector>

enum class Permission{
    READ = 1,
    WRITE = 2,
    Execute = 4,
    Delete = 8
};

Permission operator|(Permission per_1, Permission per_2) {
    return (Permission)((int) (per_1) | (int) (per_2));
}

Permission operator&(Permission per_1, Permission per_2) {
    return (Permission)((int) (per_1) & (int) (per_2));
}

Permission operator~(Permission per_1) {
    return (Permission)(~(int) (per_1));
}

bool is_allowed(Permission users, Permission allowed) {
    return (users & allowed) == allowed;
}

struct User {
    std::string name;
    Permission permission;
};

int main() {
    std::vector<User> users = {
        {"Admin",Permission::READ | Permission::Delete | Permission::WRITE},
        {"Unsigned", Permission::READ},
        {"Moderator", Permission::Execute}
    };
    for (const auto& user : users) {
        std::cout << "USER" << ' ' << user.name << " Permission:\n";
        std::cout << "READ: " << is_allowed(user.permission, Permission::READ) << '\n';
        std::cout << "WRITE: " << is_allowed(user.permission, Permission::WRITE) << '\n';
        std::cout << "DELETE: " << is_allowed(user.permission, Permission::Delete) << '\n';
        std::cout << "EXECTUTE: " << is_allowed(user.permission, Permission::Execute) << '\n';
        std::cout << '\n';
    }
    return 0;
}