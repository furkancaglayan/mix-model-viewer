#include "mixText_asset.h"
namespace mix
{
    namespace assetsystem
    {
        mix::assetsystem::mixText_asset::mixText_asset (const mix::platform::mixAsset_path& path, std::string&& content)
        : mixAsset_item (path)
        {
            _content = std::make_unique<std::string> (std::move (content));
        }
    } // namespace assetsystem
} // namespace mix