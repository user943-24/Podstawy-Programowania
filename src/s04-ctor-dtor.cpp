#include <iostream>

struct rand_struct {
    std::string text;
    rand_struct(std::string text) {
        this->text = text;
    }
    ~rand_struct() {
        std::cout << "DESTRUCTION!\n";
        std::cout << text << "\n";
    }
};

auto main() -> int {
    auto x = rand_struct("random text");
    return 0;
}
