#include <iostream>
#include <string>
#include <sstream>
#include <locale>

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
    if(!check_if_number(argv[1])) {
        std::cout << "Not a number or a negative number!\n";
        return 3;
    }
    int count_to;
    std::stringstream num;

    num << arg;
    num >> count_to;
    if(count_to == 2147483647) {
        std::cout << "Number is too big!\n";
        return 4;
    }

    for(auto i = 1; i <= count_to; ++i) {
        if(i%3 == 0 && i%5 == 0)
            std::cout << "FizzBuzz\n";
        else if(i%3 == 0)
            std::cout << "Fizz\n";
        else if(i%5 == 0)
            std::cout << "Buzz\n";
        else
            std::cout << i << "\n";
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
