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

            template <class T> T* resolve (const mix::platform::mixAsset_file& file)
            {
                std::string ext = file.get_extension ();
                mixAsset_item* item = resolve_impl (file);
                T* childPtr = static_cast<T*> (item);
                return childPtr;
            }

            protected:

            virtual mixAsset_item* resolve_impl (const mix::platform::mixAsset_file& file)
            {
                throw std::invalid_argument ("This shouldn't be called");
            }
        };

    } // namespace assetsystem
} // namespace mix
