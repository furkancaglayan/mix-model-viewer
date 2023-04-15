#pragma once



#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include "assets/mixAsset_item.h"
#include "loaders/mixAsset_loader_base.h"
#include "asset_types.h"
#include "../platform/mixFile.h"
#include "../platform/mixFolder.h"

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>

        class mixAsset_manager
        {
            class mixAsset_map
            {
                public:

                size_t get_size () const
                {
                    // return _map.size ();
                }

                std::shared_ptr<mixAsset_item> get (const mix::core::mixGuid& guid)
                {
                    // return _map.at(guid);
                }

                inline void add (std::shared_ptr<mixAsset_item>&& t) noexcept
                {
                    //_map.insert ({ t->_guid, t });
                }

                private:

                std::unordered_map<mix::core::mixGuid, mix::core::mixGuid> _map;
            };


            public:

            mixAsset_manager (std::string&& root);
            mixAsset_manager (const std::string& root);


            template <class T> void add_asset_map ()
            {
                auto index = std::type_index{ typeid (T) };
                _maps.insert ({ index, std::make_unique<mixAsset_map> () });
            }

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
                mix::assetsystem::mixAsset_loader_base* loader = get_loader (file.get_asset_type());
                return loader->resolve (file);
            }

            void resolve_all ();
            
        private:


            std::unordered_map<std::type_index, std::unique_ptr<mixAsset_map>> _maps;
            std::unordered_map<asset_type, std::unique_ptr<mix::assetsystem::mixAsset_loader_base>> _loaders;
            //Use multimap and bind to extensions instead
            std::unique_ptr<mix::platform::mixFolder> _root;
        };


    } // namespace assetsystem
} // namespace mix
