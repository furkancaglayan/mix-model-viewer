#include "mixAsset_manager.h"

namespace mix
{
    namespace assetsystem
    {
        mixAsset_manager::mixAsset_manager (std::string&& root)
        : _root{ std::make_unique<mix::platform::mixFolder> (std::move (root)) }
        {

        }
        mixAsset_manager::mixAsset_manager (const std::string& root)
        : _root{ std::make_unique<mix::platform::mixFolder> (root) }
        {

        }

        void mixAsset_manager::resolve_all ()
        {
            std::vector<std::string> all_paths;
            mix::platform::platform_utils::get_all_dfs (_root->get_path (), all_paths);

            for (auto path : all_paths)
            {
                if (mix::platform::platform_utils::is_folder(path))
                {
                
                }
                else
                {
                    mix::platform::mixFile file{ path };
                    mixAsset_item* asset = resolve_asset (file);
                }
            }
        }

    } // namespace assetsystem
} // namespace mix