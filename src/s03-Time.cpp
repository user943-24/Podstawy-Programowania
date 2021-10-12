#include "../include/s1234/Time.h"
#include <iostream>
#include <string>
#include <sstream>

s1234::Time::Time(unsigned short h, unsigned short m, unsigned short s) :
    hour{std::move(h)}, minute{std::move(m)}, second{std::move(s)} {}

auto s1234::Time::next_hour() -> void {
    if(hour == 23)
        hour = 0;
    else
        hour++;
}

auto s1234::Time::next_minute() -> void {
    if(minute == 59) {
        minute = 0;
        next_hour();
    } else
        minute++;
}

auto s1234::Time::next_second() -> void {
    if(second == 59) {
        second = 0;
        next_minute();
    } else {
        second++;
    }
}

auto s1234::Time::to_string() const -> std::string {
    auto out = std::ostringstream{};

    if(hour < 10)
        out << "0" << hour << ":";
    else
        out << hour << ":";

    if(minute < 10)
        out << "0" << minute << ":";
    else
        out << minute << ":";

    if(second < 10)
        out << "0" << second;
    else
        out << second;

    return out.str();
}

auto s1234::Time::to_string(s1234::Time::Time_of_day tod) const -> std::string {
    switch(tod) {
        case morning:
            return "morning";
        case afternoon:
            return "afternoon";
        case  evening:
            return "evening";
        case night:
            return "night";
        default:
            throw "Something's wrong!";
    };
}

auto s1234::Time::time_of_day() const -> Time_of_day {
    if(hour >= 6 && hour <= 11)
        return s1234::Time::morning;
    else if(hour >= 12 && hour <= 16)
        return s1234::Time::afternoon;
    else if(hour >= 17 && hour <= 20)
        return s1234::Time::evening;
    else
        return s1234::Time::night;
}

auto main() -> int {
    auto time = s1234::Time(23, 59, 59);

    std::cout << time.to_string() << "\n";

    time.next_minute();

    std::cout << time.to_string() << "\n";

    std::cout << time.to_string(time.time_of_day()) << "\n";

    return 0;
}
