#include "mixGui.h"
#include "gui_style.h"

std::vector<mixImGui::mixGui::w_ptr> mixImGui::mixGui::_windows;

void mixImGui::mixGui::init (GLFWwindow* window)
{
    IMGUI_CHECKVERSION ();
    ImGui::CreateContext ();
    ImGuiIO& io = ImGui::GetIO ();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    auto& style = ImGui::GetStyle ();
    gui_style::get_default_dark_style (style);
    // Setup Dear ImGui style
    /* ImGui::StyleColorsDark ();
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
    // ImGui::StyleColorsLight();*/
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

void mixImGui::mixGui::on_editor_window_size_changed (const vec2i& size)
{
    for (auto& win : _windows)
    {
        win->on_editor_window_size_changed (size);
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

void mixImGui::mixGui::add_font (mix::assetsystem::mixFont* font, bool set_default)
{
    ImGuiIO& io = ImGui::GetIO ();
    ImFont* im_font = io.Fonts->AddFontFromFileTTF (font->get_path ().c_str(), 105);

    if (set_default)
    {
        io.FontDefault = im_font;
    }
}

