#include "default_texture_processor.h"
#include "../assets/mixTexture.h"

void mix::assetsystem::default_processors::default_texture_processor::post_process (mixAsset_item* asset)
{
    auto texture = static_cast<mixTexture*> (asset);

    if (texture->get_extension () == "png")
    {
        texture->set_format (mix::texture::texture_format::rgb_alpha);
    }
}