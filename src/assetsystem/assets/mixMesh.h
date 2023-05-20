#pragma once
#include "../../math/vertex.h"
#include "mixAsset_item.h"
#include "mixMaterial.h"
#include <memory>
#include <string>
#include <vector>
#include "../../rendering/rendering_context.h"
using namespace mix::math;

namespace mix
{
    namespace assetsystem
    {

        class mixMesh : public mix::assetsystem::mixAsset_item
        {
            public:

            mixMesh (const mix::platform::mixAsset_path& path, std::vector<vertex>&& vertices, std::vector<unsigned>&& indices);
            ~mixMesh ();
            void draw (mix::rendering::rendering_context* rendering) const;
            void set_material (std::shared_ptr<mixMaterial> material);

            const std::vector<unsigned>& get_indices () const;
            const std::vector<vertex>& get_vertices () const;
            const unsigned get_vao () const;
            const unsigned get_ebo () const;
            const unsigned get_vbo () const;
            void initialize_mesh ();

            private:

            unsigned VAO{};
            unsigned VBO{};
            unsigned EBO{};
            std::vector<vertex> _vertices;
            std::vector<unsigned> _indices;
            std::weak_ptr<mixMaterial> _material;
        };
    } // namespace assetsystem
} // namespace mix
