#include "hierarchy_window.h"

void mix::editor::windows::hierarchy_window::render ()
{
    auto scene = mix::mixEditor::_instance->get_active_scene ();
    if (scene)
    {
        set_title (scene->get_root ()->get_name ());
        begin ();

        gui_layout::begin_vertical ();
        gui_layout::collapsing_label ("Objects", &_visible_entities);

        if (_visible_entities)
        {
            auto children = scene->get_root ()->get_children ();

            for (size_t i = 0; i < children.size (); i++)
            {
                render_entity (children.at (i).get (), static_cast<int> (i));
            }
        }
        else
        {
            _selected_entity = -1;
        }

        gui_layout::end_vertical ();
        end ();
    }
}

void mix::editor::windows::hierarchy_window::on_editor_window_size_changed_impl (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.75f;
    auto WINDOW_SIZE = 0.25f;
    auto width = size.x * WINDOW_SIZE;
    rescale (vec2i (width, static_cast<float> (size.y)));
    set_position (vec2i (size.x * WINDOW_BEGIN_POS, 0));
}

mix::editor::windows::hierarchy_window::hierarchy_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::MenuBar | mixImGui::window_flags::NoCollapse |
                        mixImGui::window_flags::NoMove | mixImGui::window_flags::NoResize)

{
}

mix::editor::windows::hierarchy_window::~hierarchy_window ()
{
}

void mix::editor::windows::hierarchy_window::initialize (const vec2i& size)
{
    // TODO: MAKE ALL INT ARGUMENTS AS W, H TO VEC2
    auto WINDOW_BEGIN_POS = 0.75f;
    auto WINDOW_SIZE = 0.25f;
    auto rect = mixImGui::window_rect ((int) (size.x * WINDOW_BEGIN_POS), 0, (int) (size.x * WINDOW_SIZE), size.y);
    mixImGui::mixGui::add_window (new editor::windows::hierarchy_window (std::string ("Hierarchy"), rect));
}

void mix::editor::windows::hierarchy_window::render_entity (mix::core::mixEntity* entity, int i)
{
    gui_layout::horizontal_space (20);
    bool selected = i == _selected_entity;

    if (gui_layout::selectable (entity->get_name (), selected))
    {
        _selected_entity = i;
    }
}
