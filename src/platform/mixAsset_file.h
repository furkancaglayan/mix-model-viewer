#pragma once
#include "mixAsset_path.h"
#include "typedefs.h"
#include <cassert>
#include <memory>
#include <sstream>
#include <string>

namespace mix
{
    namespace platform
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
        ///
        /// TODO: guid syustem
        class mixAsset_file
        {
            public:

            mixAsset_file (mixAsset_path&& path);
            mixAsset_file (std::string&& path);
            ~mixAsset_file ();

            bool open ();
            bool read (char* ptr);
            std::string read_all_text ();
            bool close ();
            size_t get_file_size ();


            inline const std::string& get_extension () const
            {
                return _path.get_extension ();
            }

            inline const std::string& get_name_without_extension () const
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
