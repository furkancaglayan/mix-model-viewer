#pragma once
#include "../platform/mixAsset_file.h"
#include "mixAsset_item.h"
#include <stdexcept>
#include <functional>
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

            template <class T> T* resolve (mix::platform::mixAsset_file& file)
            {
                mixAsset_item* item = resolve_impl (file);
                T* asset = static_cast<T*> (item);
                return asset;
            }

            protected:

            virtual mixAsset_item* resolve_impl (mix::platform::mixAsset_file& file)
            {
                throw std::invalid_argument ("This shouldn't be called");
            }
        };

    } // namespace assetsystem
} // namespace mix
