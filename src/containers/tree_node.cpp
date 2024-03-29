#include "tree_node.h"


mix::containers::tree_node* mix::containers::tree_node::insert (const mix::core::mixGuid& key,
                                                                std::shared_ptr<mix::assetsystem::mixAsset_item> child)
{
    size_t index = 0;
    for (; index < _children.size (); index++)
    {
        if (_children.at (index)->get_key () < key)
        {
            break;
        }
    }
    auto it = _children.insert (_children.begin () + index, std::make_unique<tree_node> (key, std::move (child), this));
    return _children.at (index).get ();
}
std::shared_ptr<mix::assetsystem::mixAsset_item> mix::containers::tree_node::search_with_guid (const mix::core::mixGuid& key) const
{
    return search_with_member<const mix::core::mixGuid&> (key, &mix::assetsystem::mixAsset_item::get_guid);
}

std::shared_ptr<mix::assetsystem::mixAsset_item> mix::containers::tree_node::search_with_base_name (const std::string& name) const
{
    return search_with_member<const std::string&> (name, &mix::assetsystem::mixAsset_item::get_base_name);
}
std::shared_ptr<mix::assetsystem::mixAsset_item> mix::containers::tree_node::search_with_full_name (const std::string& name) const
{
    return search_with_member<const std::string&> (name, &mix::assetsystem::mixAsset_item::get_full_name);
}
std::shared_ptr<mix::assetsystem::mixAsset_item> mix::containers::tree_node::search_with_path (const std::string& path) const
{
    return search_with_member<const std::string&> (path, &mix::assetsystem::mixAsset_item::get_path);
}

void mix::containers::tree_node::print_node (mix::containers::tree_node* node, int depth)
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
