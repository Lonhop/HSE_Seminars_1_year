#include<iostream>
#include<string>
#include<vector>

enum class Event{
    Login = 1,
    Logout = 2,
    MessageSent = 4,
    FileUploaded = 8,
    ErrorOccurred = 16,
    PaymentReceived = 32,
    UserRegistered = 64
};

struct User {
    std::string name;
    Event event;
};


int main() {
    std::vector<User> users = {
        {"Leon",Event::PaymentReceived},
        {"Mike", Event::MessageSent},
        {"Winston",Event::UserRegistered},
        {"Puppey"}
    };
    for (auto user : users) {
        std::cout << user.name << ": ";
        switch (user.event) {
            case Event::Login:
                std::cout << "You are already Login\n";
                break;
            case Event::Logout:
                std::cout << "You are already Logout\n";
                break;
            case Event::MessageSent:
                std::cout << "You are already sent a message\n";
                break;
            case Event::FileUploaded:
                std::cout << "You are already upload file\n";
                break;
            case Event::ErrorOccurred:
                std::cout << "Error occurred\n";
                break;
            case Event::PaymentReceived:
                std::cout << "You are already receive payment\n";
                break;
            case Event::UserRegistered:
                std::cout << "You are already registered\n";
                break;
            default:
                std::cout << "No such command\n";

        }
    }

    return 0;
}