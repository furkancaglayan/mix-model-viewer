#include "mixAsset_manager.h"

namespace mix
{
    namespace assetsystem
    {
        mixAsset_manager::mixAsset_manager (std::string&& root)
        : _root{ std::make_unique<mix::platform::mixAsset_folder> (std::move (root)) }
        {
        }
        mixAsset_manager::mixAsset_manager (const std::string& root)
        : _root{ std::make_unique<mix::platform::mixAsset_folder> (root) }
        {
        }
    } // namespace assetsystem
} // namespace mix