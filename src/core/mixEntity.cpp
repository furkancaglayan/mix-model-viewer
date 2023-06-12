#include "mixEntity.h"
#include <iostream>

mix::core::mixEntity::mixEntity () : mixEntity ("Entity")
{
}

mix::core::mixEntity::mixEntity (vec3 pos) : mixEntity ("Entity", pos)
{
}

mix::core::mixEntity::mixEntity (std::string name) : mixEntity (name, vec3 (0))
{
}

mix::core::mixEntity::mixEntity (std::string name, vec3 pos) : _name{ name }
{
    _transform = std::make_unique<mix::core::mixTransform> (pos);
    _transform->set_position (pos);
}

void mix::core::mixEntity::add_component (mix::components::mixComponent* comp)
{
    _components.emplace_back (std::unique_ptr<mix::components::mixComponent> (comp));
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

void mix::core::mixEntity::render (mix::rendering::rendering_context* rendering)
{
    for (auto it = _components.cbegin (); it < _components.cend (); it++)
    {
        auto comp = (*it).get ();
        comp->render (rendering, static_cast<const mix::core::mixTransform*> (_transform.get ()));
    }

    for (auto it = _children.cbegin (); it < _children.cend (); it++)
    {
        auto ch = (*it).get ();
        ch->render (rendering);
    }
}

void mix::core::mixEntity::on_gui ()
{
    mixImGui::gui_layout::begin_vertical ();
    mixImGui::gui_layout::text_label (get_name ());
    mixImGui::gui_layout::begin_horizontal ();
    mixImGui::gui_layout::text_label ("Position: ");
    mixImGui::gui_layout::horizontal_space(10);

    auto pos = _transform->get_position();
    mixImGui::gui_layout::text_label ("X: ");
    mixImGui::gui_layout::text_label (std::to_string(pos.x));
    mixImGui::gui_layout::text_label ("Y: ");
    mixImGui::gui_layout::text_label (std::to_string (pos.y));
    mixImGui::gui_layout::text_label ("Z: ");
    mixImGui::gui_layout::text_label (std::to_string (pos.z));
    mixImGui::gui_layout::end_horizontal ();
    mixImGui::gui_layout::end_vertical ();
}

void mix::core::mixEntity::on_inspector_gui ()
{
}

void mix::core::mixEntity::on_scene_gui ()
{
}

std::string mix::core::mixEntity::get_gui_name ()
{
    return get_name ();
}
