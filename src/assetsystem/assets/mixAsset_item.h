#pragma once
#include "../../core/mixGuid.h"
#include <iostream>
#include <map>
#include <istream>
#include <fstream>
#include "../../platform/mixAsset_path.h"

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
     

        class mixAsset_item
        {
            public:

            mixAsset_item (mix::platform::mixAsset_path&& path) noexcept;
            mixAsset_item (const mix::platform::mixAsset_path& path) noexcept;

            virtual inline const std::string& get_base_name () const
            {
                return _path.get_name_without_extension ();
            }

              virtual inline const std::string& get_full_name () const
            {
                return _path.get_name ();
            }

            virtual std::ostream& operator<< (std::ostream& out) const;
            virtual std::istream& operator>> (std::istream& in) const;

            inline virtual operator std::string () const
            {
                return get_base_name ();
            }

            inline const mix::core::mixGuid& get_guid () const
            {
                return _guid;
            }
            void set_visible (bool v);
            void create_asset ();
            protected:

            bool is_readonly;
            const mix::core::mixGuid _guid;

            mix::platform::mixAsset_path _path;

        };
    } // namespace assetsystem
} // namespace mix
