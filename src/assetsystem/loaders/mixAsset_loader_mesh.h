#pragma once
#include "mixAsset_loader_base.h"
#include "../assets/mixText_asset.h"

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
        namespace loaders
        {

            class mixAsset_loader_mesh : public mix::assetsystem::mixAsset_loader_base
            {
                protected:
                mix::assetsystem::mixAsset_item* resolve_impl (mix::platform::mixFile& file) override;
            };
        }
    } // namespace assetsystem
} // namespace mix
