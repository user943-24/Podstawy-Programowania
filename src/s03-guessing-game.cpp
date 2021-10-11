#include <iostream>
#include <random>
#include <string>
#include <locale>
#include <sstream>

auto check_if_number(std::string) -> bool;

auto main() -> int {
    // Generating random number
    std::mt19937 engine;
    std::uniform_int_distribution<int> distribution(1, 100);
    engine.seed(std::random_device{}());
    auto const RANDOM_NUMBER = distribution(engine);

    auto tmp = std::string{};
    int number;
    std::stringstream sstream;
    for(;;) {
        sstream.clear();
        std::cout << "guess: ";
        std::getline(std::cin, tmp);
        if(!check_if_number(tmp))
            std::cout << "not a number or a negative number!\n";
        else {
            sstream << tmp;
            sstream >> number;
            if(number > RANDOM_NUMBER)
                std::cout << "number too big!\n";
            else if(number < RANDOM_NUMBER)
                std::cout << "number too small!\n";
            else {
                std::cout << "just right!\n";
                break;
            }
        }
    }

    return 0;
}

auto check_if_number(std::string word) -> bool {
    std::locale loc; // Global locale
    for(auto const &c : word) {
        if(!std::isdigit(c, loc))
            return false;
    }
    return true;
}
