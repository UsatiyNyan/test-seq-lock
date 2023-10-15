#include "workers.h"

#include <iostream>

#ifdef TEST_SL_RELAXED

uint32_t increment_once(SharedState& ss) {
    const uint32_t seq0 = ss.seq.fetch_add(1, std::memory_order_relaxed);
    ss.cnt0.fetch_add(1, std::memory_order_relaxed);
    ss.cnt1.fetch_add(1, std::memory_order_relaxed);
    ss.seq.fetch_add(1, std::memory_order_relaxed);
    return seq0 + 2;
}

std::tuple<uint32_t, uint32_t> read_once(SharedState& ss) {
    uint32_t seq0 = 0;
    uint32_t seq1 = 0;
    uint32_t cnt0 = 0;
    uint32_t cnt1 = 0;

    do {
        seq0 = ss.seq.load(std::memory_order_relaxed);
        cnt0 = ss.cnt0.load(std::memory_order_relaxed);
        cnt1 = ss.cnt1.load(std::memory_order_relaxed);
        seq1 = ss.seq.load(std::memory_order_relaxed);
    } while (seq0 != seq1 || seq0 & 1);

    return {cnt0, cnt1};
}

#endif

#ifdef TEST_SL_2HB

uint32_t increment_once(SharedState& ss) {
    
}

std::tuple<uint32_t, uint32_t> read_once(SharedState& ss) {

}

#endif

#ifdef TEST_SL_3HB

uint32_t increment_once(SharedState& ss) {
    
}

std::tuple<uint32_t, uint32_t> read_once(SharedState& ss) {

}

#endif

void increment_worker(SharedState& ss) {
    ss.start.arrive_and_wait();

    while (ss.run.load(std::memory_order_relaxed)) {
        const uint32_t seq = increment_once(ss);
        if (seq % (2 << 20) == 0) {
            std::cout << "curr seq: " << seq << '\n';
        }
    }
}

void reader_worker(SharedState& ss) {
    ss.start.arrive_and_wait();

    while (ss.run.load(std::memory_order_relaxed)) {
        const auto [cnt0, cnt1] = read_once(ss);
        if (cnt0 != cnt1) {
            std::cerr << "counts have diverged: " << cnt0 << " and " << cnt1 << '\n';
            return;
        }
    }
}

