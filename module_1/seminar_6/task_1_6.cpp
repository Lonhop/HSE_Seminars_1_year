#include <iostream>
#include <thread>
#include <chrono>

int main() {
    char loader_chars[4] = {'/','|',char(92),char(45)};
    int num_chars = 4;
    int i = 0;

    while (true) {
        std::cout <<"Loading" << "\r" << loader_chars[i] << std::flush;
        i = (i + 1) % num_chars;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    return 0;
}