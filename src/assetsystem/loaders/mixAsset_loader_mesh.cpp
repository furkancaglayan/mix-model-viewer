#include "mixAsset_loader_mesh.h"

namespace mix
{
    namespace assetsystem
    {
        namespace loaders
        {
            mix::assetsystem::mixAsset_item* mixAsset_loader_mesh::resolve_impl (mix::platform::mixFile& file)
            {
                return new mix::assetsystem::mixText_asset (file.get_name_without_extension (), file.read_all_text ());
            }
        } // namespace loaders
    } // namespace assetsystem
} // namespace mix