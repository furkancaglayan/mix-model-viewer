#include "asset_types.h"
#include "default_assets.h"
#include "../library/debug.h"

const mix::assetsystem::mixTexture* mix::assetsystem::default_assets::get_asset_default_icon (const std::string& ext)
{
    ASSERT (mixAsset_manager::instance != nullptr);
    auto name = asset_types::get_asset_default_icon_name (ext);
    auto asset = mixAsset_manager::instance->get_asset_with_base_name<mix::assetsystem::mixTexture> (name).get ();
    return asset;
}
