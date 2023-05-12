#include "mixEntity.h"
#include "mixCamera.h"


mix::core::mixEntity::mixEntity () : mixEntity ("Entity", vec3 (0))
{
}

mix::core::mixEntity::mixEntity (vec3 pos) : mixEntity ("Entity", pos)
{
}

mix::core::mixEntity::mixEntity (std::string name) : mixEntity (name, vec3 (0))
{
}

mix::core::mixEntity::mixEntity (std::string name, vec3 pos) : _name{ "Entity" }
{
    _transform = std::make_unique<mix::core::mixTransform> (pos);
    _transform->set_position (pos);
}

void mix::core::mixEntity::add_component (std::unique_ptr<mixComponent> comp)
{
    _components.emplace_back (std::move (comp));
}

void mix::core::mixEntity::add_component (mixComponent* comp)
{
    add_component (std::unique_ptr<mixComponent> (comp));
}

void mix::core::mixEntity::add_child (std::shared_ptr<mixEntity> ch)
{
    _children.emplace_back (std::move (ch));
}

std::string mix::core::mixEntity::get_name () const
{
    return _name;
}

mix::core::mixEntity* mix::core::mixEntity::get_parent () const
{
    if (_parent.expired())
    {
        return nullptr;
    }

    return _parent.lock ().get ();
}

std::vector<std::shared_ptr<mix::core::mixEntity>> mix::core::mixEntity::get_children () const
{
    return _children;
}

void mix::core::mixEntity::set_name (std::string name)
{
    _name = name;
}

void mix::core::mixEntity::update ()
{
    _transform->update ();

    for (auto it = _components.cbegin (); it < _components.cend (); it++)
    {
        auto comp = (*it).get ();
        comp->update ();
    }
    
    
    for (auto it = _children.cbegin (); it < _children.cend (); it++)
    {
        auto ch = (*it).get ();
        ch->update ();
    }
}

void mix::core::mixEntity::render ()
{
    for (auto it = _components.cbegin (); it < _components.cend (); it++)
    {
        auto comp = (*it).get ();
        comp->render ();
    }
}
