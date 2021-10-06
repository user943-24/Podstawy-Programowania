#include <s42/Cat.h>

#include <iostream>

s42::Cat::Cat(std::string n, unsigned const ll)
        : name{std::move(n)}, lives_left{ll}
{}

auto s42::Cat::adopt_cat(std::string new_name) const -> Cat
{
    return Cat{std::move(new_name), lives_left};
}

auto s42::Cat::make_sound() const -> std::string
{
    auto out = std::ostringstream{};
    out << "Meow! ("
        << name
        << ", with "
        << lives_left
        << " lives left)";
    return out.str();
}

auto main() -> int
{
    auto cat = s42::Cat{"Mr. Snuggles"};
    std::cout << cat.make_sound() << "\n";

    // uciek
    --cat.lives_left;

    auto cat_basi = cat.adopt_cat("Evil Elvis");
    std::cout << cat_basi.make_sound() << "\n";

    return 0;
}
