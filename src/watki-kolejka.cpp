#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>


auto print_stuff_from_queue(
    std::queue<std::string>& k
    , std::mutex& mtx
    , std::condition_variable& cv
    , int const id
) -> void
{
    while (true) {
        std::unique_lock lck { mtx };
        cv.wait(lck);

        if (k.empty()) {
            std::cout << (std::to_string(id) + ": spurious wakeup\n");
            continue;
        }

        auto x = k.front();

        k.pop();

        if (x.empty()) {
            std::cout << (std::to_string(id) + ": done\n");
            break;
        }

        std::cout << (std::to_string(id) + ": " + x + "\n");
    }
}


auto main() -> int
{
    auto k = std::queue<std::string>{};
    std::mutex mtx;
    std::condition_variable cv;

    auto t0 = std::thread{
        print_stuff_from_queue
        , std::ref(k)
        , std::ref(mtx)
        , std::ref(cv)
        , 0
    };
    auto t1 = std::thread{
        print_stuff_from_queue
        , std::ref(k)
        , std::ref(mtx)
        , std::ref(cv)
        , 1
    };

    auto done = 0;

    while (true) {
        auto line = std::string{};
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) {
            ++done;
        }

        {
            std::unique_lock<std::mutex> lck { mtx };
            k.push(std::move(line));
        }
        cv.notify_one();

        if (done >= 2) {
            break;
        }
    }

    t0.join();
    t1.join();

    return 0;
}
