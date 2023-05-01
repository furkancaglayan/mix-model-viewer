#pragma once
#include "../algorithms/binary_search.h"
#include "../assetsystem/assets/mixAsset_item.h"
#include "../core/mixGuid.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
namespace mix
{
    namespace containers
    {
        using mix::algorithms::search;

        class tree_node
        {
            public:

            tree_node (mix::core::mixGuid key, std::shared_ptr<mix::assetsystem::mixAsset_item> value)
            : _key{ key }, _value{ std::move (value) }
            {
            }

            tree_node* insert (const mix::core::mixGuid& key, std::shared_ptr<mix::assetsystem::mixAsset_item> child);
            mix::assetsystem::mixAsset_item* search_with_guid (const mix::core::mixGuid& key) const;
            mix::assetsystem::mixAsset_item* search_with_base_name (const std::string& name) const;
            mix::assetsystem::mixAsset_item* search_with_full_name (const std::string& name) const;


            inline bool has_children () const
            {
                return _children.size ();
            }

            inline const mix::core::mixGuid& get_key () const
            {
                return _key;
            }

            inline const mix::assetsystem::mixAsset_item* get_value () const
            {
                return _value.get ();
            }

            inline void print ()
            {
                print_node (this, 0);
            }

            private:

            template <class T>
            mix::assetsystem::mixAsset_item* search_with_member (T val, T (mix::assetsystem::mixAsset_item::*getter) (void) const) const
            {
                auto s = std::invoke (getter, _value.get ());
                if (val == s)
                {
                    return _value.get ();
                }

                for (auto&& node : _children)
                {
                    auto s = std::invoke (getter, node->_value.get ());

                    if (val == s)
                    {
                        return node->_value.get ();
                    }

                    auto found = node->search_with_member<T> (val, getter);
                    if (found)
                    {
                        return found;
                    }
                }

                return nullptr;
            }
            static void print_node (tree_node* node, int depth);
            mix::core::mixGuid _key;
            std::shared_ptr<mix::assetsystem::mixAsset_item> _value;
            std::vector<std::unique_ptr<tree_node>> _children;
        };
    } // namespace containers
} // namespace mix
