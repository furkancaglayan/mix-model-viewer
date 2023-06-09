#pragma once
#include "../../platform/mixFile.h"
#include "../assets/mixAsset_item.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "../../library/event.h"
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

            mixAsset_loader_base ();
            inline mixAsset_item* resolve (mix::platform::mixFile& file)
            {
                auto item = resolve_impl (file);
                _postprocess_item_event->dispatch (item);
                return item;
            }

            protected:

            std::unique_ptr<mix::library::event<mixAsset_item>> _postprocess_item_event;
            virtual mixAsset_item* resolve_impl (mix::platform::mixFile& file) = 0;
        };


    } // namespace assetsystem
} // namespace mix
