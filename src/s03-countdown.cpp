#include <cstdlib>
#include <iostream>
#include <string>
#include <locale>
#include <sstream>

auto check_if_number(std::string) -> bool;

auto main(int argc, char *argv[]) -> int {
    if(argc <= 1) {
        std::cout << "No arguments specified!\n";
        return 1;
    } else if(argc > 2) {
        std::cout << "Too many arguments!\n";
        return 2;
    }
    std::string arg(argv[1]);
    if(!check_if_number(arg)) {
        std::cout << "Not a number or a negative number!\n";
        return 3;
    }
    int res;
    std::stringstream num;

    num << arg;
    num >> res;
    if(res == 2147483647) {
        std::cout << "Number is too big!\n";
        return 4;
    }

    do {
        std::cout << res << "...\n";
        res--;
    } while(res >= 0);

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

