#include "mixAsset_manager.h"
#include "mixAsset_item.h"

namespace mix
{
    namespace assetsystem
    {
        void mix::assetsystem::mixAsset_item::construct_from (mix::platform::mixAsset_file file)
        {
            auto content = file.get_content ();
        }
    } // namespace assetsystem
} // namespace mix