#pragma once

#include <string>
#include "../assets/mixAsset_item.h"
#include "../asset_processor.h"
namespace mix
{
    namespace assetsystem
    {
        namespace default_processors
        {
            class default_texture_processor : public asset_processor
            {
                public:

                void post_process (mixAsset_item* asset) override;
            };
        }
    } // namespace assetsystem
} // namespace mix
