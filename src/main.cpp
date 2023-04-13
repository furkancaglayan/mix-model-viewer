
#include "platform/typedefs.h"
#include "editor/mixEditor.h"

#include <imgui.h>
#include <iostream>
#include <memory>
#include <string>

#include "assetsystem/mixMesh.h"
#include "assetsystem/loaders/mixAsset_loader_mesh.h"
#include "platform/mixAsset_file.h"
#include "platform/mixAsset_folder.h"
#include "assetsystem/mixAsset_manager.h"

int main ()
{
    /* mix::assetsystem::mixMesh mesh (
    std::string ("C:\\Users\\furka\\Desktop\\Develop\\mix-"
                 "model-viewer\\assets\\sometext.txt"));
    mesh.read ();
    auto cont = mesh.get_content ();
    mix::assetsystem::mixAsset_manager assets{ std::string{"C:\\Users\\furka\\Desktop\\Develop\\mix-model-viewer\\assets" } };
    assets.load ();*/

    std::string path{ "C:\\Users\\furka\\Desktop\\Develop" };
    mix::platform::mixAsset_folder folder{ std::move (path)};

    std::string path2{ "C:\\Users\\furka\\Desktop\\Develop\\spnpccharacters.xml" };
    mix::platform::mixAsset_file f{ std::move (path2) };

   
     mix::assetsystem::mixAsset_manager assets{ std::string{
    "C:\\Users\\furka\\Desktop\\Develop\\mix-model-viewer\\assets" } };

    assets.add_asset_map<mix::assetsystem::mixMesh> ();
     assets.register_loader<mix::assetsystem::mixMesh, mix::assetsystem::loaders::mixAsset_loader_mesh> ();

    if (f.open())
    {
        auto s = f.read_all_text ();
        f.close ();
    }

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