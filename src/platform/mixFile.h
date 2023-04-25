#pragma once
#include "mixAsset_path.h"
#include "typedefs.h"
#include <cassert>
#include <memory>
#include <sstream>
#include <string>
#include "../assetsystem/assets/mixAsset_item.h"
#include "../assetsystem/asset_types.h"

namespace mix
{
    namespace platform
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
        ///
        /// TODO: guid syustem
        class mixFile
        {
            public:

            mixFile (mixAsset_path&& path);
            mixFile (const mixAsset_path& path);
            mixFile (std::string&& path);
            ~mixFile ();

            bool open ();
            bool read (char* ptr);
            std::string read_all_text ();
            bool close ();
            size_t get_file_size ();


            inline const std::string& get_extension () const
            {
                return _path.get_extension ();
            }

            inline const mix::assetsystem::asset_type get_asset_type () const
            {
                return mix::assetsystem::asset_types::get_asset_type (get_extension());
            }

            inline const std::string& get_name_without_extension () const
            {
                return _path.get_name_without_extension ();
            }

            
            inline const std::string& get_path () const
            {
                return _path.to_str();
            }

            mixAsset_path _path;

            protected:
            private:

            bool is_open = false;
            HANDLE _handle;
        };
    } // namespace platform
} // namespace mix
