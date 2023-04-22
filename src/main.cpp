
#include "editor/mixEditor.h"
#include "platform/typedefs.h"

#include <imgui.h>
#include <iostream>
#include <memory>
#include <string>

#include "assetsystem/loaders/mixAsset_loader_text.h"
#include "assetsystem/mixAsset_manager.h"
#include "assetsystem/loaders/mixAsset_loader_mesh.h"

int main ()
{
    std::string path{ "C:\\Users\\furka\\Desktop\\Develop\\mb3_dev\\WOTS\\Modules\\Native\\ModuleData" };
    std::string path2{ "C:\\Users\\furka\\Desktop\\Develop" };
    mix::assetsystem::mixAsset_manager assets{ path };

    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Text);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Texture);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Material);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_mesh> (mix::assetsystem::asset_type::Mesh);
    assets.register_loader<mix::assetsystem::loaders::mixAsset_loader_text> (mix::assetsystem::asset_type::Other);

    assets.resolve_all_assets ();
    assets.debug ();

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