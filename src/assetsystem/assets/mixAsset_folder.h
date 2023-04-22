#pragma once
#include <memory>
#include <string>
#include "mixAsset_item.h"

namespace mix
{
    namespace assetsystem
    {
        class mixAsset_folder : public mix::assetsystem::mixAsset_item
        {
            public:

            mixAsset_folder (mix::platform::mixAsset_path&& path) noexcept;
            mixAsset_folder (const mix::platform::mixAsset_path& path) noexcept;

            inline const std::string get_path_as_str () const
            {
                return _path;
            }
            private:

            const mix::platform::mixAsset_path _path;
        };
    } // namespace assetsystem
} // namespace mix
