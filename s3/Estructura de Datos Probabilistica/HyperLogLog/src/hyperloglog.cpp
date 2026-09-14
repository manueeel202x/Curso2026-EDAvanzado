#include "hyperloglog.h"

#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

HyperLogLog::HyperLogLog(int p) : p_(p), m_(1 << p), registers_(m_, 0) {
    alpha_ = 0.7213 / (1.0 + (1.079 / static_cast<double>(m_)));
}

std::uint64_t HyperLogLog::hash(const std::string& value) const {
    std::uint64_t h = 14695981039346656037ULL;
    for (unsigned char c : value) {
        h ^= c;
        h *= 1099511628211ULL;
    }
    return h;
}

int HyperLogLog::rank(std::uint64_t value) const {
    int zeros = 0;
    int limit = 64 - p_;
    std::uint64_t mask = 1ULL << (limit - 1);

    while (mask > 0) {
        if (value & mask) {
            break;
        }
        zeros++;
        mask >>= 1;
    }

    return zeros + 1;
}

void HyperLogLog::add(const std::string& value) {
    std::uint64_t h = hash(value);
    int idx = static_cast<int>(h & (m_ - 1));
    std::uint64_t rest = h >> p_;
    int r = rank(rest);

    if (r > registers_[idx]) {
        registers_[idx] = r;
    }
}

double HyperLogLog::estimate() const {
    double sum = 0.0;
    for (int value : registers_) {
        sum += std::pow(2.0, -value);
    }

    double estimate = alpha_ * m_ * m_ / sum;
    int zeros = 0;

    for (int value : registers_) {
        if (value == 0) {
            zeros++;
        }
    }

    if (zeros > 0 && estimate <= 2.5 * m_) {
        return m_ * std::log(static_cast<double>(m_) / zeros);
    }

    return estimate;
}
