#include "mixAsset_loader_base.h"

namespace mix
{
    namespace assetsystem
    {
        mixAsset_item* mixAsset_loader_base::resolve_impl (mix::platform::mixAsset_file& file)
        {
            throw std::invalid_argument ("This shouldn't be called");
        }

    } // namespace assetsystem
} // namespace mix