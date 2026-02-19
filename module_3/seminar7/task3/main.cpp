#include <iostream>
#include <optional>
#include <string>

struct Email {
    std::string address;
};

struct Profile {
    std::optional<Email> email;
};

struct User {
    std::optional<Profile> profile;
};

std::optional<std::string> get_user_email(const User& u) {
    return u.profile
        .and_then([](const Profile& p) { return p.email; })
        .transform([](const Email& e) { return e.address; });
}


int main() {
    // Create a user with complete data
    User user1{
        .profile = Profile{
            .email = Email{"john@example.com"}
        }
    };

    // User with profile but no email
    User user2{
        .profile = Profile{
            .email = std::nullopt
        }
    };

    // User with no profile
    User user3{
        .profile = std::nullopt
    };

    // Test the function
    auto email1 = get_user_email(user1);
    auto email2 = get_user_email(user2);
    auto email3 = get_user_email(user3);

    std::cout << "User1 email: " << email1.value_or("No email") << std::endl;
    std::cout << "User2 email: " << email2.value_or("No email") << std::endl;
    std::cout << "User3 email: " << email3.value_or("No email") << std::endl;

    return 0;
}