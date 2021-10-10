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

auto main() -> int {
    auto time = s1234::Time(23, 59, 59);

    std::cout << time.to_string() << "\n";

    time.next_minute();

    std::cout << time.to_string() << "\n";

    return 0;
}
