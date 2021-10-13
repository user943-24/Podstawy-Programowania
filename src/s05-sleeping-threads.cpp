#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <chrono>
#include <array>
#include <string>
#include <random>

std::mutex mtx;
std::mt19937 engine;
std::uniform_int_distribution<int> distribution(10, 100);

auto get_from_queue(unsigned short, std::queue<std::string>&) -> void;

auto main() -> int {
    auto threads = std::array<std::thread, 4>{};
    auto existing_threads = threads.size();
    auto texts = std::queue<std::string>{};
    auto tmp = std::string{};

    // for(auto& t : threads) {
    // }

    do {
        std::getline(std::cin, tmp);
        texts.push(tmp);
    } while(existing_threads > 0);

    return 0;
}

auto get_from_queue(unsigned short id, std::queue<std::string>& texts) -> void {
    std::unique_lock<std::mutex> lck (mtx);

    using namespace std::chrono;

    if(!texts.empty() || texts.front() != "") {
        std::cout << id << ": " << texts.front() << "\n";
        texts.pop();
    } else if(texts.empty()) {
        engine.seed(std::random_device{}());
        auto random_number = distribution(engine);
        std::this_thread::sleep_for(std::chrono::milliseconds(random_number));
    } else {
        std::cout << "thread " << id << " exiting";
        return;
    }
}
