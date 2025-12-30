#include "PairHashing.h"
#include <cstddef>
#include <cmath>

std::size_t PairHashing::operator()(const std::pair<float, float>& pair) const
{
    size_t hash = 0; //hashing for pair<float,float> for maps that use that type of pair
    float max = pair.first < pair.second ? pair.second : pair.first;
    hash = std::abs((pair.second - pair.first) * 2 + max);
    return hash;
}

std::size_t PairHashing::operator()(const std::pair<int, int>& pair) const
{
    size_t hash = 0; // hashing for pair<int,int> for maps that type of pair
    hash = std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1); // xor the 2 results (merge basicly) and change the 2nd by shifting 1 bit to the left.
    return hash;
}
