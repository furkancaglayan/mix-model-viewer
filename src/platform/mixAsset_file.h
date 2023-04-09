#pragma once
#include "typedefs.h"
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include "mixAsset_path.h"

namespace mix
{
    namespace platform
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
        ///
        ///
        class mixAsset_file
        {
            public:

            mixAsset_file (mixAsset_path&& path)
            : _path{ std::move (path) }, _handle{ nullptr }, _buffer{ nullptr }
            {
            }

             mixAsset_file (std::string&& path)
            : _path{ mixAsset_path{ std::move(path) } }, _handle{ nullptr }, _buffer{ nullptr }
            {
            }

            ~mixAsset_file ()
            {
                delete _buffer;
                _buffer = nullptr;
                _handle = nullptr;
            }
            bool open ();
            bool read ();
            bool close ();
            size_t get_file_size ();
            const std::string& get_content ()
            {
                return _content;
            }

            const std::string get_extension ()
            {
                return _path.get_extension();
            }

            const std::string get_name_without_extension ()
            {
                return _path.get_name_without_extension ();
            }

            mixAsset_path _path;

            protected:
            private:

            char* _buffer;
            std::string _content;
            HANDLE _handle;
        };
    } // namespace platform
} // namespace mix
