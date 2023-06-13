#pragma once
#include "../../library/event.h"
#include "../../library/event_callback.h"
#include "../../platform/mixFile.h"
#include "../asset_processor.h"
#include "../assets/mixAsset_item.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace mix
{
    namespace assetsystem
    {
        using namespace mix::library;
        using namespace mix::assetsystem;

        class mixAsset_loader_base
        {

            public:

            mixAsset_loader_base ();
            mixAsset_loader_base (mix::assetsystem::asset_processor* processor);

            mixAsset_item* resolve (mix::platform::mixFile& file);
            void set_asset_processor (mix::assetsystem::asset_processor* processor);

            protected:

            std::unique_ptr<mix::library::event<mixAsset_item>> _postprocess_item_event;
            std::unique_ptr<mix::assetsystem::asset_processor> _asset_processor;
            virtual mixAsset_item* resolve_impl (mix::platform::mixFile& file) = 0;
        };


    } // namespace assetsystem
} // namespace mix
