#pragma once


#include "mixAsset_loader_base.h"
#include "../platform/mixAsset_folder.h"

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

            mixAsset_manager (std::string&& root)
            : _root{ std::make_unique<mix::platform::mixAsset_folder> (std::move (root)) }
            {
            }


            template <class T> void add_asset_map ()
            {
                auto index = std::type_index{ typeid (T) };
                _maps.insert ({ index, std::make_unique<mixAsset_map> () });
            }

            template <class T> bool load_asset (const mix::platform::mixAsset_file& file) noexcept;

            template <typename Ttype_l, class Ttype_I> void register_loader ()
            {
                auto index = std::type_index{ typeid (Ttype_l) };
                assert (!_loaders.count(index));
                _loaders.insert ({ index, std::make_unique<Ttype_I> () });
            }

            template <class T> mix::assetsystem::mixAsset_loader_base* get_loader () const noexcept
            {
                std::type_index index = std::type_index{ typeid (T) };
                return _loaders.at (index).get();
            }

            template <class T> T* resolve_asset (const mix::platform::mixAsset_file& file) noexcept
            {
                mix::assetsystem::mixAsset_loader_base* loader = get_loader<T> ();
                return loader->resolve<T> (file);
            }

            private:


            std::unordered_map<std::type_index, std::unique_ptr<mixAsset_map>> _maps;
            std::unordered_map<std::type_index, std::unique_ptr<mix::assetsystem::mixAsset_loader_base>> _loaders;

            std::unique_ptr<mix::platform::mixAsset_folder> _root;
        };


    } // namespace assetsystem
} // namespace mix
