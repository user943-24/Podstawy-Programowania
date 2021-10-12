#include <iostream>

auto main(int argc, char *argv[]) -> int {
    if(argc != 2) {
        std::cout << "Wrong amount of arguments!\n";
        return 1;
    }

    auto pass = std::string{argv[1]};
    auto confirm = std::string{};

    do {
        std::cout << "password: ";
        std::getline(std::cin, confirm);
    } while (confirm != pass);

    std::cout << "ok!\n";

    return 0;
}
