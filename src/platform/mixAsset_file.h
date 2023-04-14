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
        ///TODO: guid syustem
        class mixAsset_file
        {
            public:

            mixAsset_file (mixAsset_path&& path)
            : _path{ std::move (path) }, _handle{ INVALID_HANDLE_VALUE }
            {
            }

             mixAsset_file (std::string&& path)
            : _path{ mixAsset_path{ std::move (path) } }, _handle{ INVALID_HANDLE_VALUE }
            {
            }

            ~mixAsset_file ()
            {
                _handle = INVALID_HANDLE_VALUE;
            }
            bool open ();
            bool read (char* ptr);
            std::string read_all_text ();

            bool close ();
            size_t get_file_size ();
            

            const std::string& get_extension () const
            {
                return _path.get_extension();
            }

            const std::string& get_name_without_extension () const
            {
                return _path.get_name_without_extension ();
            }

            mixAsset_path _path;

            protected:
            private:

            bool is_open = false;
            HANDLE _handle;
        };
    } // namespace platform
} // namespace mix
