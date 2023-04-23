#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "../algorithms/binary_search.h"
namespace mix
{
    namespace containers
    {
        using mix::algorithms::search;

        template <class Key, class T> class tree_node
        {
            public:

            tree_node (Key key, std::unique_ptr<T> value) : _key{ key }, _value{ std::move (value) }
            {
            }

            tree_node<Key, T>* insert (Key key, std::unique_ptr<T> child)
            {
                size_t index = 0;
                for (; index < _children.size (); index++)
                {
                    if (_children.at (index)->get_key () < key)
                    {
                        break;
                    }
                }
                auto it = _children.insert (_children.begin () + index, std::make_unique<tree_node> (key, std::move (child)));
                return _children.at (index).get();
            }


            tree_node<Key, T>* search (const Key& key) const
            {
                size_t pos;
                if (search::binary_search (
                    _children.begin (), _children.end (), key,
                    [] (std::unique_ptr<T> n, const Key& key) { return n->get_key () < key; }, pos))
                {

                }
                else
                {
                    return nullptr;
                }
            }

            inline bool has_children () const
            {
                return _children.size ();
            }

            inline const Key& get_key () const
            {
                return _key;
            }

            inline const T* get_value () const
            {
                return _value.get ();
            }

            inline void print ()
            {
                print_node (this, 0);
            }

            private:

            static void print_node (tree_node* node, int depth)
            {
                std::cout << std::string (depth * 2, '-');
                if (depth > 0)
                {
                    std::cout << '>';
                }
                auto val = (*node->_value.get ());
                std::cout << (std::string) val << std::endl;

                for (size_t i = 0; i < node->_children.size (); i++)
                {
                    print_node (node->_children.at (i).get (), depth + 1);
                }
            }

            Key _key;
            std::unique_ptr<T> _value;
            std::vector<std::unique_ptr<tree_node>> _children;
        };
    } // namespace containers
} // namespace mix
