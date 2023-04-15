#include "mixAsset_folder.h"

namespace mix
{
    namespace assetsystem
    {
        mixAsset_item::mixAsset_item (mix::platform::mixAsset_path&& path) noexcept
        : _path{ std::move (path) }, _guid{ mix::core::mixGuid::create_new () }
        {

        }
        mix::assetsystem::mixAsset_item::mixAsset_item (const mix::platform::mixAsset_path& path) noexcept
        : _path{ path }, _guid{ mix::core::mixGuid::create_new () }
        {

        }
    } // namespace assetsystem
} // namespace mix