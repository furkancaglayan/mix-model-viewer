#pragma once

#include <string>
#include "mixAsset_manager.h"
#include "assets/mixTexture.h"

namespace mix
{
    namespace assetsystem
    {

        class default_assets
        {
            default_assets () = delete;

            public:

            const static mix::assetsystem::mixTexture* get_asset_default_icon (const std::string& ext);

            private:
        };
    } // namespace assetsystem
} // namespace mix
