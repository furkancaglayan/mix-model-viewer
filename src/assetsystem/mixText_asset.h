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
