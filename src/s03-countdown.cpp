#include <iostream>
#include <string>
#include <locale>

auto check_if_number(std::string) -> bool;
auto check_if_number_too_big(std::string) -> bool;

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
        std::cout << "Not a number!\n";
        return 3;
    }
    if(check_if_number_too_big(arg)) {
        std::cout << "Number too big!\n";
        return 4;
    }

    auto count_val = std::stoi(arg);
    do {
        std::cout << count_val << "...\n";
        count_val--;
    } while(count_val >= 0);

    return 0;
}

auto check_if_number(std::string word) -> bool {
    std::locale loc; // Global locale
    bool ret_value = true;
    for(auto &c : word) {
        if(!std::isdigit(c, loc))
            ret_value = false;
    }
    return ret_value;
}

auto check_if_number_too_big(std::string number) -> bool {
    if(number.length() < 10)
        return false;
    else if(number.length() > 10)
        return true;
    else {
        auto max_number = "2147483647";
        for(auto i = 0; i < 10; ++i) {
            if(number[i]-'0' < max_number[i]-'0')
                return false;
            else if(number[i]-'0' > max_number[i]-'0')
                return true;
        }
        return false;
    }
}
