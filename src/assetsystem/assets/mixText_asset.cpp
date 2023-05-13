#include "mixText_asset.h"
namespace mix
{
    namespace assetsystem
    {
        mix::assetsystem::mixText_asset::mixText_asset (const mix::platform::mixAsset_path& path, std::string&& content)
        : mixAsset_item (path)
        {
            _content = std::move (content);
        }
        const std::string mixText_asset::get_content () const
        {
            return _content;
        }
    } // namespace assetsystem
} // namespace mix