#include "mixAsset_manager.h"
#include "default_processors/default_texture_processor.h"
#include "loaders/mixAsset_loader_font.h"
#include "loaders/mixAsset_loader_mesh.h"
#include "loaders/mixAsset_loader_shader.h"
#include "loaders/mixAsset_loader_text.h"
#include "loaders/mixAsset_loader_texture.h"
#include "../library/debug.h"

namespace mix
{
    namespace assetsystem
    {
        mixAsset_manager* mixAsset_manager::instance = nullptr;
        mixAsset_manager::mixAsset_manager (std::unique_ptr<mix::assetsystem::mixAsset_folder> root)
        {
            instance = this;
            _assets = std::make_unique<asset_tree_val> (root->get_guid (), std::move (root), nullptr);
            initialize_default_asset_loaders ();
            resolve_all_assets ();
            debug ();
        }

        mixAsset_manager::mixAsset_manager (std::string& root_path)
        {
            instance = this;
            auto root = std::make_unique<mix::assetsystem::mixAsset_folder> (root_path);
            _assets = std::make_unique<asset_tree_val> (root->get_guid (), std::move (root), nullptr);
            initialize_default_asset_loaders ();
            resolve_all_assets ();
            debug ();
        }

        const mix::assetsystem::mixAsset_folder* mixAsset_manager::get_root_folder () const
        {
            return static_cast<const mix::assetsystem::mixAsset_folder*> (_assets->get_value ());
        }

        const asset_tree_ptr mixAsset_manager::get_root_node () const
        {
            return _assets.get ();
        }

        void mixAsset_manager::resolve_all_assets ()
        {
            INFO (mixAsset_manager::resolve_all_assets);
            auto root =
            static_cast<const mix::assetsystem::mixAsset_folder*> (static_cast<const mixAsset_item*> (_assets->get_value ()));
            resolve_assets_impl (root->get_path_as_str (), _assets.get ());
        }

        // tree_node
        void mixAsset_manager::resolve_assets_impl (const std::string& p, asset_tree_ptr node)
        {
            // root->get_path_as_str ()
            auto all_paths = mix::platform::platform_utils::get_files (p, mix::platform::platform_utils::search_type::all);
            DEBUG_LOG ("Resolving asset: " + p);

            for (auto path : all_paths)
            {
                if (mix::platform::platform_utils::is_folder (path))
                {
                    auto folder = std::make_shared<mix::assetsystem::mixAsset_folder> (path);
                    auto guid = folder->get_guid ();
                    auto new_node = node->insert (guid, std::move (folder));
                    // TODO: add path join
                    resolve_assets_impl (path, new_node);
                }
                else
                {
                    mix::platform::mixFile file{ path };
                    mixAsset_item* asset = mixAsset_manager::instance->resolve_asset (file);
                    node->insert (asset->get_guid (), std::shared_ptr<mixAsset_item>{ asset });
                    DEBUG_LOG ("\t Adding file: " + path);
                }
            }
        }

        void mixAsset_manager::initialize_default_asset_loaders ()
        {
            register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Text);
            register_loader<mix::assetsystem::loaders::mixAsset_loader_texture> (
            mix::assetsystem::asset_type::Texture, new mix::assetsystem::default_processors::default_texture_processor ());
            register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Material);
            register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Mesh);
            register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Other);
            register_loader<mix::assetsystem::loaders::mixAsset_loader_shader> (mix::assetsystem::asset_type::Shader);
            register_loader<mix::assetsystem::loaders::mixAsset_loader_font> (mix::assetsystem::asset_type::Font);
        }
    } // namespace assetsystem
} // namespace mix