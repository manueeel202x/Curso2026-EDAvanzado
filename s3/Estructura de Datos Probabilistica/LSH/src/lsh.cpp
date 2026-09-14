#include "lsh.h"

#include <sstream>
#include <iomanip>
#include <vector>

LSH::LSH(int k, int bands) : k_(k), bands_(bands) {}

std::uint64_t LSH::hash_value(const std::string& value, int seed) const {
    std::uint64_t h = 14695981039346656037ULL + seed;
    for (unsigned char c : value) {
        h ^= c;
        h *= 1099511628211ULL;
    }
    return h;
}

void LSH::add(const std::string& value) {
    values_.push_back(value);
}

std::string LSH::signature(const std::string& value) const {
    std::vector<int> parts;
    for (int i = 0; i < k_; i++) {
        std::uint64_t h = hash_value(value, i);
        int bucket = static_cast<int>(h % bands_);
        parts.push_back(bucket);
    }

    std::ostringstream out;
    for (int i = 0; i < k_; i++) {
        if (i > 0) {
            out << ";";
        }
        out << parts[i];
    }
    return out.str();
}
