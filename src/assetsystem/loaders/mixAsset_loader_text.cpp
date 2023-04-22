#include "mixAsset_loader_text.h"

namespace mix
{
    namespace assetsystem
    {
        namespace loaders
        {
            mix::assetsystem::mixAsset_item* mixAsset_loader_text::resolve_impl (mix::platform::mixFile& file)
            {
                return new mixText_asset (file._path, file.read_all_text ());
            }
        } // namespace loaders
    } // namespace assetsystem
} // namespace mix