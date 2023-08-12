#include "editor/mixEditor.h"

#include <iostream>
#include <memory>
#include <string>

#include "assetsystem/loaders/mixAsset_loader_mesh.h"
#include "assetsystem/loaders/mixAsset_loader_shader.h"
#include "assetsystem/loaders/mixAsset_loader_text.h"
#include "assetsystem/mixAsset_manager.h"

#include "core/components/mixMesh_component.h"
#include "assetsystem/loaders/mixAsset_loader_texture.h"

#include "library/debug.h"

void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);

int main ()
{
    GLenum err;
    DEBUG_LOG ("Initializing GLFW");
    if (!glfwInit ())
    {
        FAILED_ASSERT ("GLFW initialization error!");
    }

    mix::editor_config config = mix::editor_config ();
    mix::mixEditor::create_new (config);

    if ((err = glewInit ()) != GLEW_OK)
    {
        DEBUG_LOG (glewGetErrorString (err));
        FAILED_ASSERT ("GLEW initialization error!");
    }
    glewExperimental = true;
    mix::mixEditor::_instance->init_render_buffers ();
   
    std::string path{ "C:\\Users\\furka\\Desktop\\Develop\\mb3_dev\\WOTS\\Modules\\Native\\ModuleData" };
    std::string path2{ "C:\\Users\\furka\\Desktop\\Develop" };
    std::string path3{ "..\\..\\..\\assets" };
    std::string pathtext{ "..\\..\\..\\assets\\sometext.txt" };


    mix::mixEditor::initialize_asset_manager (path3);
    mix::mixEditor::initialize_gui ();
    mix::mixEditor::_instance->get_window ()->show ();
    mix::assetsystem::mixAsset_manager* assets = mix::mixEditor::get_asset_manager ();

    auto mesh = assets->get_asset_with_full_name<mix::assetsystem::mixMesh> ("cube.obj");
    auto tex = assets->get_asset_with_full_name<mix::assetsystem::mixTexture> ("albedo_17.jpg");
    auto normal = assets->get_asset_with_full_name<mix::assetsystem::mixTexture> ("normal_wood.jpg");
    auto mesh2 = assets->get_asset_with_full_name<mix::assetsystem::mixMesh> ("Skull2.obj");

    auto vertex_shader = assets->get_asset_with_full_name<mix::assetsystem::mixShader> ("_vertex.vert");
    // assert (vertex_shader);

    auto fragment_shader = assets->get_asset_with_full_name<mix::assetsystem::mixShader> ("_fragment.frag");
    // assert (fragment_shader);

    glfwSetKeyCallback (mix::mixEditor::_instance->get_window ()->get_glfw_window (), key_callback);


    std::string path4{ "..\\..\\..\\assets\\shaders\\program.p" };
    mix::platform::mixAsset_path p (path4);
    auto program = std::make_shared<mix::assetsystem::mixShader_program> (p, vertex_shader.get (), fragment_shader.get ());

   


    auto material = std::make_shared<mix::assetsystem::mixMaterial> (path4, program);
    material->set_color (vec3 (1));
    material->set_texture (mix::texture::texture_type::diffuse, tex);
    material->set_texture (mix::texture::texture_type::normal, normal);

    for (size_t i = 0; i < 10; i++)
    {
        auto model = std::make_shared<mix::core::mixEntity> ();
        model->_transform->set_position (vec3 (float (i) * 2, 1, float (i) * 2));
        auto component = new mix::components::mixMesh_component (mesh);
        component->set_material (material);
        model->add_component (component);
        model->set_name ("Cube " + std::to_string(i));
        mix::scene_management::mixScene::_instance->add_entity (std::move (model));
    }
    auto light = std::make_shared<mix::core::light::mixLight> (mix::core::light::light_type::directional, vec3 (0.33, 0.33, 0));
    light->_transform->set_position (vec3 (0, 10, 10));
    auto light2 =
    std::make_shared<mix::core::light::mixLight> (mix::core::light::light_type::directional, vec3 (1));
    light2->_transform->set_position (vec3 (0, 10,0));
    light2->set_intensity (0.33f);

    light->set_name ("Light 1");
    light2->set_name ("Light 2");
    mix::scene_management::mixScene::_instance->add_entity (std::move (light2));
    mix::scene_management::mixScene::_instance->add_entity (std::move (light));
    while (mix::mixEditor::_instance->_should_run)
    {
        mix::mixEditor::_instance->run ();
        mix::mixEditor::_instance->render ();
    }

    mix::mixEditor::destroy ();
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
}