#include "../include/s1234/Time.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>

namespace s1234 {
    Time::Time(unsigned short h, unsigned short m, unsigned short s) :
        hour{std::move(h)}, minute{std::move(m)}, second{std::move(s)} {}

    auto Time::next_hour() -> void {
        if(hour == 23)
            hour = 0;
        else
            hour++;
    }

    auto Time::next_minute() -> void {
        if(minute == 59) {
            minute = 0;
            next_hour();
        } else
            minute++;
    }

    auto Time::next_second() -> void {
        if(second == 59) {
            second = 0;
            next_minute();
        } else {
            second++;
        }
    }

    auto Time::to_string() const -> std::string {
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

    auto Time::to_string(Time::Time_of_day tod) const -> std::string {
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

    auto Time::time_of_day() const -> Time_of_day {
        if(hour >= 6 && hour <= 11)
            return Time::morning;
        else if(hour >= 12 && hour <= 16)
            return Time::afternoon;
        else if(hour >= 17 && hour <= 20)
            return Time::evening;
        else
            return Time::night;
    }

    auto Time::count_seconds() const -> std::uint64_t {
        std::uint64_t count = 0;
        count += hour * 60 * 60;
        count += minute * 60;
        count += second;
        return count;
    }

    auto Time::count_minutes() const -> std::uint64_t {
        std::uint64_t count = 0;
        count += hour * 60;
        count += minute;
        return count;
    }

    auto Time::time_to_midnight() const -> Time {
        Time time;
        time.second = 60 - second;

        if(time.second > 0)
            time.minute = 59 - minute;
        else
            time.minute = 60 - minute;

        if(time.minute > 0)
            time.hour = 23 - hour;
        else
            time.minute = 24 - hour;

        return time;
    }

    auto Time::operator+ (Time const& o) const -> Time {
        unsigned short h = hour;
        unsigned short m = minute;
        unsigned short s = second;
        s += o.second;
        if(s > 59) {
            s -= 60;
            m++;
        }
        m += o.minute;
        if(m > 59) {
            m -= 60;
            h++;
        }
        h += o.hour;
        if(h > 23)
            h -= 24;

        return Time(h, m, s);
    }

    auto Time::operator- (Time const& o) const -> Time {
        short h = hour;
        short m = minute;
        short s = second;
        s -= o.second;
        if(s < 0) {
            s += 60;
            m--;
        }
        m -= o.minute;
        if(m < 0) {
            m += 60;
            h--;
        }
        h -= o.hour;
        if(h < 0)
            h += 24;

        return Time(h, m, s);
    }

    auto Time::operator< (Time const& o) const -> bool {
        if(hour < o.hour)
            return true;
        if(hour != o.hour)
            return false;
        if(minute < o.minute)
            return true;
        if(minute != o.minute)
            return false;
        if(second < o.second)
            return true;
        if(second != o.minute)
            return false;
        return false;
    }

    auto Time::operator> (Time const& o) const -> bool {
        if(hour > o.hour)
            return true;
        if(hour != o.hour)
            return false;
        if(minute > o.minute)
            return true;
        if(minute != o.minute)
            return false;
        if(second > o.second)
            return true;
        if(second != o.minute)
            return false;
        return false;
    }

    auto Time::operator== (Time const& o) const -> bool {
        return (hour==o.hour && minute==o.minute&&second==o.second);
    }

    auto Time::operator!= (Time const& o) const -> bool {
        return !(hour==o.hour && minute==o.minute&&second==o.second);
    }
}

auto main() -> int {
    auto time = s1234::Time(23, 59, 59);

    std::cout << time.to_string() << "\n";

    time.next_minute();

    std::cout << time.to_string() << "\n";

    std::cout << time.to_string(time.time_of_day()) << "\n";

    std::cout << "seconds: " << time.count_seconds() << "\n";
    std::cout << "minutes: " << time.count_minutes() << "\n";
    std::cout << "time to midnight: " << time.time_to_midnight().to_string() << "\n";

    auto x = time + s1234::Time(10, 50, 30);
    auto y = x - s1234::Time(0, 0, 31);

    std::cout << x.to_string() << "\n";
    std::cout << y.to_string() << "\n";

    return 0;
}
