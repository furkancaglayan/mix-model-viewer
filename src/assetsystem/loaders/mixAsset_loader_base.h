#pragma once
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "../assets/mixAsset_item.h"
#include "../../platform/mixFile.h"

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>

        class mixAsset_loader_base
        {
            public:

            inline mixAsset_item* resolve (mix::platform::mixFile& file)
            {
                return resolve_impl (file);
            }

            protected:

            virtual mixAsset_item* resolve_impl (mix::platform::mixFile& file);
        };


    } // namespace assetsystem
} // namespace mix
