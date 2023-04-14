#pragma once
#include "mixAsset_path.h"
#include <memory>
#include <string>
#include <vector>

namespace mix
{
    namespace platform
    {
        class mixAsset_folder
        {
            public:

            mixAsset_folder (mixAsset_path&& path);
            mixAsset_folder (std::string&& path);
            mixAsset_folder (const std::string& path);

            inline const std::string get_name () const
            {
                return _path.get_name_without_extension ();
            }

            private:

            mixAsset_path _path;
        };
    }; // namespace platform
} // namespace mix
