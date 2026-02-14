#ifndef BENCHMARK_CONFIG_H
#define BENCHMARK_CONFIG_H

#include <benchmark/benchmark.h>
#include <memory>

struct Object {
    int x = 1;
    int y = 2;
    int z = 3;

    void work() noexcept {
        benchmark::DoNotOptimize(x + y + z);
    }
};

#endif