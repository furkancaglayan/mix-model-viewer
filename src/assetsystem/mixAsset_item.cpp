#include "mixAsset_item.h"

namespace mix
{
    namespace assetsystem
    {
        mixAsset_item::mixAsset_item (std::string&& name) noexcept
        : _name{ std::move (name) }, _guid{ mix::core::mixGuid::create_new () }
        {

        }
        mix::assetsystem::mixAsset_item::mixAsset_item (const std::string& name) noexcept
        : _name{ name }, _guid{ mix::core::mixGuid::create_new () }
        {

        }
    } // namespace assetsystem
} // namespace mix