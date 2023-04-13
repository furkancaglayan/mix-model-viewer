#pragma once
#include "../platform/typedefs.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>
#include <functional>

#if defined(SYSTEM_WIN64)
#include <combaseapi.h>
#endif



namespace mix
{
    namespace core
    {
        /// <summary>
        /// std::unordered_map requires the key type to implement a hash function using operator() and
        /// comparison function for equality.
        /// <see href="https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key">Related stackoverflow pos</see>
        /// </summary>
        class mixGuid
        {
            public:

            static mixGuid create_new ();
            std::string get () const
            {
                return _internal;
            }
            bool operator== (const mixGuid& p) const
            {
                return !_internal.compare (p._internal);
            }

            bool operator!= (const mixGuid& p) const
            {
                return _internal.compare (p._internal);
            }


            mixGuid& operator= (mixGuid t)
            {
                _internal = t._internal;
                return *this;
            }
            private:

            mixGuid (std::string& val) : _internal{ std::move (val) }
            {
            }
            std::string _internal;
        };
    } // namespace core
} // namespace mix

namespace std
{
    template <> struct std::hash<mix::core::mixGuid>
    {
        std::size_t operator() (const mix::core::mixGuid& s) const noexcept
        {
            std::size_t hash = std::hash<std::string>{}(s.get ());
            return hash;
        }
    };
} // namespace std