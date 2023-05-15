
#include "editor/mixEditor.h"
#include "platform/typedefs.h"

#include <imgui.h>
#include <iostream>
#include <memory>
#include <string>

#include "assetsystem/loaders/mixAsset_loader_mesh.h"
#include "assetsystem/loaders/mixAsset_loader_shader.h"
#include "assetsystem/loaders/mixAsset_loader_text.h"
#include "assetsystem/mixAsset_manager.h"
#include "core/components/mixMesh_component.h"


void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);

int main ()
{
    GLenum err;
    if (!glfwInit ())
    {
        std::cout << "GLFW INIT ERROR!";
    }

    mix::mixEditor::create_new ();

    if ((err = glewInit ()) != GLEW_OK)
    {
        std::cout << glewGetErrorString (err) << std::endl;
    }
    glewExperimental = true;


    std::string path{ "C:\\Users\\furka\\Desktop\\Develop\\mb3_dev\\WOTS\\Modules\\Native\\ModuleData" };
    std::string path2{ "C:\\Users\\furka\\Desktop\\Develop" };
    std::string path3{ "..\\..\\..\\assets" };
    std::string pathtext{ "..\\..\\..\\assets\\sometext.txt" };

    mix::assetsystem::mixAsset_manager assets{ path3 };

    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Text);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Texture);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Material);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Mesh);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Other);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_shader> (mix::assetsystem::asset_type::Shader);


    assets.resolve_all_assets ();
    assets.debug ();
    auto mesh = std::shared_ptr<mix::assetsystem::mixMesh> (
    static_cast<mix::assetsystem::mixMesh*> (assets.get_asset_with_full_name ("Skull.obj")));
    auto vertex_shader = assets.get_asset_with_full_name ("vertex.vert");
    assert (vertex_shader);

    auto fragment_shader = assets.get_asset_with_full_name ("fragment.frag");
    assert (fragment_shader);

    glfwSetKeyCallback (mix::mixEditor::_instance->_window->get_glfw_window (), key_callback);
    glEnable (GL_DEPTH_TEST);


    std::string path4{ "..\\..\\..\\assets\\shaders\\program.p" };
    mix::platform::mixAsset_path p (path4);
    mix::assetsystem::mixShader x{ *static_cast<mix::assetsystem::mixShader*> (vertex_shader) };
    mix::assetsystem::mixShader y{ *static_cast<mix::assetsystem::mixShader*> (fragment_shader) };
    auto program = std::make_shared<mix::assetsystem::mixShader_program> (p, x, y);

    auto model = std::make_shared<mix::core::mixEntity> ();
    auto component = new mix::components::mixMesh_component (mesh);
    auto material = std::make_shared<mix::assetsystem::mixMaterial> (path4, program);
    mesh->set_material (material);
    model->add_component (component);
    mix::scene_management::mixScene::_instance->get_root ()->add_child (model);
    auto light = std::make_shared<mix::core::light::mixLight> (mix::core::light::light_type::directional, vec3 (1, 0, 0));
    light->_transform->set_position (vec3 (4, 3, 2));

    mix::scene_management::mixScene::_instance->add_light (light);
    while (mix::mixEditor::_instance->_should_run)
    {
        mix::mixEditor::_instance->run ();
    }
}

void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const float cameraSpeed = 1.0f; // adjust accordingly
    if (key == GLFW_KEY_W && action == GLFW_REPEAT)
    {
        mix::scene_management::mixScene::_instance->get_main_cam ()->_transform->translate (cameraSpeed * mix::transform::forward);
    }
    if (key == GLFW_KEY_S && action == GLFW_REPEAT)
    {
        mix::scene_management::mixScene::_instance->get_main_cam ()->_transform->translate (-cameraSpeed * mix::transform::forward);
    }
    if (key == GLFW_KEY_A && action == GLFW_REPEAT)
    {
        mix::scene_management::mixScene::_instance->get_main_cam ()->_transform->translate (-mix::transform::right * cameraSpeed);
    }
    if (key == GLFW_KEY_D && action == GLFW_REPEAT)
    {
        mix::scene_management::mixScene::_instance->get_main_cam ()->_transform->translate (mix::transform::right * cameraSpeed);
    }

    if (key == GLFW_KEY_X && action == GLFW_REPEAT)
    {
        mix::scene_management::mixScene::_instance->get_lights ().at (0).lock ()->set_intensity (
        mix::scene_management::mixScene::_instance->get_lights ().at (0).lock ()->get_intensity () - 0.1f);
    }

    if (key == GLFW_KEY_C && action == GLFW_REPEAT)
    {
        mix::scene_management::mixScene::_instance->get_lights ().at (0).lock ()->set_intensity (
        mix::scene_management::mixScene::_instance->get_lights ().at (0).lock ()->get_intensity () + 0.1f);
    }
}