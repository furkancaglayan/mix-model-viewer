#pragma once

#include <string>

namespace mix
{
    namespace assetsystem
    {

        class asset_processor
        {
            public:
            virtual void post_process (mixAsset_item* asset) = 0;
        };
    } // namespace assetsystem
} // namespace mix
