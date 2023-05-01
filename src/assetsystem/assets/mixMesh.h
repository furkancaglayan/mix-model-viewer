#pragma once
#include "mixAsset_item.h"
#include <memory>
#include <string>
#include <vector>
#include "../../math/vertex.h"
#include "mixMaterial.h"
using namespace mix::math;

namespace mix
{
    namespace assetsystem
    {

        class mixMesh : public mix::assetsystem::mixAsset_item
        {
            public:

            mixMesh (const mix::platform::mixAsset_path& path,
                     std::vector<vertex>&& vertices,
                     std::vector<unsigned>&& indices);
            ~mixMesh ();
            void draw () const;
            void set_material (std::shared_ptr<mixMaterial> material);
            private:

            void initialize_mesh ();

            GLuint VAO{};
            GLuint VBO{};
            GLuint EBO{};
            std::vector<vertex> _vertices;
            std::vector<unsigned> _indices;
            std::weak_ptr<mixMaterial> _material;
        };
    } // namespace assetsystem
} // namespace mix
