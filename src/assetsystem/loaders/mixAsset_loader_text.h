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

                mix::assetsystem::mixAsset_item* resolve_impl (mix::platform::mixAsset_file& file) override
                {
                    return new mixText_asset (file.get_name_without_extension (), file.read_all_text ());
                }
            };
        }
    } // namespace assetsystem
} // namespace mix
