#ifndef S42_CAT_H
#define S42_CAT_H

#include <sstream>
#include <string>


namespace s42 {

struct Cat {
    std::string const name;
    constexpr static unsigned LIVES_LEFT { 9 };
    unsigned lives_left{LIVES_LEFT};

    Cat(std::string, unsigned const = LIVES_LEFT);

    auto make_sound() const -> std::string;
    auto adopt_cat(std::string) const -> Cat;
};

}  // namespace s42

#endif
