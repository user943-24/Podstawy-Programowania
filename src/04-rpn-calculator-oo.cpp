/*
 * A reverse-polish notation calculator.
 */

#include "../include/RPN_calculator.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include <locale>


static auto pop_top(std::stack<double>& stack) -> double {
    if (stack.empty()) {
        throw std::logic_error{"empty stack"};
    }
    auto element = std::move(stack.top());
    stack.pop();
    return element;
}

static auto check_if_double(std::string word) -> bool {
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


namespace student { namespace rpn_calculator {
    Element::~Element() {}

    Literal::Literal(double const v) : value{v} {}
    auto Literal::evaluate(stack_type& stack) const -> void {
        stack.push(value);
    }

    auto Print::evaluate(stack_type& stack) const -> void {
        std::cout << stack.top() << "\n";
    }

    auto Addition::evaluate(stack_type& stack) const -> void {
        if (stack.size() < 2) {
            throw std::logic_error{"not enough operands for +"};
        }
        auto const b = pop_top(stack);
        auto const a = pop_top(stack);
        stack.push(a + b);
    }

    auto Subtraction::evaluate(stack_type& stack) const -> void {
        if (stack.size() < 2) {
            throw std::logic_error{"not enough operands for -"};
        }
        auto const b = pop_top(stack);
        auto const a = pop_top(stack);
        stack.push(a - b);
    }

    auto Multiplying::evaluate(stack_type& stack) const -> void {
        if (stack.size() < 2) {
            throw std::logic_error{"not enough operands for *"};
        }
        auto const b = pop_top(stack);
        auto const a = pop_top(stack);
        stack.push(a * b);
    }

    auto Dividing::evaluate(stack_type& stack) const -> void {
        if (stack.size() < 2) {
            throw std::logic_error{"not enough operands for /"};
        }
        auto const b = pop_top(stack);
        auto const a = pop_top(stack);
        stack.push(a / b);
    }

    auto Dividing_Absolute::evaluate(stack_type& stack) const -> void {
        if (stack.size() < 2) {
            throw std::logic_error{"not enough operands for //"};
        }
        auto const b = pop_top(stack);
        auto const a = pop_top(stack);
        stack.push(std::round(a / b));
    }

    auto Modulo::evaluate(stack_type& stack) const -> void {
        if (stack.size() < 2) {
            throw std::logic_error{"not enough operands for %"};
        }
        auto const b = std::round(pop_top(stack));
        auto const a = std::round(pop_top(stack));
        stack.push((int)a % (int)b);
    }

    auto Power::evaluate(stack_type& stack) const -> void {
        if (stack.size() < 2) {
            throw std::logic_error{"not enough operands for **"};
        }
        auto const b = pop_top(stack);
        auto const a = pop_top(stack);
        stack.push(std::pow(a, b));
    }

    auto Sqrt::evaluate(stack_type& stack) const -> void {
        if (stack.size() < 2) {
            throw std::logic_error{"not enough operands for sqrt"};
        }
        auto const a = pop_top(stack);
        stack.push(std::sqrt(a));
    }

    auto Log10::evaluate(stack_type& stack) const -> void {
        if (stack.size() < 2) {
            throw std::logic_error{"not enough operands for log10"};
        }
        auto const a = pop_top(stack);
        stack.push(std::log10(a));
    }

    Calculator::Calculator(stack_type s) : stack{std::move(s)} {}

    auto Calculator::push(std::unique_ptr<Element> op) -> void {
        ops.push(std::move(op));
    }

    // FIXME implement Calculator::push(std::string)

    auto Calculator::evaluate() -> void {
        while (not ops.empty()) {
            auto op = std::move(ops.front());
            ops.pop();

            op->evaluate(stack);
        }
    }
}}  // namespace student::rpn_calculator


auto make_args(int argc, char* argv[], bool const with_exec = false)
    -> std::vector<std::string> {
    auto args         = std::vector<std::string>{};
    auto const offset = static_cast<size_t>(not with_exec);
    std::copy_n(argv + offset, argc - offset, std::back_inserter(args));
    return args;
}

auto main(int argc, char* argv[]) -> int {
    using student::rpn_calculator::Calculator;
    auto calculator = Calculator{};

    for (auto const& each : make_args(argc, argv)) {
        try {
            using student::rpn_calculator::Addition;
            using student::rpn_calculator::Subtraction;
            using student::rpn_calculator::Multiplying;
            using student::rpn_calculator::Dividing;
            using student::rpn_calculator::Dividing_Absolute;
            using student::rpn_calculator::Modulo;
            using student::rpn_calculator::Power;
            using student::rpn_calculator::Sqrt;
            using student::rpn_calculator::Log10;
            using student::rpn_calculator::Literal;
            using student::rpn_calculator::Print;

            if (each == "p") {
                calculator.push(std::make_unique<Print>());
            } else if (each == "+") {
                calculator.push(std::make_unique<Addition>());
            } else if (each == "-") {
                calculator.push(std::make_unique<Subtraction>());
            } else if (each == "*") {
                calculator.push(std::make_unique<Multiplying>());
            } else if (each == "/") {
                calculator.push(std::make_unique<Dividing>());
            } else if (each == "//") {
                calculator.push(std::make_unique<Dividing_Absolute>());
            } else if (each == "%") {
                calculator.push(std::make_unique<Modulo>());
            } else if (each == "**") {
                calculator.push(std::make_unique<Power>());
            } else if (each == "sqrt") {
                calculator.push(std::make_unique<Sqrt>());
            } else if (each == "log10") {
                calculator.push(std::make_unique<Log10>());
            } else if (check_if_double(each)) {
                calculator.push(std::make_unique<Literal>(std::stod(each)));
            } else {
                throw std::logic_error{"unknown expression"};
                break;
            }
        } catch (std::logic_error const& e) {
            std::cerr << "error: '" << each << "' : " << e.what() << "\n";
            return 1;
        }
    }

    if(std::string(argv[argc-1]) != "p")
        calculator.push(std::make_unique<student::rpn_calculator::Print>());

    try {
        calculator.evaluate();
    } catch (std::logic_error const& e) {
        std::cerr << "error: during evaluation: " << e.what() << "\n";
    }

    return 0;
}
