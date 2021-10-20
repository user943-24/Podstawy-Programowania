#ifndef S1234_TIME_H
#define S1234_TIME_H

#include <cstdint>
#include <string>

namespace s1234 {

struct Time {
    unsigned short hour = 0;
    unsigned short minute = 0;
    unsigned short second = 0;
    enum Time_of_day {
        morning,
        afternoon,
        evening,
        night,
    };

    Time() = default;
    Time(unsigned short, unsigned short, unsigned short);

    auto next_hour() -> void;
    auto next_minute() -> void;
    auto next_second() -> void;
    auto to_string() const -> std::string;
    auto to_string(Time_of_day) const -> std::string;
    auto time_of_day() const -> Time_of_day;
    auto count_seconds() const -> std::uint64_t;
    auto count_minutes() const -> std::uint64_t;
    auto time_to_midnight() const -> Time;

    auto operator+  (Time const&) const -> Time;
    auto operator-  (Time const&) const -> Time;
    auto operator<  (Time const&) const -> bool;
    auto operator>  (Time const&) const -> bool;
    auto operator== (Time const&) const -> bool;
    auto operator!= (Time const&) const -> bool;
};

}

#endif // S1234_TIME_H
