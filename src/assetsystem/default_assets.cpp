#include "asset_types.h"
#include "default_assets.h"
#include "../library/debug.h"

const mix::assetsystem::mixTexture* mix::assetsystem::default_assets::get_asset_default_icon (const mix::assetsystem::mixAsset_item* item)
{
    ASSERT (mixAsset_manager::instance != nullptr);
    if (const mix::assetsystem::mixTexture* t = dynamic_cast<const mix::assetsystem::mixTexture*>(item))
    {
        return t;
    }
    auto name = asset_types::get_asset_default_icon_name (item->get_extension());
    auto asset = mixAsset_manager::instance->get_asset_with_base_name<mix::assetsystem::mixTexture> (name).get ();
    return asset;
}
