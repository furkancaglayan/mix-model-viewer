#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "../platform/typedefs.h"

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

                /*
                size_t get_size () const
                {
                    return _map.size ();
                }

                std::weak_ptr<mixAsset_base> get (const std::string& name)
                {
                    for (size_t i = 0; i < _map.size(); i++)
                    {
                        if (_map[i].lock()->get_content().compare(name) == 0)
                        {
                            return _map[i];
                        }
                    }
                }

                inline void add (std::shared_ptr<mixAsset_base> t)
                {
                    _map.emplace_back (t);
                }
                private:

                std::vector<std::weak_ptr<mixAsset_base>> _map;*/
            };
            public:

            mixAsset_manager (std::string&& root)
            : _root{ std::make_unique<mix::platform::mixAsset_folder> (std::move(root), nullptr) }
            {
            
            }
            template <typename T> void add_asset_map ();
            template <typename T> void add_asset (T t);
            template <typename T> T get_asset (const std::string& name) const;

            void load ();
            void load_async ();

            private:

            std::map<std::type_info, std::unique_ptr<mixAsset_map>> _maps;
            std::unique_ptr<mix::platform::mixAsset_folder> _root;

        };
    } // namespace core
} // namespace mix
