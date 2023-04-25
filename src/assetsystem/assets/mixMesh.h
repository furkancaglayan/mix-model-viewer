#pragma once
#include "mixAsset_item.h"
#include <memory>
#include <string>
#include <vector>
#include "../../core/vertex.h"
#include "mixMaterial.h"

namespace mix
{
    namespace assetsystem
    {
        class mixMesh : public mix::assetsystem::mixAsset_item
        {
            public:

            mixMesh (const mix::platform::mixAsset_path& path,
                     std::vector<vertex>&& vertices,
                     std::vector<unsigned>&& indices
                     /* mixMaterial&& material*/);
            ~mixMesh ();
            void load ();
            private:

            GLuint VAO{};
            GLuint VBO{};
            GLuint EBO{};
            std::vector<vertex> _vertices;
            std::vector<unsigned> _indices;
            //mixMaterial _material;
        };
    } // namespace assetsystem
} // namespace mix
