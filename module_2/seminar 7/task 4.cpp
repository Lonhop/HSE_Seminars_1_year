#include <iostream>
#include<string>
#include <vector>

class FS {
    struct File   { std::string name; int size; File(const std::string name, const int size) : name(name), size(size) {}};
    struct Folder { std::string name; std::vector<File> files; Folder(const std::string& name) : name(name) {} };
    Folder root;
public:
    FS(const std::string& rootName) : root(rootName) {}
    FS& operator=(const FS& other) {
        if (this == &other) {
            return *this;
        }
        this->root.name = other.root.name;
        this->root.files = other.root.files;
        return *this;
    }
    void addFile(const std::string& name, int size) {
        this->root.files.emplace_back(name,size);
        std::cout << "Added file " << name << " (" << size << " bytes) to folder " << this->root.name << '\n';
    }
    int totalSize() const {
        int total = 0;
        for (const auto& file : this->root.files) {
            total += file.size;
        }
        return total;
    }
    void print() const {
        std::cout << "Folder: " << this->root.name << "\nFiles (" << this->root.files.size() << "):\n";
        if (this->root.files.empty()) std::cout << " (empty)\n";
        else {
            for (const auto& file : this->root.files) std::cout << " - " << file.name << "(" << file.size << " bytes)\n";
        }
        std::cout << "Total size: " << this->totalSize() << " bytes\n";
    }

};

int main() {
    FS fs("home");
    fs.addFile("notes.txt", 120);
    fs.addFile("image.png", 10240);
    fs.print();
    return 0;
}