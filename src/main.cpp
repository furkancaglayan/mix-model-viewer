
#include "editor/mixEditor.h"
#include "platform/typedefs.h"

#include <imgui.h>
#include <iostream>
#include <memory>
#include <string>

#include "assetsystem/loaders/mixAsset_loader_text.h"
#include "assetsystem/mixAsset_manager.h"

int main ()
{
    std::string path{ "C:\\Users\\furka\\Desktop\\Develop" };
    mix::platform::mixAsset_folder folder{ std::move (path) };

    std::string path2{ "C:\\Users\\furka\\Desktop\\Develop\\spnpccharacters.xml" };
    mix::platform::mixAsset_file f{ std::move (path2) };


    mix::assetsystem::mixAsset_manager assets{ std::string{
    "C:\\Users\\furka\\Desktop\\Develop\\mix-model-viewer\\assets" } };

    assets.add_asset_map<mix::assetsystem::mixText_asset> ();
    assets.register_loader<mix::assetsystem::mixText_asset, mix::assetsystem::loaders::mixAsset_loader_text> ();
    std::unique_ptr<mix::assetsystem::mixText_asset> ptr =
    std::unique_ptr<mix::assetsystem::mixText_asset> (assets.resolve_asset<mix::assetsystem::mixText_asset> (f));

    if (ptr)
    {
        std::cout << "uniqye" << std::endl;
    }
    else
    {
        std::cout << "not uniqye" << std::endl;
    
    }
    if (f.open ())
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