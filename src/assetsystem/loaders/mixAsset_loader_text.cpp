#include "mixAsset_loader_text.h"

namespace mix
{
    namespace assetsystem
    {
        namespace loaders
        {
            mix::assetsystem::mixAsset_item* mixAsset_loader_text::resolve_impl (mix::platform::mixFile& file)
            {
                return new mixText_asset (file._path, file.read_all_text ());
            }

            bool mixAsset_loader_text::save_impl (mix::platform::mixFile& file, mix::assetsystem::mixAsset_item* item)
            {
                auto t = static_cast<mix::assetsystem::mixText_asset*> (item);
                auto text = t->get_content ();
                return file.write (text);
            }
        } // namespace loaders
    } // namespace assetsystem
} // namespace mix