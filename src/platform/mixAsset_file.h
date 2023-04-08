#pragma once
#include "typedefs.h"
#include <cassert>
#include <memory>
#include <string>

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
            : _path{ mixAsset_path (std::move (path)) }, _handle{ nullptr }, _buffer{ nullptr }
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
            std::string get_content () const
            {
                return _content;
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
