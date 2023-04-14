#include "mixText_asset.h"
namespace mix
{
    namespace assetsystem
    {
        mix::assetsystem::mixText_asset::mixText_asset (const std::string& name, std::string&& content)
        : mixAsset_item (name)
        {
            _content = std::make_unique<std::string> (std::move (content));
        }
    } // namespace assetsystem
} // namespace mix