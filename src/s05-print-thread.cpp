#include <iostream>
#include <thread>
#include <array>

auto print_hello(unsigned) -> void;

auto main() -> int {
    auto threads = std::array<std::thread, 42>{};
    auto i = 1;

    for(auto& t : threads) {
        t = std::thread(print_hello, i);
        ++i;
        t.detach();
    }

    return 0;
}

auto print_hello(unsigned x) -> void {
    std::cout << "Hello " << x << "!\n";
}
