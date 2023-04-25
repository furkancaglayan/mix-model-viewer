#pragma once
#include "typedefs.h"
#include "windows/platform_utils.h"
#include <algorithm>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace mix
{
    namespace platform
    {
        class mixAsset_path
        {
            public:

            mixAsset_path (const std::string& path);


            inline operator std::string () const
            {
                return std::string{ _path };
            }

            inline operator std::wstring () const
            {
                return std::wstring{ _path.begin (), _path.end () };
            }

            inline const std::string& to_str () const
            {
                return _path;
            }

            inline const std::string& get_name_without_extension () const
            {
                return _base_name;
            }

            inline const std::string& get_extension () const
            {
                return _extension;
            }

            inline const std::string& get_name () const
            {
                return _name;
            }


            inline const std::string& operator() ()
            {
                return _path;
            }

            inline operator std::string& ()
            {
                return _path;
            }

            inline operator const char* ()
            {
                return _path.c_str();
            }


            inline mixAsset_path operator+ (const mixAsset_path& str) const
            {
                std::string return_val{ _path };
                return_val.append (str._path);
                return mixAsset_path{ std::move (return_val) };
            }
            // member function
            inline mixAsset_path operator+ (const std::string& str) const
            {
                std::string return_val{ _path };
                return_val.append (str);
                return mixAsset_path{ std::move (return_val) };
            }

            inline bool operator== (const mixAsset_path& p) const
            {
                return !p._path.compare (_path);
            }

            inline bool operator!= (const mixAsset_path& p) const
            {
                return p._path.compare (_path);
            }

            inline std::ostream& operator<< (std::ostream& os) const
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

            std::string _name;
            std::string _base_name;
            std::string _extension;
            std::string _path;
        };
    }; // namespace platform
} // namespace mix
