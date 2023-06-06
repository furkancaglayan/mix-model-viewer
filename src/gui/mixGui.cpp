#include "mixGui.h"

std::vector<mixImGui::mixGui::w_ptr> mixImGui::mixGui::_windows;

void mixImGui::mixGui::init (GLFWwindow* window)
{
    IMGUI_CHECKVERSION ();
    ImGui::CreateContext ();
    ImGuiIO& io = ImGui::GetIO ();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark ();
    auto& style = ImGui::GetStyle ();
    ImVec4* colors = style.Colors;
    const ImVec4 bgColor = ImVec4 (0.1f, 0.1f, 0.1f, 0.5f);

    colors[ImGuiCol_Text] = ImVec4 (0.99f, 0.99f, 0.99f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4 (0.35f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4 (0.1f, 0.1f, 0.1f, 0.96f);
    colors[ImGuiCol_ChildBg] = ImVec4 (0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4 (0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4 (0.00f, 0.00f, 0.00f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4 (0.00f, 0.00f, 0.00f, 0.8f);
    colors[ImGuiCol_FrameBg] = ImVec4 (0.00f, 0.00f, 0.00f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4 (0.37f, 0.14f, 0.14f, 0.67f);
    colors[ImGuiCol_FrameBgActive] = ImVec4 (0.39f, 0.20f, 0.20f, 0.67f);
    colors[ImGuiCol_TitleBg] = ImVec4 (0.04f, 0.04f, 0.04f, 0.8f);
    colors[ImGuiCol_TitleBgActive] = ImVec4 (0.48f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4 (0.48f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4 (0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4 (0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4 (0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4 (0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4 (0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4 (0.56f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4 (1.00f, 0.19f, 0.19f, 0.40f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4 (0.89f, 0.00f, 0.19f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4 (1.00f, 0.19f, 0.19f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4 (0.80f, 0.17f, 0.00f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4 (0.89f, 0.00f, 0.19f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4 (0.76f, 0.28f, 0.44f, 0.37f);
    colors[ImGuiCol_HeaderHovered] = ImVec4 (0.76f, 0.28f, 0.44f, 0.57f);
    colors[ImGuiCol_HeaderActive] = ImVec4 (0.76f, 0.28f, 0.44f, 0.57f);
    colors[ImGuiCol_Separator] = ImVec4 (0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4 (0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4 (0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4 (1.00f, 1.00f, 1.00f, 0.85f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4 (1.00f, 1.00f, 1.00f, 0.60f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4 (1.00f, 1.00f, 1.00f, 0.90f);
    colors[ImGuiCol_Tab] = ImVec4 (0.07f, 0.07f, 0.07f, 0.51f);
    colors[ImGuiCol_TabHovered] = ImVec4 (0.86f, 0.23f, 0.43f, 0.67f);
    colors[ImGuiCol_TabActive] = ImVec4 (0.19f, 0.19f, 0.19f, 0.57f);
    colors[ImGuiCol_TabUnfocused] = ImVec4 (0.05f, 0.05f, 0.05f, 0.90f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4 (0.13f, 0.13f, 0.13f, 0.74f);
    colors[ImGuiCol_PlotLines] = ImVec4 (0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4 (1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4 (0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4 (1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4 (0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4 (0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4 (0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4 (0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4 (1.00f, 1.00f, 1.00f, 0.07f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4 (0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4 (1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4 (0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4 (1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4 (0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4 (0.80f, 0.80f, 0.80f, 0.35f);
   style.FrameRounding = 4;
   style.IndentSpacing = 12.0f;
   style.WindowRounding = 4.0f;
   style.ChildRounding = 4.0f;
   style.PopupRounding = 2.0f;
   style.TabRounding = 4.0f;
   style.ScrollbarRounding = 4.0f;
    // ImGui::StyleColorsLight();
    const char* glsl_version = "#version 130";
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL (window, true);
    ImGui_ImplOpenGL3_Init (glsl_version);
}

void mixImGui::mixGui::render (mix::containers::frame_buffer* buffer)
{
    begin ();

    //mixImGui::mixGui::show_style_editor (ImGui::GetStyle ());

    for (size_t i = 0; i < _windows.size(); i++)
    {
        _windows.at (i)->render ();
    }

    end ();
}

void mixImGui::mixGui::on_window_size_changed (int w, int h)
{
    for (auto& win : _windows)
    {
        win->on_window_size_changed (w, h);
    }
    
}

void mixImGui::mixGui::begin ()
{
    ImGui_ImplOpenGL3_NewFrame ();
    ImGui_ImplGlfw_NewFrame ();
    ImGui::NewFrame ();
}

void mixImGui::mixGui::end ()
{
    ImGui::Render ();
    ImGui_ImplOpenGL3_RenderDrawData (ImGui::GetDrawData ());
}

void mixImGui::mixGui::show_style_editor (ImGuiStyle& style)
{
    ImGui::ShowStyleEditor (&style);
}
/*
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

        cursor_pos_x = ImGui::GetCursorPosX ();
        auto r_z = std::string ("Rotate Z##") + light->get_name ();
        ImGui::SetCursorPos (ImVec2 (cursor_pos_x + btn_size.x * 3, cursor_pos_y)); // Move cursor on needed positions
        if (ImGui::Button (r_z.c_str (), btn_size))
        {
            light->_transform->rotate_around (0, 0, 5);
        }
        // 8, 75
    }
}
    */