#include "mixAsset_loader_base.h"


mix::assetsystem::mixAsset_loader_base::mixAsset_loader_base ()
{
    _postprocess_item_event = std::make_unique<mix::library::event<mixAsset_item>> ();
}

mix::assetsystem::mixAsset_loader_base::mixAsset_loader_base (mix::assetsystem::asset_processor* processor)
{
    _postprocess_item_event = std::make_unique<mix::library::event<mixAsset_item>> ();
    set_asset_processor (processor);
}

mix::assetsystem::mixAsset_item* mix::assetsystem::mixAsset_loader_base::resolve (mix::platform::mixFile& file)
{
    auto item = resolve_impl (file);
    _postprocess_item_event->dispatch (item);
    return item;
}

void mix::assetsystem::mixAsset_loader_base::set_asset_processor (mix::assetsystem::asset_processor* processor)
{
    if (_asset_processor != nullptr)
    {
        _asset_processor.reset ();
    }

    _asset_processor = std::unique_ptr<mix::assetsystem::asset_processor> (processor);
    // TODO: FiX remove behabior
    auto callback =
    event_callback_args<asset_processor, mixAsset_item>::create_callback (_asset_processor.get (),
                                                                          &mix::assetsystem::asset_processor::post_process);
    _postprocess_item_event->add_listener (callback);
}
