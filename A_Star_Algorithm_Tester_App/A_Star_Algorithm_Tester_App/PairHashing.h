#pragma once
#include <cstddef>
#include <utility>

class PairHashing
{
public:
	std::size_t operator()(const std::pair<float, float>& p) const;
	std::size_t operator()(const std::pair<int, int>& p) const;
};