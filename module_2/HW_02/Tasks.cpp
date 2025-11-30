#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <memory>

class Logger {
public:
    enum class Level {
        ERROR,
        WARNING,
        INFO,
        DEBUG
    };

private:
    static Logger* instance;
    std::ofstream logFile;
    Level currentLevel;
    std::string filename;

    Logger(const std::string& file) : filename(file), currentLevel(Level::INFO) {
        logFile.open(file, std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Cannot open log file: " + file);
        }
        log("Logger initialized", Level::INFO);
    }

    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        ss << "." << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }

    std::string levelToString(Level level) {
        switch (level) {
            case Level::ERROR: return "ERROR";
            case Level::WARNING: return "WARNING";
            case Level::INFO: return "INFO";
            case Level::DEBUG: return "DEBUG";
            default: return "UNKNOWN";
        }
    }

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance(const std::string& file = "log.txt") {
        static Logger instance(file);
        return instance;
    }

    void log(const std::string& message, Level level) {
        if (static_cast<int>(level) > static_cast<int>(currentLevel)) {
            return;
        }

        if (logFile.is_open()) {
            logFile << "[" << getCurrentTime() << "] "
                    << "[" << levelToString(level) << "] "
                    << message << std::endl;
        }
    }

    void setLevel(Level level) {
        currentLevel = level;
        log("Log level set to: " + levelToString(level), Level::INFO);
    }

    void close() {
        if (logFile.is_open()) {
            log("Logger shutting down", Level::INFO);
            logFile.close();
        }
    }

    ~Logger() {
        close();
    }
};

class TrackedString {
private:
    std::string value;
    int id;
    static int nextId;
    static int objectCount;

    void logConstructor(const std::string& type, const void* thisPtr, const TrackedString* from = nullptr) {
        auto& logger = Logger::getInstance();
        std::string message = "[" + type + "] id=" + std::to_string(id) +
                             " this=" + ptrToString(thisPtr);
        if (from) {
            message += " from id=" + std::to_string(from->id);
        }
        logger.log(message, Logger::Level::INFO);
    }

    void logAssignment(const std::string& type, const void* thisPtr, const TrackedString* from = nullptr) {
        auto& logger = Logger::getInstance();
        std::string message = "[" + type + "] id=" + std::to_string(id) +
                             " this=" + ptrToString(thisPtr);
        if (from) {
            message += " from id=" + std::to_string(from->id);
        }
        logger.log(message, Logger::Level::INFO);
    }

    std::string ptrToString(const void* ptr) {
        std::stringstream ss;
        ss << ptr;
        return ss.str();
    }

public:
    TrackedString() : value(""), id(++nextId) {
        objectCount++;
        logConstructor("default ctor", this);
    }

    TrackedString(const std::string& s) : value(s), id(++nextId) {
        objectCount++;
        logConstructor("string ctor", this);
    }

    TrackedString(const char* s) : value(s), id(++nextId) {
        objectCount++;
        logConstructor("const char* ctor", this);
    }

    TrackedString(const TrackedString& other) : value(other.value), id(++nextId) {
        objectCount++;
        logConstructor("copy ctor", this, &other);
    }

    TrackedString(TrackedString&& other) noexcept : value(std::move(other.value)), id(++nextId) {
        objectCount++;
        logConstructor("move ctor", this, &other);
    }

    TrackedString& operator=(const TrackedString& other) {
        if (this != &other) {
            value = other.value;
            logAssignment("copy assignment", this, &other);
        }
        return *this;
    }

    TrackedString& operator=(TrackedString&& other) noexcept {
        if (this != &other) {
            value = std::move(other.value);
            logAssignment("move assignment", this, &other);
        }
        return *this;
    }

    ~TrackedString() {
        objectCount--;
        auto& logger = Logger::getInstance();
        logger.log("[dtor] id=" + std::to_string(id) + " this=" + ptrToString(this), Logger::Level::INFO);
    }

    const std::string& getValue() const { return value; }
    int getId() const { return id; }
    static int getObjectCount() { return objectCount; }

    friend std::ostream& operator<<(std::ostream& os, const TrackedString& ts) {
        os << ts.value;
        return os;
    }

    friend bool operator==(const TrackedString& lhs, const TrackedString& rhs) {
        auto& logger = Logger::getInstance();
        logger.log("operator== called: id=" + std::to_string(lhs.id) +
                   " vs id=" + std::to_string(rhs.id), Logger::Level::DEBUG);
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const TrackedString& lhs, const TrackedString& rhs) {
        auto& logger = Logger::getInstance();
        logger.log("operator!= called: id=" + std::to_string(lhs.id) +
                   " vs id=" + std::to_string(rhs.id), Logger::Level::DEBUG);
        return lhs.value != rhs.value;
    }

