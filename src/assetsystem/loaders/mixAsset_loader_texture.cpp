#include "mixAsset_loader_texture.h"

namespace mix
{
    namespace assetsystem
    {
        namespace loaders
        {
            mix::assetsystem::mixAsset_item* mixAsset_loader_texture::resolve_impl (mix::platform::mixFile& file)
            {
                auto type = mix::texture::texture_type::diffuse;
                if (file.get_name_without_extension ().rfind ("normal_") == 0)
                {
                    type = mix::texture::texture_type::normal;
                }
                return new mix::assetsystem::mixTexture (file.get_path (), type);
            }
        } // namespace loaders
    }     // namespace assetsystem
} // namespace mix