#include "hierarchy_window.h"
#include <stdint.h>

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

        //gui_layout::collapsing_label ("Entities", &_visible_entities);

        if (gui_layout::tree_node ("Entities", -1, false, true, false))
        {
            auto children = scene->get_root ()->get_children ();

            for (int i = 0; i < children.size (); i++)
            {
                bool is_node = children.at (i)->get_children ().size();
                if (gui_layout::tree_node (children.at (i)->get_name ().c_str (), i, false, false, !is_node))
                {
                    if (gui_layout::begin_drag_drop_source())
                    {
                        gui_layout::set_drag_drop_payload ("ENTITY_", children.at (i).get (), sizeof (mix::core::mixEntity));
                        gui_layout::end_drag_drop_source ();
                    }

                    if (gui_layout::begin_drag_drop_target ())
                    {
                        auto data = gui_layout::accept_drag_drop_payload ("ENTITY_");
                        if (data)
                        {
                            auto target = reinterpret_cast<mix::core::mixEntity*> (data);
                            if (target != children.at (i).get())
                            {
                                //children.at (i).get ()->add_child (target);
                            }
                        }
                        gui_layout::end_drag_drop_target ();
                    }

                    if (is_node)
                    {
                        gui_layout::tree_pop ();
                    }
                }
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
    auto WINDOW_BEGIN_POS = 0.85f;
    auto WINDOW_SIZE = 0.15f;
    auto width = size.x * WINDOW_SIZE;
    rescale (vec2i (width, static_cast<int> (size.y * 0.75f)));
    set_position (vec2i (size.x * WINDOW_BEGIN_POS, 0));
}

mix::editor::windows::hierarchy_window::hierarchy_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::MenuBar | mixImGui::window_flags::NoCollapse |
                        mixImGui::window_flags::NoMove)

{
    _selected_entity = nullptr;
}

mix::editor::windows::hierarchy_window::~hierarchy_window ()
{
}

void mix::editor::windows::hierarchy_window::initialize (const vec2i& size)
{
    // TODO: MAKE ALL INT ARGUMENTS AS W, H TO VEC2
    auto WINDOW_BEGIN_POS = 0.85f;
    auto WINDOW_SIZE = 0.15f;
    auto rect = mixImGui::window_rect ((int) (size.x * WINDOW_BEGIN_POS), 0, (int) (size.x * WINDOW_SIZE),
                                       static_cast<int> (size.y * 0.75f));
    mixImGui::mixGui::add_window (new editor::windows::hierarchy_window (std::string ("Hierarchy"), rect));
}
