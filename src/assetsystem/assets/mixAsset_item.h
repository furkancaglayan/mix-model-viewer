#pragma once
#include "../../core/mixGuid.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "../../platform/mixAsset_path.h"

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
     

        class mixAsset_item
        {
            public:

            mixAsset_item (mix::platform::mixAsset_path&& path) noexcept;
            mixAsset_item (const mix::platform::mixAsset_path& path) noexcept;

            mix::core::mixGuid _guid;
           
            protected:

            mix::platform::mixAsset_path _path;

        };
    } // namespace assetsystem
} // namespace mix
