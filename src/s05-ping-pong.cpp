#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <utility>
#include <string>

std::mutex mtx;
std::condition_variable ping_cv, pong_cv;
bool ping=true;

std::mt19937 engine;
std::uniform_int_distribution<int> distribution(1, 42);

auto refuse(std::string, unsigned&) -> void;

auto main() -> int {
    engine.seed(std::random_device{}());
    unsigned number = 0;
    auto ping = std::pair<std::thread, std::string>{};
    auto pong = std::pair<std::thread, std::string>{};

    ping.second = "ping";
    pong.second = "pong";

    ping.first = std::thread{refuse, ping.second, std::ref(number)};
    pong.first = std::thread{refuse, pong.second, std::ref(number)};

    ping.first.join();
    pong.first.join();

    return 0;
}

auto refuse(std::string id, unsigned& number) -> void {
    for(;;) {
        std::unique_lock<std::mutex> lck(mtx);
        if(id == "ping")
            while(!ping) {
                ping_cv.wait(lck);
            }
        else
            while(ping) {
                pong_cv.wait(lck);
            }

        if(number > 1024) {
            if(id == "ping") {
                ping = false;
                pong_cv.notify_all();
            } else {
                ping = true;
                ping_cv.notify_all();
            }
            return;
        }

        number += distribution(engine);
        std::cout << id << " " << number << "\n";

        if(id == "ping") {
            ping = false;
            pong_cv.notify_all();
        } else {
            ping = true;
            ping_cv.notify_all();
        }
    }
}
