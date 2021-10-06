/*
 * A demonstration of loops in C++.
 */

#include <iostream>

auto for_loop(int const init, int const limit) -> void
{
    for (auto i = init; i < limit; ++i) {
        std::cout << "for-i = " << i << '\n';
    }
}

auto while_loop(int const init, int const limit) -> void
{
    auto i = init;
    while (i < limit) {
        std::cout << "while-i = " << i << '\n';
        ++i;
    }
}

auto do_while_loop(int const init, int const limit) -> void
{
    auto i = init;
    do {
        std::cout << "do-while-i = " << i << '\n';
        ++i;
    } while (i < limit);
}

auto main() -> int
{
    for_loop(0, 5);
    while_loop(0, 5);
    do_while_loop(0, 5);

    // for_loop(0, 0);
    // while_loop(0, 0);
    // do_while_loop(0, 0);

    return 0;
}
