#pragma once
#include <memory>
#include <string>
#include "mixAsset_item.h"

namespace mix
{
    namespace assetsystem
    {
        class mixText_asset : public mix::assetsystem::mixAsset_item
        {

            public:

            mixText_asset (const mix::platform::mixAsset_path& path, std::string&& content);

            const std::string get_content () const;
            private:

            std::string _content;
        };
    } // namespace assetsystem
} // namespace mix
