#pragma once
#include "../assets/mixMesh.h"
#include "../assets/mixText_asset.h"
#include "mixAsset_loader_base.h"

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
        namespace loaders
        {

            class mixAsset_loader_texture : public mix::assetsystem::mixAsset_loader_base
            {
                public:

                mixAsset_loader_texture (mix::assetsystem::asset_processor* processor)
                : mixAsset_loader_base (processor)
                {

                }

                protected:

                mix::assetsystem::mixAsset_item* resolve_impl (mix::platform::mixFile& file) override;
            };
        } // namespace loaders
    }     // namespace assetsystem
} // namespace mix
