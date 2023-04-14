#pragma once
#include "../mixAsset_loader_base.h"
#include "../mixText_asset.h"

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
        namespace loaders
        {

            class mixAsset_loader_text : public mix::assetsystem::mixAsset_loader_base
            {
               
                protected:

                mix::assetsystem::mixAsset_item* resolve_impl (mix::platform::mixAsset_file& file) override;
            };
        }
    } // namespace assetsystem
} // namespace mix
