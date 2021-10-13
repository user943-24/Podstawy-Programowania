#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int {
    if(argc != 3) {
        std::cout << "Wrong number of arguments!\n";
        return 1;
    }
    auto const a = std::stoi(argv[1]);
    auto const b = std::stoi(argv[2]);
    std::cout << (a * b) << "\n";

    return 0;
}
