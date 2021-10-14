#include <functional>
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

auto threads = std::array<std::thread, 4>{};
auto existing_threads = threads.size();

auto get_from_queue(unsigned short, std::queue<std::string>&) -> void;

auto main() -> int {
    auto texts = std::queue<std::string>{};
    auto tmp = std::string{};

    for(auto i=0; i < (int)existing_threads; ++i) {
        threads[i] = std::thread{get_from_queue, i+1, std::ref(texts)};
        threads[i].detach();
    }

    do {
        std::getline(std::cin, tmp);
        texts.push(tmp);
    } while(existing_threads > 0);

    return 0;
}

auto get_from_queue(unsigned short id, std::queue<std::string>& texts) -> void {
    using namespace std::chrono;

    for(;;) {
        mtx.lock();
        if(texts.front() != "" && !texts.empty()) {
            std::cout << id << ": " << texts.front() << "\n";
            texts.pop();
            mtx.unlock();
        } else if(texts.empty()) {
            mtx.unlock();
            engine.seed(std::random_device{}());
            auto random_number = distribution(engine);
            std::this_thread::sleep_for(std::chrono::milliseconds(random_number));
        } else {
            texts.pop();
            std::cout << "thread " << id << " exiting\n";
            existing_threads--;
            mtx.unlock();
            return;
        }
    }
}
