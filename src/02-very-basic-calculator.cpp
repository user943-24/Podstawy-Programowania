/*
 * A very basic calculator, with rudimentary error handling.
 */

#include <iostream>
#include <string>

auto read_int_from_stdin(std::string prompt) -> int
{
    try {
        auto s = std::string{};
        std::cout << prompt;
        std::getline(std::cin, s);
        return std::stoi(s);
    } catch (std::invalid_argument const&) {
        return 0;
    }

    return 0;
}

auto main() -> int
{
    auto const left_hand_operand  = read_int_from_stdin("lhs = ");
    auto const right_hand_operand = read_int_from_stdin("rhs = ");

    std::cout << "op = ";
    auto const action = static_cast<char>(std::getchar());

    auto result = int{0};
    switch (action) {
    case '+':
        result = (left_hand_operand + right_hand_operand);
        break;
    case '-':
        result = (left_hand_operand - right_hand_operand);
        break;
    case '%':
        result = (left_hand_operand % right_hand_operand);
        break;
    default:
        // return 1 to signal that an error occured
        return 1;
    }

    std::cout << left_hand_operand << ' ' << action << ' ' << right_hand_operand
              << " = " << result << '\n';

    return 0;
}
