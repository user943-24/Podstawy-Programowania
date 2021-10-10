#include <iostream>
#include <locale>
#include <sstream>
#include <limits>

auto check_if_number(std::string) -> bool;

auto main(int argc, char *argv[]) -> int {
    if(argc > 2) {
        std::cout << "Too many arguments!\n";
        return 1;
    }

    auto original = 99;
    auto count = 99;

    if(argc == 2) {
        if(!check_if_number(argv[1])) {
            std::cout << "Not a number or a negative number!\n";
            return 2;
        }
        auto const IMAX = std::numeric_limits<int>::max();
        std::stringstream sstream;
        sstream << argv[1];
        sstream >> original;
        if(original == IMAX) {
            std::cout << "Number too big!\n";
            return 3;
        }
        count = original;
    }

    for(; count > 1; --count) {
        std::cout << count << " bottles of beer on the wall,"
            " " << count << " bottles of beer.\n"
            "Take one down, pass it around,"
            " " << count << " bottles of beer on the wall...\n";
    }
    std::cout << "1 bottle of beer on the wall,"
        " 1 bottle of beer.\n"
        "Take one down, pass it around,"
        " 1 bottle of beer on the wall...\n";

    if(original == 1) {
        std::cout << "No more bottles of beer on the wall, "
            "no more bottles of beer.\n"
            "Go to the store and buy some more,"
            " 1 bottle of beer on the wall...\n";
    } else {
        std::cout << "No more bottles of beer on the wall, "
            "no more bottles of beer.\n"
            "Go to the store and buy some more,"
            " " << original << " bottles of beer on the wall...\n";
    }


    return 0;
}

auto check_if_number(std::string word) -> bool {
    std::locale loc; // Global locale
    for(auto &c : word) {
        if(!std::isdigit(c, loc))
            return false;
    }
    return true;
}
