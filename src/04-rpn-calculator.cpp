/*
 * A reverse-polish notation calculator.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <locale>
#include <sstream>

auto pop_top(std::stack<double>&) -> double;
auto evaluate_addition(std::stack<double>&) -> void;
auto evaluate_subtraction(std::stack<double>&) -> void;
auto evaluate_multiplying(std::stack<double>&) -> void;
auto evaluate_dividing(std::stack<double>&) -> void;
auto evaluate_dividing_absolute(std::stack<double>&) -> void;
auto evaluate_modulo(std::stack<double>&) -> void;
auto evaluate_power(std::stack<double>&) -> void;
auto evaluate_sqrt(std::stack<double>&) -> void;
auto evaluate_log10(std::stack<double>&) -> void;
auto make_args(int, char*[]) -> std::vector<std::string>;
auto check_if_double(std::string) -> bool;

auto main(int argc, char* argv[]) -> int {
    auto const args = make_args(argc - 1, argv + 1);
    auto stack = std::stack<double>{};
    std::stringstream sstream;
    double tmp;
    bool wrote = false;

    for (auto each : args) {
        try {
            if (each == "p") {
                std::cout << pop_top(stack) << "\n";
                wrote = true;
            } else if (each == "+") {
                evaluate_addition(stack);
            } else if (each == "-") {
                evaluate_subtraction(stack);
            } else if (each == "*") {
                evaluate_multiplying(stack);
            } else if (each == "/") {
                evaluate_dividing(stack);
            } else if (each == "//") {
                evaluate_dividing_absolute(stack);
            } else if (each == "%") {
                evaluate_modulo(stack);
            } else if (each == "**") {
                evaluate_power(stack);
            } else if (each == "sqrt") {
                evaluate_sqrt(stack);
            } else if (each == "log10") {
                evaluate_log10(stack);
            } else if (!check_if_double(each)) {
                throw std::logic_error{"not a number nor supported symbol"};
            } else {
                sstream.clear();
                sstream << each;
                sstream >> tmp;
                stack.push(tmp);
            }
        } catch (std::logic_error const& e) {
            std::cerr << "error: " << each << ": " << e.what() << "\n";
            return 1;
        }
    }
    if(!wrote)
        std::cout << pop_top(stack) << "\n";

    return 0;
}

auto pop_top(std::stack<double>& stack) -> double {
    if (stack.empty()) {
        throw std::logic_error{"empty stack"};
    }
    auto element = std::move(stack.top());
    stack.pop();
    return element;
}

auto evaluate_addition(std::stack<double>& stack) -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for +"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a + b);
}

auto evaluate_subtraction(std::stack<double>& stack) -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for -"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a - b);
}

auto evaluate_multiplying(std::stack<double>& stack) -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for *"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a * b);
}

auto evaluate_dividing(std::stack<double>& stack) -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for /"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a / b);
}

auto evaluate_dividing_absolute(std::stack<double>& stack) -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for //"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(std::round(a / b));
}

auto evaluate_modulo(std::stack<double>& stack) -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for %"};
    }
    auto const b = std::round(pop_top(stack));
    auto const a = std::round(pop_top(stack));
    stack.push((int)a % (int)b);
}

auto evaluate_power(std::stack<double>& stack) -> void {
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for **"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(std::pow(a, b));
}

auto evaluate_sqrt(std::stack<double>& stack) -> void {
    if (stack.size() < 1) {
        throw std::logic_error{"not enough operands for sqrt"};
    }
    auto const a = pop_top(stack);
    stack.push(std::sqrt(a));
}

auto evaluate_log10(std::stack<double>& stack) -> void {
    if (stack.size() < 1) {
        throw std::logic_error{"not enough operands for log10"};
    }
    auto const a = pop_top(stack);
    stack.push(std::log10(a));
}

auto make_args(int argc, char* argv[]) -> std::vector<std::string> {
    auto args = std::vector<std::string>{};
    std::copy_n(argv, argc, std::back_inserter(args));
    return args;
}

auto check_if_double(std::string word) -> bool {
    if(word[0] == '.')
        return false;
    std::locale loc; // Global locale
    bool dot = false;
    for(auto const &c : word) {
        if(!std::isdigit(c, loc)) {
            if(!dot)
                dot = true;
            else
                return false;
        }
    }
    return true;
}
