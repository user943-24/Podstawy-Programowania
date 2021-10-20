#include <string>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

auto main() -> int {
    auto name = std::string{"./example.txt"};
    auto fd = open(name.c_str(), O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

    close(fd);

    return 0;
}
