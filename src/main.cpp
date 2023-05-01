
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

#include "core/mixCamera.h"

#include "core/components/mixTransform.h"
void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);

std::unique_ptr<mix::core::mixCamera> _camera;

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
    mix::assetsystem::mixAsset_manager assets{ path3 };

    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Text);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Texture);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Material);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Mesh);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Other);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_shader> (mix::assetsystem::asset_type::Shader);


    assets.resolve_all_assets ();
    assets.debug ();
    auto mesh = static_cast<mix::assetsystem::mixMesh*> (assets.get_asset_with_full_name ("Skull.obj"));
    auto vertex_shader = assets.get_asset_with_full_name ("vertex.vert");
    assert (vertex_shader);

    auto fragment_shader = assets.get_asset_with_full_name ("fragment.frag");
    assert (fragment_shader);

    std::string path4{ "..\\..\\..\\assets\\shaders\\program.p" };
    mix::platform::mixAsset_path p (path4);


    mix::assetsystem::mixShader x{ *static_cast<mix::assetsystem::mixShader*> (vertex_shader) };
    mix::assetsystem::mixShader y{ *static_cast<mix::assetsystem::mixShader*> (fragment_shader) };
    auto program = std::make_shared<mix::assetsystem::mixShader_program> (p, x, y);

    auto material = std::make_shared<mix::assetsystem::mixMaterial> (program);
    material->set_color (vec4 (1));
    mesh->set_material (material);
 

    _camera = std::make_unique<mix::core::mixCamera> ();
    mat4 model = mat4 (1);
    vec3 _light{ 0.35f };
    mix::components::mixTransform t{ vec3 (0) };
    vec3 _light_pos{ 4.0f, -3.0f, 3.0f };

    glfwSetKeyCallback (mix::mixEditor::_instance->_window->get_glfw_window (), key_callback);
    glEnable (GL_DEPTH_TEST);

        float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
        0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f,
        0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,
        0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f,
    };

    glEnable (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (mix::mixEditor::_instance->_should_run)
    {
        glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
         //mesh->draw ();
        glDepthMask (GL_FALSE);
        glUseProgram (program->get_program_id ());

        program->set_mat4 ("_model", t.get_model_mat());
        program->set_mat4 ("_view", _camera->get_view_mat ());
        program->set_mat4 ("_projection", _camera->get_projection_mat ());
        program->set_vec3 ("_light", _light);
        program->set_vec3 ("_light_pos", _light_pos);
        program->set_vec3 ("_view_pos", _camera->_transform->get_position());
        material->apply ();

        glBindVertexArray (mesh->get_vao ());
        auto x = static_cast<GLsizei> (mesh->get_indices ().size ());
        glDrawElements (GL_TRIANGLES, x, GL_UNSIGNED_INT, 0);
        glBindVertexArray (0);

        _camera->update ();
        glfwSwapBuffers (mix::mixEditor::_instance->_window->get_glfw_window ());
        glfwPollEvents ();
        // mix::mixEditor::_instance->run ();
        glDepthMask (GL_FALSE);
    }
}

void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const float cameraSpeed = 1.0f; // adjust accordingly
    if (key == GLFW_KEY_W && action == GLFW_REPEAT)
    {
        _camera->_transform->translate (cameraSpeed * mix::transform::forward);
    }
    if (key == GLFW_KEY_S && action == GLFW_REPEAT)
    {
        _camera->_transform->translate (-cameraSpeed * mix::transform::forward);
    }
    if (key == GLFW_KEY_A && action == GLFW_REPEAT)
    {
        _camera->_transform->translate (-mix::transform::right * cameraSpeed);
    }
    if (key == GLFW_KEY_D && action == GLFW_REPEAT)
    {
        _camera->_transform->translate (mix::transform::right * cameraSpeed);
    }
}