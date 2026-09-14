#ifndef LSH_H
#define LSH_H

#include <cstdint>
#include <string>
#include <vector>

class LSH {
public:
    LSH(int k = 3, int bands = 5);
    void add(const std::string& value);
    std::string signature(const std::string& value) const;

private:
    int k_;
    int bands_;
    std::vector<std::string> values_;

    std::uint64_t hash_value(const std::string& value, int seed) const;
};

#endif
