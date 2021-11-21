#pragma once
#include <concepts>
#include <vector>

template<typename T>
concept integral = std::integral<T>;

template <typename T> requires integral<T>
class vector_ext
{
private:
	int _size = 0;
	std::vector<T> _arr;

public:
	vector_ext(std::vector<T>& array)
	{
		_arr = array;
		_size = array.size();
	}
};
