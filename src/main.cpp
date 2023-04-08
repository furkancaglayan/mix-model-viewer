#include <GL/glew.h>
#include "editor/mixEditor.h"
#include <imgui.h>
#include <iostream>
#include <memory>

#include "assetsystem/mixAsset_base.h"
#include "assetsystem/mixMesh.h"



int main ()
{
    mix::assetsystem::mixMesh mesh (
    std::string ("C:\\Users\\furka\\Desktop\\Develop\\mix-"
                 "model-viewer\\assets\\sometext.txt"));
    mesh.read ();
    auto cont = mesh.get_content ();

    GLenum err;
    if (!glfwInit ())
    {
        std::cout << "GLFW INIT ERROR!";
    }
    glewExperimental = true;
    if ((err = glewInit ()) != GLEW_OK)
    {
        std::cout << glewGetErrorString (err) << std::endl;
    }

    mix::mixEditor::create_new ();
    while (mix::mixEditor::_instance->_should_run)
    {
        mix::mixEditor::_instance->run ();
    }
}