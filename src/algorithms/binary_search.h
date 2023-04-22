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
            template <class Key, class T, template <typename> class Container> T* binary_search (const Key& key, Container<T> container)
            {

                Container<T> output = input;
                Container<T>::const_iterator in_it = input.begin ();
                std::vector
                for (Container<T>::iterator out_it = std::next (output.begin ()); out_it != output.end (); ++out_it, ++in_it)
                    *out_it += *in_it;
                return output;
            }
        };

    } // namespace algorithms
} // namespace mix
