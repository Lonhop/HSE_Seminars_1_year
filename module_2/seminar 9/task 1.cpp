#include<iostream>
#include<string>
#include <utility>
#include <vector>

class Notification {
protected:
    std::string recipient;
    std::string message;
public:
    Notification(std::string res, std::string mess) : recipient(std::move(res)), message(std::move(mess)) {}
    virtual void send() const = 0;
    virtual std::string type() const = 0;
    virtual ~Notification() = default;
};

class EmailNotification : public Notification {
private:
    std::string subject;
public:
    EmailNotification(std::string res, std::string mess,std::string sub) : Notification(std::move(res),std::move(mess)), subject(std::move(sub)) {}
    void send() const override {
        std::cout << "Sending Email to <" << recipient << ">\nsubject: <" << subject <<">\nText: <" << message << ">\n";
    }
    std::string type() const override{
        return subject;
    }
};

class SmsNotification : public Notification {
public:
    SmsNotification(std::string res, std::string mess) : Notification(std::move(res),std::move(mess)) {}
    void send() const override {
        std::cout << "Sending SMS to <" << recipient << ">\nText: <" << message << ">\n";
    }
    std::string type() const override {
        return "SMS";
    }
};

class PushNotification : public Notification {
private:
    std::string title;
public:
    PushNotification(std::string res, std::string mess,std::string tit) : Notification(std::move(res), std::move(mess)), title(std::move(tit)) {}
    void send() const override {
        std::cout << "Sending PUSH to <" << recipient << ">,\nTitle: <" <<title << ">\nBody: <" << message << ">\n";
    }
    std::string type() const override {
        return title;
    }
};

void sendAll(const std::vector<Notification*>& list) {
    for (const auto c : list) {
        c->send();
        std::cout << '\n';
    }
}

int main() {
    std::vector<Notification*> notifications;
    notifications.push_back(new EmailNotification("user@example.com",
                                                  "Hello from C++",
                                                  "Greetings"));
    notifications.push_back(new SmsNotification("+1234567890",
                                                "Your code has compiled."));
    notifications.push_back(new PushNotification("user123",
                                                 "You have a new achievement!",
                                                 "Congrats"));
    sendAll(notifications);

    for (const Notification* n : notifications) {
        delete n;
    }
    return 0;
}