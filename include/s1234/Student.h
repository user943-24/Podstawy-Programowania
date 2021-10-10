#ifndef S1234_STUDENT_H
#define S1234_STUDENT_H

#include <string>

namespace s1234 {

struct Student {
    std::string const name;
    std::string const last_name;
    std::string const index_number;
    unsigned short semester = 1;
    double average_grade = 0.0;

    Student(std::string, std::string, std::string);

    auto to_string() const -> std::string;
};

} // namespace s1234

#endif // S1234_STUDENT_H
