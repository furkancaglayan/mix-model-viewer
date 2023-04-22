#include "mixAsset_manager.h"

namespace mix
{
    namespace assetsystem
    {
        mixAsset_manager* mixAsset_manager::instance = nullptr;
        mixAsset_manager::mixAsset_manager (std::unique_ptr<mix::assetsystem::mixAsset_folder> root)
        {
            instance = this;
            auto key = static_cast<std::string> (root->_guid);
            _assets = std::make_unique<asset_tree_val> (key, std::move (root));
        }

        mixAsset_manager::mixAsset_manager (std::string& root_path)
        {
            instance = this;
            auto root = std::make_unique<mix::assetsystem::mixAsset_folder> (root_path);
            auto key = static_cast<std::string> (root->_guid);
            _assets = std::make_unique<asset_tree_val> (key, std::move (root));
        }

        void mixAsset_manager::resolve_all_assets ()
        {
            auto root =
            static_cast<const mix::assetsystem::mixAsset_folder*> (static_cast<const mixAsset_item*> (_assets->get_value ()));
            resolve_assets_impl (root->get_path_as_str (), _assets.get());
        }

        //tree_node
        void mixAsset_manager::resolve_assets_impl (const std::string& p, asset_tree_ptr node)
        {
            //root->get_path_as_str ()
            auto all_paths =
            mix::platform::platform_utils::get_files (p, mix::platform::platform_utils::search_type::all);
            std::cout << "Resolving " << p << std::endl;
            for (auto path : all_paths)
            {
                if (mix::platform::platform_utils::is_folder(path))
                {
                    auto folder = std::make_unique<mix::assetsystem::mixAsset_folder> (path);
                    auto guid = static_cast<std::string> (folder->_guid);
                    auto new_node = node->insert (guid, std::move (folder));
                    //TODO: add path join
                    resolve_assets_impl (path, new_node);
                }
                else
                {
                    mix::platform::mixFile file{ path };
                    mixAsset_item* asset = mixAsset_manager::instance->resolve_asset (file);
                    auto guid = static_cast<std::string> (asset->_guid);
                    node->insert (guid, std::unique_ptr<mixAsset_item>{ asset });
                    std::cout << "\t Adding file " << path << std::endl;
                }
            }
        }
    } // namespace assetsystem
} // namespace mix