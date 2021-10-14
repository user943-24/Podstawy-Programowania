#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <chrono>
#include <array>
#include <string>
#include <random>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;

std::mt19937 engine;
std::uniform_int_distribution<int> distribution(10, 100);

auto threads = std::array<std::thread, 4>{};
auto existing_threads = threads.size();

auto get_from_queue(unsigned short, std::queue<std::string>&) -> void;

auto main() -> int {
    engine.seed(std::random_device{}());
    auto texts = std::queue<std::string>{};
    auto tmp = std::string{};

    for(auto i=0; i < (int)existing_threads; ++i) {
        threads[i] = std::thread{get_from_queue, i+1, std::ref(texts)};
        threads[i].detach();
    }

    using namespace std::chrono_literals;
    do {
        std::getline(std::cin, tmp);
        texts.push(tmp);
        cv.notify_all();
        //short sleep to give time for threads do decrement existing_threads
        std::this_thread::sleep_for(100ms);
    } while(existing_threads > 0);

    return 0;
}

auto get_from_queue(unsigned short id, std::queue<std::string>& texts) -> void {
    using namespace std::chrono;

    for(;;) {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck);
        if(texts.front() != "" && !texts.empty()) {
            std::cout << id << ": " << texts.front() << "\n";
            texts.pop();
            lck.unlock();
        } else if(texts.empty()) {
            lck.unlock();
            auto random_number = distribution(engine);
            std::this_thread::sleep_for(std::chrono::milliseconds(random_number));
        } else {
            texts.pop();
            std::cout << "thread " << id << " exiting\n";
            existing_threads--;
            lck.unlock();
            return;
        }
    }
}
