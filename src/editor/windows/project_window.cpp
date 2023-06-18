#include "project_window.h"
#include "../../assetsystem/default_assets.h"

mix::editor::windows::project_window::project_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::NoCollapse | mixImGui::window_flags::NoMove |
                        mixImGui::window_flags::NoResize | mixImGui::window_flags::NoTitleBar)
{
    _folder_icon =
    mixEditor::get_asset_manager ()->get_asset_with_full_name<mix::assetsystem::mixTexture> ("folder.png").get ();
    assert (_folder_icon);
    _empty_folder_icon =
    mixEditor::get_asset_manager ()->get_asset_with_full_name<mix::assetsystem::mixTexture> ("empty_folder.png").get ();
    auto assets = mix::mixEditor::get_asset_manager ();
    _root_node = assets->get_root_node ();
}

void mix::editor::windows::project_window::render ()
{
    begin ();
    auto assets = mix::mixEditor::get_asset_manager ();
    if (assets)
    {
        auto assets_node = assets->get_root_node ();
        int horizontal_folder_count = get_size ().x / 64;

        auto index = 0;
        assert (_root_node);

        auto node = _root_node;
        std::vector<mix::assetsystem::asset_tree_ptr> vec{};

        while (!node->is_root ())
        {
            vec.push_back (node);
            // gui_layout::text_label (node->get_value ()->get_base_name ());
            node = (mix::assetsystem::asset_tree_ptr) node->get_parent ();
        }
        vec.push_back (assets_node);
        auto p_sz = get_size ();

        color bg = color ();
        gui_layout::set_background_color (bg);
        gui_layout::begin_child ("Project", ImVec2 ((float) p_sz.x, 40), false, static_cast<int>(get_flags()));
        gui_layout::begin_horizontal ();
        for (int i = (int) vec.size () - 1; i >= 0; i--)
        {
            gui_layout::text_label (vec.at (i)->get_value ()->get_full_name ());
        }

        gui_layout::end_horizontal ();
        gui_layout::end_child ();
        gui_layout::pop_style_vars ();

        gui_layout::begin_horizontal ();
        {
            for (auto& it : _root_node->get_children ())
            {
                gui_layout::begin_vertical ();

                if (mix::platform::platform_utils::is_folder (it->get_value ()->get_path ()))
                {
                    auto folder = static_cast<const mix::assetsystem::mixAsset_folder*> (it->get_value ());

                    {
                        bool pressed, double_clicked, right_clicked;
                        auto icon = it->has_children () ? _folder_icon->get_id () : _empty_folder_icon->get_id ();
                        gui_layout::selectable_image (it->get_key (), ImVec2 (64, 64), icon, pressed, double_clicked, right_clicked);
                        if (pressed)
                        {
                            _selected_folder = (mix::assetsystem::mixAsset_folder*) folder;

                            if (double_clicked)
                            {
                                _root_node = it.get ();
                            }
                        }
                        else if (right_clicked)
                        {
                        }


                        gui_layout::text_label (folder->get_shortened_name ());
                    }
                }
                else
                {
                    auto file = it->get_value ();

                    {
                        auto icon = mix::assetsystem::default_assets::get_asset_default_icon (file);
                        bool pressed, double_clicked, right_clicked;
                        gui_layout::selectable_image (it->get_key (), ImVec2 (64, 64), icon->get_id (), pressed,
                                                      double_clicked, right_clicked);
                        gui_layout::text_label (file->get_shortened_name ());
                    }
                }
                gui_layout::end_vertical ();
                gui_layout::horizontal_space (35);
                index++;
            }
        }
        gui_layout::end_horizontal ();

        /*
        auto flags = window_flags::AlwaysVerticalScrollbar | window_flags::NoMove;
        gui_layout::begin_child ("Assets", ImVec2 ((float) parent_size.x / 10.0f, static_cast<float> (parent_size.y)),
                                 true, static_cast<int> (flags));
        gui_layout::text_label ("Assets");
        gui_layout::end_child ();*/
    }

    end ();
}

void mix::editor::windows::project_window::on_editor_window_size_changed_impl (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.8f;
    auto WINDOW_SIZE = 0.25f;
    auto height = size.y * WINDOW_SIZE;
    auto width = size.x * WINDOW_BEGIN_POS;

    auto WINDOW_SIZE_Y = 0.2f;

    rescale (vec2i (width, height));
    set_position (vec2i (size.x * WINDOW_SIZE_Y, static_cast<int> (size.y * 0.75f)));
}

void mix::editor::windows::project_window::initialize (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.8f;
    auto WINDOW_SIZE = 0.25f;
    auto WINDOW_SIZE_Y = 0.2f;

    auto rect = mixImGui::window_rect ((int) (size.x * WINDOW_SIZE_Y), (int) (size.y * WINDOW_BEGIN_POS),
                                       (int) (size.x * WINDOW_BEGIN_POS), (int) (size.y * WINDOW_SIZE));
    mixImGui::mixGui::add_window (new editor::windows::project_window (std::string ("Project"), rect));
}
