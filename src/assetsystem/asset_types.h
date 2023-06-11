#pragma once

#include <string>
#include <unordered_map>

namespace mix
{
    namespace assetsystem
    {
        enum class asset_type
        {
            Text,
            Font,
            Mesh,
            Shader,
            Folder,
            Material,
            Texture,
            Other
        };


        class asset_types
        {
            asset_types () = delete;

            public:

            const static asset_type get_asset_type (const std::string& ext)
            {
                if (extension_map.count (ext))
                {
                    return extension_map.at (ext);
                }

                return asset_type::Other;
            };


            const static std::string get_asset_default_icon_name (const std::string& ext)
            {
                if (extension_map.count (ext))
                {
                    return "default_" + ext;
                }

                return "default_other";
            };

            private:

            const static std::unordered_map<std::string, asset_type> extension_map;
        };
    } // namespace assetsystem
} // namespace mix
