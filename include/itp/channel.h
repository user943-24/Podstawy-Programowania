#ifndef INTRODUCTION_TO_PROGRAMMING_IN_CXX_CHANNEL_H
#define INTRODUCTION_TO_PROGRAMMING_IN_CXX_CHANNEL_H

#include <stdexcept>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace itp {
    struct timeout_expired_error : public std::runtime_error {
        using runtime_error::runtime_error;
    };

    template<typename T>
    struct channel {
        using queue_type = typename std::queue<T>;
        using value_type = typename queue_type::value_type;

        private:
        queue_type q;
        std::mutex m;
        std::condition_variable cv;

        auto pop() -> value_type
        {
            auto value = std::move(q.front());
            q.pop();
            return value;
        }

        public:
        auto wait() -> value_type
        {
            std::unique_lock<std::mutex> lck { m };
            if (not q.empty()) {
                return pop();
            }

            cv.wait(lck, [this]{ return (not q.empty()); });
            return pop();
        }

        template<typename Rep, typename Period>
        auto wait_for(std::chrono::duration<Rep, Period> const duration) -> value_type
        {
            std::unique_lock<std::mutex> lck { m };
            if (not q.empty()) {
                return pop();
            }

            cv.wait_for(lck, duration, [this]{ return (not q.empty()); });

            if (q.empty()) {
                throw timeout_expired_error{"channel::wait_for()"};
            }

            return pop();
        }

        auto push(value_type const& value) -> void
        {
            {
                std::lock_guard<std::mutex> lck { m };
                q.push(value);
            }
            cv.notify_one();
        }
        auto push(value_type&& value) -> void
        {
            {
                std::lock_guard<std::mutex> lck { m };
                q.push(std::move(value));
            }
            cv.notify_one();
        }
    };
}

#endif
