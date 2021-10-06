#include <iostream>
#include <string>

auto ask_user_for_integer(std::string) -> int;

auto main() -> int {
    auto const a = ask_user_for_integer("Provide first");
    auto const b = ask_user_for_integer("Provide second");
    std::cout << (a - b) << "\n";

    return 0;
}

auto ask_user_for_integer(std::string prompt) -> int {
    std::cout << prompt << " int: ";
    auto n = std::string{};
    std::getline(std::cin, n);
    return std::stoi(n);
}
