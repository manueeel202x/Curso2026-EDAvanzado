#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

#include <cstdint>
#include <string>
#include <vector>

class HyperLogLog {
public:
    HyperLogLog(int p = 10);
    void add(const std::string& value);
    double estimate() const;

private:
    int p_;
    int m_;
    double alpha_;
    std::vector<int> registers_;

    std::uint64_t hash(const std::string& value) const;
    int rank(std::uint64_t value) const;
};

#endif
