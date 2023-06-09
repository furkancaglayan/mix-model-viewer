#pragma once
#include "../assets/mixText_asset.h"
#include "mixAsset_loader_base.h"
#include "../assets/mixMesh.h"

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
                private:

                mix::assetsystem::mixMesh* load_obj (mix::platform::mixAsset_path path);
            };
        } // namespace loaders
    }     // namespace assetsystem
} // namespace mix
