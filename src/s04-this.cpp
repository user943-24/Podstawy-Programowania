#include <iostream>

struct rand_struct {
    rand_struct() = default;
    ~rand_struct();

    auto f_this() -> rand_struct* {
        return this;
    }
};