    friend bool operator<(const TrackedString& lhs, const TrackedString& rhs) {
        auto& logger = Logger::getInstance();
        logger.log("operator< called: id=" + std::to_string(lhs.id) +
                   " vs id=" + std::to_string(rhs.id), Logger::Level::DEBUG);
        return lhs.value < rhs.value;
    }

    friend TrackedString operator+(const TrackedString& lhs, const TrackedString& rhs) {
        auto& logger = Logger::getInstance();
        logger.log("operator+ called: id=" + std::to_string(lhs.id) +
                   " + id=" + std::to_string(rhs.id), Logger::Level::DEBUG);
        return TrackedString(lhs.value + rhs.value);
    }
};

int TrackedString::nextId = 0;
int TrackedString::objectCount = 0;

class Wrapper {
private:
    TrackedString str;

public:
    Wrapper(const std::string& s) {
        auto& logger = Logger::getInstance();
        logger.log("Wrapper constructor (without init list) called", Logger::Level::INFO);
        str = TrackedString(s);
    }

};

class TrackedStringWithDelegation {
private:
    std::string value;
    int id;
    static int nextId;

    void logConstructor(const std::string& type, const void* thisPtr, const TrackedStringWithDelegation* from = nullptr) {
        auto& logger = Logger::getInstance();
        std::string message = "[" + type + "] id=" + std::to_string(id) +
                             " this=" + ptrToString(thisPtr);
        if (from) {
            message += " from id=" + std::to_string(from->id);
        }
        logger.log(message, Logger::Level::INFO);
    }

    std::string ptrToString(const void* ptr) {
        std::stringstream ss;
        ss << ptr;
        return ss.str();
    }

public:
    TrackedStringWithDelegation() : TrackedStringWithDelegation("") {
        logConstructor("delegating default ctor", this);
    }

    TrackedStringWithDelegation(const char* s) : TrackedStringWithDelegation(std::string(s)) {
        logConstructor("delegating const char* ctor", this);
    }

    TrackedStringWithDelegation(const std::string& s) : value(s), id(++nextId) {
        logConstructor("main string ctor", this);
    }

    TrackedStringWithDelegation(const TrackedStringWithDelegation& other) : value(other.value), id(++nextId) {
        logConstructor("copy ctor", this, &other);
    }
};

int TrackedStringWithDelegation::nextId = 1000;

int main() {
    auto& logger = Logger::getInstance("program_log.txt");
    logger.setLevel(Logger::Level::DEBUG);

    logger.log(" STARTING PROGRAM ", Logger::Level::INFO);

    logger.log(" TASK 2: Testing different constructors ", Logger::Level::INFO);

    TrackedString a;
    TrackedString b("hello");
    std::string s = "world";
    TrackedString c(s);
    TrackedString d = c;

    logger.log(" TASK 3: Testing initialization lists ", Logger::Level::INFO);

    Wrapper w1("hello");

    logger.log(" TASK 4: Testing delegating constructors ", Logger::Level::INFO);

    TrackedStringWithDelegation x;
    TrackedStringWithDelegation y("test");

    logger.log(" TASK 5: Comparing push_back and emplace_back ", Logger::Level::INFO);

    std::vector<TrackedString> vec;

    vec.push_back(TrackedString("temp"));

    TrackedString ts("str");
    vec.push_back(ts);

    vec.emplace_back("emplaced");

    logger.log(" TASK 6: Testing operator overloading ", Logger::Level::INFO);

    TrackedString string_1("hello");
    TrackedString string_2("world");

    std::cout << "Output: " << string_1 << " " << string_2 << std::endl;

    if (string_1 == string_2) {
        std::cout << "Strings are equal" << std::endl;
    }
    else {
        std::cout << "Strings are not equal" << std::endl;
    }

    if (string_1 < string_2) {
        std::cout << "string_1 is less than string_2" << std::endl;
    }

    auto str3 = string_1 + string_2;
    std::cout << "Concatenated: " << str3 << std::endl;

    logger.log(" PROGRAM FINISHED ", Logger::Level::INFO);
    logger.log("Remaining TrackedString objects: " + std::to_string(TrackedString::getObjectCount()),
               Logger::Level::INFO);

    return 0;
}