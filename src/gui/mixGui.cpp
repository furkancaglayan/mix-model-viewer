#include "mixGui.h"
void render_entities (const std::vector<std::shared_ptr<mix::core::mixEntity>> scene_objs, int depth);
void render_lights (std::vector<std::weak_ptr<mix::core::light::mixLight>> lights);

void mix::gui::test_gui::init (mix::core::mixWindow* window)
{
    IMGUI_CHECKVERSION ();
    ImGui::CreateContext ();
    ImGuiIO& io = ImGui::GetIO ();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark ();
    // ImGui::StyleColorsLight();
    const char* glsl_version = "#version 130";
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL (window->get_glfw_window (), true);
    ImGui_ImplOpenGL3_Init (glsl_version);
}

void mix::gui::test_gui::new_frame (mix::core::mixEntity* root,
                                    std::vector<std::weak_ptr<mix::core::light::mixLight>> lights, mix::core::mixWindow* w)
{
    ImGui_ImplOpenGL3_NewFrame ();
    ImGui_ImplGlfw_NewFrame ();
    ImGui::NewFrame ();
    bool show_demo_window = true;
    ImGui::SetNextWindowPos (ImVec2 (0, 0));
    ImGui::Begin (root->get_name ().c_str (), 0,
                  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    auto width = ImGui::GetWindowWidth ();
    ImGui::SetWindowSize (ImVec2 (width, w->get_window_size().y));
    ImGui::Text (root->get_name ().c_str ());
    render_entities (root->get_children(), 0);

    ImGui::Text ("Lights");
    render_lights (lights);

    ImGui::End ();
    ImGui::Render ();
    ImGui_ImplOpenGL3_RenderDrawData (ImGui::GetDrawData ());
}

void render_entities (const std::vector<std::shared_ptr<mix::core::mixEntity>> scene_objs, int depth)
{
    for (auto it = scene_objs.cbegin(); it < scene_objs.cend(); it++)
    {
        ImVec2 btn_size (100, 20);
        auto entity = (*it).get ();
        auto cursor_pos_y = ImGui::GetCursorPosY ();
        auto name = entity->get_name ().c_str ();
        // 8, 44
        ImGui::Text (entity->get_name ().c_str ());
        auto cursor_pos_x = ImGui::GetCursorPosX ();
        ImGui::SetCursorPos (ImVec2 (cursor_pos_x + btn_size.x, cursor_pos_y)); // Move cursor on needed positions
                    
        auto r_x = std::string ("Rotate X##") + entity->get_name ();
        if (ImGui::Button (r_x.c_str (), btn_size))
        {
            entity->_transform->rotate_around (5, 0, 0);
        }

        cursor_pos_x = ImGui::GetCursorPosX ();
        ImGui::SetCursorPos (ImVec2 (cursor_pos_x + btn_size.x * 2, cursor_pos_y)); // Move cursor on needed positions
        auto r_y = std::string ("Rotate Y##") + entity->get_name ();
        // 8, 65
        if (ImGui::Button (r_y.c_str (), btn_size))
        {
            entity->_transform->rotate_around (0, 5, 0);
        }

        cursor_pos_x = ImGui::GetCursorPosX ();
        auto r_z = std::string ("Rotate Z##") + entity->get_name ();
        ImGui::SetCursorPos (ImVec2 (cursor_pos_x + btn_size.x * 3, cursor_pos_y)); // Move cursor on needed positions
           if (ImGui::Button (r_z.c_str (), btn_size))
        {
            entity->_transform->rotate_around (0, 0, 5);
        }
        // 8, 75
        render_entities (entity->get_children (), depth + 1);
    }
}
void render_lights (std::vector<std::weak_ptr<mix::core::light::mixLight>> lights)
{
    for (auto it = lights.cbegin (); it < lights.cend (); it++)
    {
        ImVec2 btn_size (100, 20);
        auto light = (*it).lock ().get ();
        auto cursor_pos_y = ImGui::GetCursorPosY ();

        auto name = light->get_name ().c_str ();
        // 8, 44
        ImGui::Text (light->get_name ().c_str ());
        auto cursor_pos_x = ImGui::GetCursorPosX ();
        ImGui::SetCursorPos (ImVec2 (cursor_pos_x + btn_size.x, cursor_pos_y)); // Move cursor on needed positions

        auto intensity = std::string ("Intensity##") + light->get_name ();
        auto l = light->get_intensity ();
        ImGui::SliderFloat (intensity.c_str (), &l, 0, 5.0f);
        light->set_intensity (l);
        cursor_pos_x = ImGui::GetCursorPosX ();
        //ImGui::SetCursorPos (ImVec2 (cursor_pos_x + btn_size.x * 2, cursor_pos_y)); // Move cursor on needed positions


         auto color = std::string ("Color##") + light->get_name ();
        // 8, 65
        
         auto col = light->get_color ();
         ImGui::ColorPicker3 (color.c_str (), &col.x);
         light->set_color (col);

        /*
        cursor_pos_x = ImGui::GetCursorPosX ();
        auto r_z = std::string ("Rotate Z##") + light->get_name ();
        ImGui::SetCursorPos (ImVec2 (cursor_pos_x + btn_size.x * 3, cursor_pos_y)); // Move cursor on needed positions
        if (ImGui::Button (r_z.c_str (), btn_size))
        {
            light->_transform->rotate_around (0, 0, 5);
        }*/
        // 8, 75
    }
}
