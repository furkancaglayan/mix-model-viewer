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

        /// <summary>
        /// Support multiple extensions
        /// </summary>
        /* class asset_postprocess_event_callback
        {
            using proc_call = event_callback_args<asset_processor, mixAsset_item>;

            public:

            asset_postprocess_event_callback (asset_processor* processor)
            {
                _callback = std::unique_ptr<proc_call> (proc_call::create_callback (processor, &asset_processor::post_process));
            }

            void operator() (mixAsset_item* asset)
            {
                _callback->operator() (asset);
            }

            private:

            std::unique_ptr<event_callback_args<asset_processor, mixAsset_item>> _callback;
        };*/

        class mixAsset_loader_base
        {

            public:


            mixAsset_loader_base ()
            {
                _postprocess_item_event = std::make_unique<mix::library::event<mixAsset_item>> ();
            }

            mixAsset_loader_base (mix::assetsystem::asset_processor* processor)
            {
                _postprocess_item_event = std::make_unique<mix::library::event<mixAsset_item>> ();
                set_asset_processor (processor);
            }

            inline mixAsset_item* resolve (mix::platform::mixFile& file)
            {
                auto item = resolve_impl (file);
                _postprocess_item_event->dispatch (item);
                return item;
            }

            void set_asset_processor (mix::assetsystem::asset_processor* processor)
            {
                assert (_asset_processor == nullptr);
                _asset_processor = std::unique_ptr<mix::assetsystem::asset_processor> (processor);


                auto callback = 
                event_callback_args<asset_processor, mixAsset_item>::create_callback (_asset_processor.get (),
                                                                                      &mix::assetsystem::asset_processor::post_process);
                _postprocess_item_event->add_listener (callback);
            }

            protected:

            std::unique_ptr<mix::library::event<mixAsset_item>> _postprocess_item_event;
            std::unique_ptr<mix::assetsystem::asset_processor> _asset_processor;
            virtual mixAsset_item* resolve_impl (mix::platform::mixFile& file) = 0;
        };


    } // namespace assetsystem
} // namespace mix
