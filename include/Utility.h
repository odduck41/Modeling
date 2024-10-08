#pragma once
#include <chrono>

class Timer {
  public:
    Timer() = default;
    explicit Timer(const std::chrono::milliseconds& d)
     : difference_(d) {}
    void updateDifference(const std::chrono::milliseconds& d) {
        difference_ = d;
    }
    bool lasted() {
        std::chrono::milliseconds now(
                std::chrono::system_clock::now()
                .time_since_epoch().count()
                );
        return now - last_ >= difference_;
    }
    void reset() {
        std::chrono::milliseconds now(
                std::chrono::system_clock::now()
                        .time_since_epoch().count()
        );
        last_ = now;
    }
  private:
    std::chrono::milliseconds last_{
        std::chrono::system_clock::now().time_since_epoch().count()};
    std::chrono::milliseconds difference_{};
};
