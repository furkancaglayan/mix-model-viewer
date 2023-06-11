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


            const static mix::assetsystem::mixTexture* get_asset_default_icon (const std::string& ext)
            {
                assert (mixAsset_manager::instance);
                auto name = asset_types::get_asset_default_icon_name (ext);
                auto asset = mixAsset_manager::instance->get_asset_with_base_name<mix::assetsystem::mixTexture> (name).get ();
                return asset;
            };

            private:
        };
    } // namespace assetsystem
} // namespace mix
