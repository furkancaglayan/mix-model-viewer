#include "mixFolder.h"
namespace mix
{
    namespace platform
    {
        mixFolder::mixFolder (mixAsset_path&& path) : _path{ std::move (path) }
        {

        }
        mixFolder::mixFolder (std::string&& path)
        : _path{ mixAsset_path{ std::move (path) } }
        {

        }
        mixFolder::mixFolder (const std::string& path) : _path{ mixAsset_path{ path } }
        {
        }
    } // namespace platform
} // namespace mix