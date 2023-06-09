#pragma once
#include "mixAsset_loader_base.h"
#include "../assets/mixFont.h"

namespace mix
{
    namespace assetsystem
    {
        namespace loaders
        {

            class mixAsset_loader_font : public mix::assetsystem::mixAsset_loader_base
            {
                protected:

                mix::assetsystem::mixAsset_item* resolve_impl (mix::platform::mixFile& file) override;
                bool save_impl (mix::platform::mixFile& file, mix::assetsystem::mixAsset_item* item) override;
            };
        } // namespace loaders
    }     // namespace assetsystem
} // namespace mix
