#pragma once
#include <memory>
#include <string>
#include "mixAsset_item.h"

namespace mix
{
    namespace assetsystem
    {
        class mixText_asset : public mix::assetsystem::mixAsset_item
        {

            public:

            mixText_asset (const std::string& name, std::string&& content) : mixAsset_item (name)
            {
                _content = std::make_unique<std::string> (std::move (content));
            }
            private:

            std::unique_ptr<std::string> _content;

            /*
            mixMesh (std::string& name) : mixAsset_item (name)
            {
            }

            mixMesh (mixMesh&& other) noexcept : mixMesh{ other._name }
            {
                std::cout << "Move constructor is called." << std::endl;
            }

            
            mixMesh (const mixMesh& other) = default;
            mixMesh () : mixAsset_item ()
            {
            
            }*/

        };
    } // namespace assetsystem
} // namespace mix
