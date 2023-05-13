#pragma once
#include "../../platform/mixFile.h"
#include "../assets/mixAsset_item.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

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
            inline bool save (mix::platform::mixFile& file, mixAsset_item* item)
            {
                return save_impl (file, item);
            }

            protected:

            virtual mixAsset_item* resolve_impl (mix::platform::mixFile& file) = 0;
            virtual bool save_impl (mix::platform::mixFile& file, mixAsset_item* item) = 0;
        };


    } // namespace assetsystem
} // namespace mix
