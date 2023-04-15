#include "asset_types.h"

namespace mix
{
    namespace assetsystem
    {


        const std::unordered_map<std::string, asset_type> asset_types::extension_map = {
            { "txt", asset_type::Text },    { "xml", asset_type::Text },    { "json", asset_type::Text },

            { "obj", asset_type::Mesh },    { "fbx", asset_type::Mesh },

            { "png", asset_type::Texture }, { "jpg", asset_type::Texture },

            { "vs", asset_type::Shader },   { "fs", asset_type::Shader },

        };

    };
} // namespace mix
