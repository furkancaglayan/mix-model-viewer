#include "mixAsset_loader_base.h"

namespace mix
{
    namespace assetsystem
    {
        mixAsset_loader_base::mixAsset_loader_base ()
        {
            _postprocess_item_event = std::make_unique<mix::library::event<mixAsset_item>> ();
        }
    } // namespace assetsystem
} // namespace mix