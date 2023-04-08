#pragma once
#include "typedefs.h"
#include <memory>
#include <string>
#include <vector>

namespace mix
{
    namespace platform
    {
        class mixAsset_path
        {
            public:

            mixAsset_path (std::string&& path) : _path{ std::move (path) }
            {
            }

            mixAsset_path (std::string path) : _path{ path }
            {
            }

            operator std::string () const
            {
                return std::string{ _path };
            }

            operator std::wstring () const
            {
                return std::wstring{ _path.begin (), _path.end () };
            }

            std::string to_str () const
            {
                return _path;
            }

            const inline std::string& operator() ()
            {
                return _path;
            }

            inline operator std::string& ()
            {
                return _path;
            }

            inline mixAsset_path operator+ (const mixAsset_path& str)
            {
                std::string return_val{ _path };
                return_val.append (str._path);
                return mixAsset_path{ return_val };
            }
            // member function
            inline mixAsset_path operator+ (const std::string& str)
            {
                std::string return_val{ _path };
                return_val.append (str);
                return mixAsset_path{ return_val };
            }

            bool operator== (const mixAsset_path& p)
            {
                return !p._path.compare (_path);
            }

            bool operator!= (const mixAsset_path& p)
            {
                return p._path.compare (_path);
            }

            inline std::ostream& operator<< (std::ostream& os)
            {
                os << _path;
                return os;
            }
            inline std::istream& operator>> (std::istream& in)
            {
                in >> _path;
                return in;
            }

            private:

            std::string _path;
        };
    }; // namespace platform
} // namespace mix
