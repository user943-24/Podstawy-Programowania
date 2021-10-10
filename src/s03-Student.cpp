#include "../include/s1234/Student.h"
#include <iostream>
#include <sstream>


s1234::Student::Student(std::string n, std::string sn, std::string in)

    : name{std::move(n)}, last_name{std::move(sn)}, index_number{std::move(in)} {
}

auto s1234::Student::to_string() const -> std::string {
    auto result = std::ostringstream{};
    result << name
           << " " << last_name
           << " (" << index_number << "), "
           << "semestr " << semester << ": "
           << average_grade;

    return result.str();
}


auto main() -> int {
    auto student = s1234::Student("Jan", "Nowak", "s12345");
    student.average_grade = 3.5;
    std::cout << student.to_string() << "\n";

    return 0;
}
