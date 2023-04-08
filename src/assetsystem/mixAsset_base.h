#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <cassert>

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
        class mixAsset_base
        {
            public:

            mixAsset_base (std::string&& path)
            {
                _data.open (path, std::ios::in);
            }
            void read ();
            void close ();
            std::string get_content () const
            {
                return _content;
            }
            protected:

            std::ifstream _data;
            std::string _content;
        };
    } // namespace core
} // namespace mix
