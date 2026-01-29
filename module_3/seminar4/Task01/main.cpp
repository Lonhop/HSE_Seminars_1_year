#include<iostream>
#include<memory>
#include <string>
#include<cstdio>
#include <stdexcept>

struct FileDeleter {
    void operator()(FILE* file) const {
        if (file) {
            std::fclose(file);
            std::cout << "Closed\n";
        }
    }
};


class FileLogger {
private:
    std::unique_ptr<FILE, FileDeleter> file_;
public:
    explicit FileLogger(const std::string& filename) : file_(std::fopen(filename.c_str(),"w")){
        if (!file_) {
            throw std::runtime_error("No File???");
        }
    }
    FileLogger(const FileLogger&) = delete;
    FileLogger& operator=(const FileLogger&) = delete;

    FileLogger(FileLogger&&) noexcept = default;
    FileLogger& operator=(FileLogger&&) noexcept = default;

    void log(const std::string& messsage) const {
        std::fputs(messsage.c_str(), file_.get());
        std::fputc('\n',file_.get());
        std::fflush(file_.get());
    }
};


int main() {
    FileLogger logger("output.log");
    logger.log("Application started");
    logger.log("Processing data...");
    logger.log("Data precessed");
    // File should close automatically here
}