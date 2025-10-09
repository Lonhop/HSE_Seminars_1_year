#include <iostream>
#include <thread>
#include <chrono>
#include<cstdlib>

int main() {
    int N = 10;
    int r[N][N];
    while (true) {
        for(int i = 0; i < N; ++i) {
            for (int j = 0; j < N; j++) {
                r[i][j] = rand() % 10;
                std::cout << r[i][j] << ' ' << std::flush;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << std::endl;

        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("clear");
    }
}