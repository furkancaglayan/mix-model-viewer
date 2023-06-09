#include "mixAsset_loader_font.h"

mix::assetsystem::mixAsset_item* mix::assetsystem::loaders::mixAsset_loader_font::resolve_impl (mix::platform::mixFile& file)
{
    return new mix::assetsystem::mixFont(file.get_path());
}
