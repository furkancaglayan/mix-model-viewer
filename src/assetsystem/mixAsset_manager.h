#pragma once


#include "../containers/tree_node.h"
#include "../platform/mixFile.h"
#include "asset_types.h"
#include "assets/mixAsset_folder.h"
#include "assets/mixAsset_item.h"
#include "loaders/mixAsset_loader_base.h"
#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>

        using asset_tree =
        std::unique_ptr<mix::containers::tree_node<std::string, mix::assetsystem::mixAsset_item>>;
        using asset_tree_val = mix::containers::tree_node<std::string, mix::assetsystem::mixAsset_item>;
        using asset_tree_ptr = asset_tree_val*;

        class mixAsset_manager
        {

            public:

            mixAsset_manager (std::unique_ptr<mix::assetsystem::mixAsset_folder> root);
            mixAsset_manager (std::string& root_path);
            static mixAsset_manager* instance;
            template <class T> void register_loader (asset_type type)
            {
                assert (!_loaders.count (type));
                _loaders.insert ({ type, std::make_unique<T> () });
            }

            inline mix::assetsystem::mixAsset_loader_base* get_loader (const asset_type& type) const noexcept
            {
                return _loaders.at (type).get ();
            }

            inline mixAsset_item* resolve_asset (mix::platform::mixFile& file) const noexcept
            {
                mix::assetsystem::mixAsset_loader_base* loader = get_loader (file.get_asset_type ());
                return loader->resolve (file);
            }

            inline void debug ()
            {
                _assets->print ();
            }

            void resolve_all_assets ();
            private:

            static void resolve_assets_impl (const std::string& p, asset_tree_ptr node);

            std::unordered_map<asset_type, std::unique_ptr<mix::assetsystem::mixAsset_loader_base>> _loaders;
            asset_tree _assets;
        };


    } // namespace assetsystem
} // namespace mix
