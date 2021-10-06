/*
 * Ask the user for their credentials. Allow them to decline.
 */


#include <iostream>
#include <string>


auto main() -> int
{
    std::cout << "What's your name? ";

    auto name = std::string{};
    std::getline(std::cin, name);

    if (name.empty()) {
        std::cout << "OK, keep your secrets.\n";
    } else {
        std::cout << "Hello, " << name << "!\n";
    }

    return 0;
}
