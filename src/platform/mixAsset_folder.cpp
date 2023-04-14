#include "mixAsset_folder.h"
#include <iostream>
#include "mixAsset_file.h"
namespace mix
{
    namespace platform
    {
        mixAsset_folder::mixAsset_folder (mixAsset_path&& path) : _path{ std::move (path) }
        {

        }
        mixAsset_folder::mixAsset_folder (std::string&& path)
        : _path{ mixAsset_path{ std::move (path) } }
        {

        }
        mixAsset_folder::mixAsset_folder (const std::string& path) : _path{ mixAsset_path{ path } }
        {
        }
    } // namespace platform
} // namespace mix