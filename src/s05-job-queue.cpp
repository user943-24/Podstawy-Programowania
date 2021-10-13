#include <iostream>
#include <thread>
#include <array>
#include <mutex>
#include <queue>
#include <random>

std::mutex mtx;

auto get_from_queue(unsigned short, std::queue<int>&) -> void;

auto main() -> int {
    // Random numbers generator
    std::mt19937 engine;
    std::uniform_int_distribution<int> distribution(1, 1000);
    engine.seed(std::random_device{}());

    auto numbers = std::queue<int>{};
    auto threads = std::array<std::thread, 4>{};

    // Filling queue with random numbers
    for(auto i=0; i < 100; ++i)
        numbers.push(distribution(engine));

    while(!numbers.empty()) {
        for(unsigned long i=1; i <= threads.size(); ++i) {
            threads[i-1] = std::thread{get_from_queue, (unsigned short)i, std::ref(numbers)};
        }
        for(auto& t : threads)
            t.join();
    }


    return 0;
}

auto get_from_queue(unsigned short id, std::queue<int>& numbers) -> void {
    std::unique_lock<std::mutex> lck (mtx);
    if(!numbers.empty()) {
        std::cout << id << ": " << numbers.front() << "\n";
        numbers.pop();
    }
}
