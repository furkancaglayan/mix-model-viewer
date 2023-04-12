#pragma once
#include "../platform/mixAsset_folder.h"
#include "mixAsset_item.h"
#include "mixAsset_loader_base.h"
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <typeindex>

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
                    return _map.size ();
                }

                std::shared_ptr<mixAsset_item> get (const std::string& name)
                {
                    for (size_t i = 0; i < _map.size (); i++)
                    {
                        /* if (_map[i].lock ()->get_content ().compare (name) == 0)
                        {
                            return _map[i];
                        }*/
                    }
                }

                inline void add (std::shared_ptr<mixAsset_item>&& t) noexcept
                {
                    _map.emplace_back (std::move (t));
                }
                private:

                std::vector<std::shared_ptr<mixAsset_item>> _map;
            };

            public:

            mixAsset_manager (std::string&& root)
            : _root{ std::make_unique<mix::platform::mixAsset_folder> (std::move (root)) }
            {
            }
            template <class T> void add_asset_map ()
            {
                auto index = std::type_index{ typeid (T) };
                auto map = std::make_shared<mixAsset_map>();
                _maps.insert ({ index, map });
            }

            template <class T> void add_asset (T&& t) noexcept
            {
                auto index = std::type_index{ typeid (T) };
                if (_maps.count (index))
                {
                    mixAsset_map t = static_cast<mixAsset_map> ((_maps[index])->get ());
                    t->add (t);
                }
                else
                {
                    add_asset_map<T> ();
                    add_asset (t);
                }
            }
            template <typename T> std::shared_ptr<T> get_asset (const std::string& name) const
            {
                auto index = std::type_index{ typeid (T) };
                mixAsset_map t = static_cast<mixAsset_map> ((_maps[index])->get ());
                return t.get (name);
            }

            template <typename Ttype_l, class Ttype_I> void register_loader ()
            {
                auto index = std::type_index{ typeid (Ttype_l) };
                assert (!_loaders[index]);
                _loaders[index] = std::make_unique<Ttype_I> ();
            }

            template <class T> std::shared_ptr<mix::assetsystem::mixAsset_loader_base> get_loader ()
            {
                auto index = std::type_index{ typeid (T) };
                return _loaders[index];
            }

            private:

            std::map<std::type_index, std::shared_ptr<mixAsset_map>> _maps;
            std::map<std::type_index, std::shared_ptr<mix::assetsystem::mixAsset_loader_base>> _loaders;

            std::unique_ptr<mix::platform::mixAsset_folder> _root;
        };

    } // namespace assetsystem
} // namespace mix
