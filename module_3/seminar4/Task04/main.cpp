#include <string>
#include <iostream>
#include <memory>

class Document {
    std::string content_;
    static int instance_count_;
public:
    explicit Document(std::string content) : content_(std::move(content)) {
        ++instance_count_;
    }
    ~Document() {
        --instance_count_;
    }
    std::shared_ptr<Document> clone() const {
        return std::make_shared<Document>(this->content_);
    }
    const std::string& content() {
        return content_;
    }
};

int Document::instance_count_ = 0;


int main() {
    auto doc1 = std::make_shared<Document>("Original");
    {
        auto doc2 = doc1;
        auto doc3 = doc1->clone();
        std::cout << doc1.use_count() << "\n";
    }
    std::cout << doc1.use_count() << "\n";
}