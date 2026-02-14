#include "benchmark_config.h"

static void BM_Raw_CreateDestroy(benchmark::State& state) {
    for (auto _ : state) {
        Object* obj = new Object;
        benchmark::DoNotOptimize(obj);
        delete obj;
    }
}
BENCHMARK(BM_Raw_CreateDestroy);

static void BM_Unique_CreateDestroy(benchmark::State& state) {
    for (auto _ : state) {
        std::unique_ptr<Object> obj = std::make_unique<Object>();
        benchmark::DoNotOptimize(obj);
    }
}
BENCHMARK(BM_Unique_CreateDestroy);

static void BM_Shared_CreateDestroy(benchmark::State& state) {
    for (auto _ : state) {
        std::shared_ptr<Object> obj = std::make_shared<Object>();
        benchmark::DoNotOptimize(obj);
    }
}
BENCHMARK(BM_Shared_CreateDestroy);

static void BM_Raw_Dereference(benchmark::State& state) {
    Object* obj = new Object;

    for (auto _ : state) {
        obj->work();
    }

    delete obj;
}
BENCHMARK(BM_Raw_Dereference);

static void BM_Unique_Dereference(benchmark::State& state) {
    std::unique_ptr<Object> obj = std::make_unique<Object>();

    for (auto _ : state) {
        obj->work();
    }
}
BENCHMARK(BM_Unique_Dereference);

static void BM_Shared_Dereference(benchmark::State& state) {
    std::shared_ptr<Object> obj = std::make_shared<Object>();

    for (auto _ : state) {
        obj->work();
    }
}
BENCHMARK(BM_Shared_Dereference);

static void BM_Raw_Copy(benchmark::State& state) {
    Object* obj = new Object;

    for (auto _ : state) {
        Object* copy = obj;
        benchmark::DoNotOptimize(copy);
    }

    delete obj;
}
BENCHMARK(BM_Raw_Copy);

static void BM_Unique_Move(benchmark::State& state) {
    for (auto _ : state) {
        std::unique_ptr<Object> p1 = std::make_unique<Object>();
        std::unique_ptr<Object> p2 = std::move(p1);
        benchmark::DoNotOptimize(p2);
    }
}
BENCHMARK(BM_Unique_Move);

static void BM_Shared_Copy(benchmark::State& state) {
    std::shared_ptr<Object> p1 = std::make_shared<Object>();

    for (auto _ : state) {
        std::shared_ptr<Object> p2 = p1;
        benchmark::DoNotOptimize(p2);
    }
}
BENCHMARK(BM_Shared_Copy);
