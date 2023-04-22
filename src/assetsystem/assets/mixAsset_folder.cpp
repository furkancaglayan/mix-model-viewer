#include "mixAsset_folder.h"

mix::assetsystem::mixAsset_folder::mixAsset_folder (mix::platform::mixAsset_path&& path) noexcept
: mixAsset_item (path), _path{ path }
{
}

mix::assetsystem::mixAsset_folder::mixAsset_folder (const mix::platform::mixAsset_path& path) noexcept
: mixAsset_item (path), _path{ path }
{
}
