#pragma once
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "typedefs.h"
namespace mix
{
    namespace platform
    {
        class mixAsset_path
        {
            public:

            mixAsset_path (std::string&& path) : _path{ std::move (path) }
            {
                _name = _path.substr (_path.find_last_of ("/\\") + 1);
                std::string::size_type const p (_name.find_last_of ('.'));
                if (platform_utils::is_file(_path))
                {
                    _extension = _name.substr (p + 1);
                }
                else
                {
                    _extension = std::string ();
                }
                _base_name = _name.substr (0, p);
            }

            operator std::string () const
            {
                return std::string{ _path };
            }

            operator std::wstring () const
            {
                return std::wstring{ _path.begin (), _path.end () };
            }

            const std::string& to_str ()
            {
                return _path;
            }

            const std::string& get_name_without_extension ()
            {
                return _base_name;
            }

            const std::string& get_extension ()
            {
                return _extension;
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
                return mixAsset_path{ std::move(return_val) };
            }
            // member function
            inline mixAsset_path operator+ (const std::string& str)
            {
                std::string return_val{ _path };
                return_val.append (str);
                return mixAsset_path{ std::move (return_val) };
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

            std::string _name;
            std::string _base_name;
            std::string _extension;
            std::string _path;
        };
    }; // namespace platform
} // namespace mix
