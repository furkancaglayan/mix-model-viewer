#include "mixAsset_folder.h"
#include <iostream>
namespace mix
{
    namespace platform
    {
        void mixAsset_folder::collect ()
        {
            auto dirs = platform_utils::get_directories (_path);
        }
    } // namespace assetsystem
} // namespace mix