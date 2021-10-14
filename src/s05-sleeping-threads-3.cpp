#include "../include/itp/channel.h"

#include <iostream>
#include <thread>
#include <array>
#include <string>
#include <chrono>
#include <thread>

itp::channel<std::string> ch;

auto threads = std::array<std::thread, 4>{};
auto existing_threads = threads.size();

auto get_from_queue(unsigned short) -> void;

auto main() -> int {
    auto tmp = std::string{};

    for(auto i=0; i < (int)existing_threads; ++i) {
        threads[i] = std::thread{get_from_queue, i+1};
        threads[i].detach();
    }

    using namespace std::chrono_literals;
    do {
        std::getline(std::cin, tmp);
        ch.push(tmp);
        //short sleep to give time for threads do decrement existing_threads
        std::this_thread::sleep_for(100ms);
    } while(existing_threads > 0);

    return 0;
}

auto get_from_queue(unsigned short id) -> void {
    std::string tmp;
    for(;;) {
        tmp = ch.wait();
        if(tmp != "")
            std::cout << id << ": " << tmp << "\n";
        else {
            std::cout << "thread " << id << " exiting\n";
            existing_threads--;
            return;
        }
    }
}
