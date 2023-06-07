#include "hierarchy_window.h"

void mix::editor::windows::hierarchy_window::render ()
{
    auto scene = mix::mixEditor::_instance->get_active_scene ();
    if (scene)
    {
        set_title (scene->get_root ()->get_name ());
        begin ();

        gui_layout::begin_vertical ();
        gui_layout::begin_selectable_list (_selected_entity);

        gui_layout::collapsing_label ("Cameras", &_visible_cameras);

        if (_visible_cameras)
        {
            gui_layout::add_selectable (static_cast<i_guielement*> (scene->get_main_cam ()));
            gui_layout::render_added_selectables ();
        }

        gui_layout::collapsing_label ("Lights", &_visible_lights);
        if (_visible_lights)
        {
            auto children = scene->get_lights();
            for (size_t i = 0; i < children.size (); i++)
            {
                if (!children.at (i).expired ())
                {
                    gui_layout::add_selectable (static_cast<i_guielement*> (children.at (i).lock ().get ()));
                }
            }
            gui_layout::render_added_selectables ();
        }
        gui_layout::collapsing_label ("Entities", &_visible_entities);

        if (_visible_entities)
        {
            auto children = scene->get_root ()->get_children ();

            for (size_t i = 0; i < children.size (); i++)
            {
                gui_layout::add_selectable (static_cast<i_guielement*> (children.at (i).get ()));
            }
        }
     
        _selected_entity = gui_layout::end_selectable_list ();

        if (_selected_entity != nullptr)
        {
            _selected_entity->on_gui ();
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
    _selected_entity = nullptr;
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
