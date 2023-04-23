#pragma once
#include <Windows.h>
#include <functional>
#include <string>
#include <tchar.h>
#include <vector>

namespace mix
{
    namespace algorithms
    {
        class search
        {
            template <class ForwardIt, class T, class Compare>
            bool binary_search (ForwardIt first, ForwardIt last, const T& value, Compare comp, size_t& pos)
            {
                last = std::lower_bound (first, last, value, comp);
                pos = last - first;
                return (!(first == last) && !(comp (value, *first)));
            }
        };

    } // namespace algorithms
} // namespace mix
