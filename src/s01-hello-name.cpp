#include <iostream>
#include <string>

auto main() -> int {
    auto name = std::string{};
    std::getline(std::cin, name);

    std::cout << "Hello, " << name << "!\n";

    return 0;
}
