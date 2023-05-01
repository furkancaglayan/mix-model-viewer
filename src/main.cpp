
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
    material->set_color (vec3(0.4f, 0.89f, 0.12f));
    mesh->set_material (material);
    /*x float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};    

     unsigned int VBO, VAO;
    glGenVertexArrays (1, &VAO);
    glGenBuffers (1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray (VAO);

    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*) 0);
    glEnableVertexAttribArray (0);
    // color attribute
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*) (3 * sizeof (float)));
    glEnableVertexAttribArray (1);
    */

    auto camera = std::make_shared<mix::core::mixCamera> ();

    mat4 model = mat4 (1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, -5, 0, 0, 0, 1);
    vec3 _light = vec3 (1, 1, 1);
    vec3 _light_pos = vec3 (-1, -1, -1);
    vec3 _view_pos = vec3 (0, 0, +5);


    while (mix::mixEditor::_instance->_should_run)
    {
        glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera->refresh ();
        mesh->draw ();
        program->set_mat4 ("_model", model);
        program->set_mat4 ("_view", camera->get_view_mat ());
        program->set_mat4 ("_projection", camera->get_projection_mat ());
        program->set_vec3 ("_light", _light);
        program->set_vec3 ("_light_pos", _light_pos);
        program->set_vec3 ("_view_pos", _view_pos);
        glfwSwapBuffers (mix::mixEditor::_instance->_window->get_glfw_window ());
        glfwPollEvents ();
        //mix::mixEditor::_instance->run ();
    }
}