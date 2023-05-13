#pragma once
#include "../assets/mixMesh.h"
#include "../assets/mixText_asset.h"
#include "mixAsset_loader_base.h"

namespace mix
{
    namespace assetsystem
    {
        namespace loaders
        {
            class mixAsset_loader_shader : public mix::assetsystem::mixAsset_loader_base
            {
                protected:

                mix::assetsystem::mixAsset_item* resolve_impl (mix::platform::mixFile& file) override;
                bool save_impl (mix::platform::mixFile& file, mix::assetsystem::mixAsset_item* item) override;
            };
        } // namespace loaders
    }     // namespace assetsystem
} // namespace mix
