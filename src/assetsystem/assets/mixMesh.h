#pragma once
#include "../../math/vertex.h"
#include "mixAsset_item.h"
#include "mixMaterial.h"
#include <memory>
#include <string>
#include <vector>
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
            void draw () const;
            void set_material (std::shared_ptr<mixMaterial> material);
            inline const std::vector<unsigned>& get_indices () const
            {
                return _indices;
            }

            inline const std::vector<vertex>& get_vertices () const
            {
                return _vertices;
            }

            inline const unsigned get_vao () const
            {
                return VAO;
            }

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
