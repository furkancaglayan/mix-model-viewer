#pragma once
#include "mixAsset_path.h"
#include <memory>
#include <string>
#include <vector>

namespace mix
{
    namespace platform
    {
        class mixFolder
        {
            public:

            mixFolder (mixAsset_path&& path);
            mixFolder (std::string&& path);
            mixFolder (const std::string& path);

            inline const std::string get_name () const
            {
                return _path.get_name_without_extension ();
            }

            inline const std::string get_path () const
            {
                return _path.to_str ();
            }

            private:

            mixAsset_path _path;
        };
    }; // namespace platform
} // namespace mix
