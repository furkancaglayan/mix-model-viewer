
#include "editor/mixEditor.h"
#include "platform/typedefs.h"

#include <iostream>
#include <memory>
#include <string>

#include "assetsystem/loaders/mixAsset_loader_mesh.h"
#include "assetsystem/loaders/mixAsset_loader_shader.h"
#include "assetsystem/loaders/mixAsset_loader_text.h"
#include "assetsystem/mixAsset_manager.h"

#include "core/components/mixMesh_component.h"
#include "assetsystem/loaders/mixAsset_loader_texture.h"


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
    mix::mixEditor::_instance->init_render_buffers ();
   
    std::string path{ "C:\\Users\\furka\\Desktop\\Develop\\mb3_dev\\WOTS\\Modules\\Native\\ModuleData" };
    std::string path2{ "C:\\Users\\furka\\Desktop\\Develop" };
    std::string path3{ "..\\..\\..\\assets" };
    std::string pathtext{ "..\\..\\..\\assets\\sometext.txt" };

    mix::assetsystem::mixAsset_manager assets{ path3 };

    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Text);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_texture> (mix::assetsystem::asset_type::Texture);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Material);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Mesh);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Other);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_shader> (mix::assetsystem::asset_type::Shader);


    assets.resolve_all_assets ();
    assets.debug ();
    auto mesh = assets.get_asset_with_full_name<mix::assetsystem::mixMesh> ("cube.obj");
    auto tex = assets.get_asset_with_full_name<mix::assetsystem::mixTexture> ("albedo_17.jpg");
    auto normal = assets.get_asset_with_full_name<mix::assetsystem::mixTexture> ("normal_wood.jpg");
    auto mesh2 = assets.get_asset_with_full_name<mix::assetsystem::mixMesh> ("Skull2.obj");

    auto vertex_shader = assets.get_asset_with_full_name<mix::assetsystem::mixShader> ("standard_vertex.vert");
    // assert (vertex_shader);

    auto fragment_shader = assets.get_asset_with_full_name<mix::assetsystem::mixShader> ("standard_fragment.frag");
    // assert (fragment_shader);

    glfwSetKeyCallback (mix::mixEditor::_instance->_window->get_glfw_window (), key_callback);


    std::string path4{ "..\\..\\..\\assets\\shaders\\program.p" };
    mix::platform::mixAsset_path p (path4);
    auto program = std::make_shared<mix::assetsystem::mixShader_program> (p, vertex_shader.get (), fragment_shader.get ());

    auto model = std::make_shared<mix::core::mixEntity> ();
    auto model2 = std::make_shared<mix::core::mixEntity> ();
    model->_transform->set_position (vec3 (0, 0, 15));
    model2->_transform->set_position (vec3 (0, 0, -15));


    auto component = new mix::components::mixMesh_component (mesh);
    auto component2 = new mix::components::mixMesh_component (mesh2);


    auto material = std::make_shared<mix::assetsystem::mixMaterial> (path4, program);
    auto material2 = std::make_shared<mix::assetsystem::mixMaterial> (path4, program);
    material->set_color (vec3 (1));
    material->set_texture (mix::texture::texture_type::diffuse, tex);
    material2->set_texture (mix::texture::texture_type::diffuse, tex);
    material->set_texture (mix::texture::texture_type::normal, normal);
    material2->set_texture (mix::texture::texture_type::normal, normal);

    component->set_material (material);
    component2->set_material (material2);
    model->add_component (component);
    model->set_name ("Gameobject 1");
    model2->add_component (component2);
    model2->set_name ("Gameobject 2");
    mix::scene_management::mixScene::_instance->get_root ()->add_child (model);
    mix::scene_management::mixScene::_instance->get_root ()->add_child (model2);

    auto light = std::make_shared<mix::core::light::mixLight> (mix::core::light::light_type::directional, vec3 (0.33, 0.33, 0));
    light->_transform->set_position (vec3 (0, 10, 10));
    auto light2 =
    std::make_shared<mix::core::light::mixLight> (mix::core::light::light_type::directional, vec3 (1));
    light2->_transform->set_position (vec3 (0, 10,0));
    light2->set_intensity (0.33f);

    mix::scene_management::mixScene::_instance->add_light (light2);
    //mix::scene_management::mixScene::_instance->add_light (light);
    while (mix::mixEditor::_instance->_should_run)
    {
        mix::mixEditor::_instance->run ();
        mix::mixEditor::_instance->render ();
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