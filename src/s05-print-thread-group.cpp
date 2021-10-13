#include <iostream>
#include <thread>
#include <array>

auto print_hello(unsigned) -> void;

auto main() -> int {
    auto threads = std::array<std::thread, 42>{};

    for(long unsigned i=1; i <= threads.size(); ++i) {
        threads[i-1] = std::thread(print_hello, i);
        if(i%6 == 0) {
            for(auto j=i-6; j < i; ++j)
                threads[j].join();
        }
    }

    return 0;
}

auto print_hello(unsigned x) -> void {
    std::cout << "Hello " << x << "!\n";
}
