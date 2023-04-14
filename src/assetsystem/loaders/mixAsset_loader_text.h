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
                public:

                mixAsset_loader_text ()
                {
                }

               
                protected:

                mix::assetsystem::mixAsset_item* resolve_impl (const mix::platform::mixAsset_file& file) override
                {
                    return new mix::assetsystem::mixText_asset ();
                }

            };
        }
    } // namespace assetsystem
} // namespace mix
