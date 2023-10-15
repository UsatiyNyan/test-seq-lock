#pragma once

#include <thread>
#include <atomic>
#include <new>
#include <latch>

struct SharedState {
    std::latch start;

    alignas(std::hardware_destructive_interference_size)
    std::atomic<uint32_t> seq;

    alignas(std::hardware_destructive_interference_size)
    std::atomic<uint32_t> cnt0;

    alignas(std::hardware_destructive_interference_size)
    std::atomic<uint32_t> cnt1;

    alignas(std::hardware_destructive_interference_size)
    std::atomic<bool> run{true};
};

void increment_worker(SharedState& ss);

void reader_worker(SharedState& ss);

