#include "mixAsset_loader_mesh.h"

namespace mix
{
    namespace assetsystem
    {
        namespace loaders
        {
            const static std::string obj_v = "v ";
            const static std::string obj_vt = "vt";
            const static std::string obj_vn = "vn";
            const static std::string obj_f = "f";

            mix::assetsystem::mixAsset_item* mixAsset_loader_mesh::resolve_impl (mix::platform::mixFile& file)
            {
                return load_obj (file.get_path ());
            }

            mix::assetsystem::mixMesh* mixAsset_loader_mesh::load_obj (mix::platform::mixAsset_path path)
            {
                std::ifstream in (static_cast<const char*> (path), std::ios::in);
                if (!in)
                {
                    // assert
                    return nullptr;
                }

                std::vector<vec3> normals;
                std::vector<vec3> uvs;
                std::vector<unsigned> indices;
                std::vector<vertex> vertices;

                std::string line;

                while (std::getline (in, line))
                {
                    auto is_vertex_definition = line.substr (0, 2) == obj_v;
                    auto is_tex_definition = line.substr (0, 2) == obj_vt;
                    auto is_normal_definition = line.substr (0, 2) == obj_vn;

                    if (is_vertex_definition || is_tex_definition || is_normal_definition)
                    {
                        std::istringstream s (line.substr (2));
                        vec3 v;
                        s >> v.x;
                        s >> v.y;
                        s >> v.z;

                        if (is_vertex_definition)
                        {
                            vertices.emplace_back (vertex(v));
                        }
                        else if (is_tex_definition)
                        {
                            uvs.emplace_back (v);
                        }
                        else if (is_normal_definition)
                        {
                            normals.emplace_back (v);
                        }
                    }
                    else if (line.substr (0, 1) == "f")
                    {
                        // TODO: implement alternative face formats.
                        unsigned int vertex_index[3], uv_index[3], normal_index[3];
                        sscanf_s (line.substr (2).c_str (), "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0],
                                  &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1],
                                  &vertex_index[2], &uv_index[2], &normal_index[2]);

                        indices.push_back (vertex_index[0] - 1);
                        indices.push_back (vertex_index[1] - 1);
                        indices.push_back (vertex_index[2] - 1);

                        auto& v0 = vertices.at (vertex_index[0] - 1);
                        auto& v1 = vertices.at (vertex_index[1] - 1);
                        auto& v2 = vertices.at (vertex_index[2] - 1);

                        // Shortcuts for UVs
                        auto& uv0 = uvs.at (uv_index[0] - 1);
                        auto& uv1 = uvs.at (uv_index[1] - 1);
                        auto& uv2 = uvs.at (uv_index[2] - 1);


                        auto& n0 = normals.at (normal_index[0] - 1);
                        auto& n1 = normals.at (normal_index[1] - 1);
                        auto& n2 = normals.at (normal_index[2] - 1);


                        // Edges of the triangle : position delta
                        auto delta_pos_1 = v1._position - v0._position;
                        auto delta_pos_2 = v2._position - v0._position;

                        // UV delta
                        auto delta_uv1 = uv1 - uv0;
                        auto delta_uv2 = uv2 - uv0;

                        float r = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv1.y * delta_uv2.x);
                        vec3 t = (delta_pos_1 * delta_uv2.y - delta_pos_2 * delta_uv1.y) * r;
                        vec3 b = (delta_pos_2 * delta_uv1.x - delta_pos_1 * delta_uv2.x) * r;

                        //vertex vert0 (v0, n0, uv0, t, b);
                        //vertex vert1 (v1, n1, uv1, t, b);
                        //vertex vert2 (v2, n2, uv2, t, b);
                        v0._normal = n0;
                        v1._normal = n1;
                        v2._normal = n2;

                        v0._tex_coords = uv0;
                        v1._tex_coords = uv1;
                        v2._tex_coords = uv2;

                        v0._tangent = t;
                        v1._tangent = t;
                        v2._tangent = t;

                        v0._tangent = b;
                        v1._tangent = b;
                        v2._tangent = b;
                    }
                }

                // TODO: unnecessary vectors are taking up space. Can be optimized.

                return new mix::assetsystem::mixMesh (path, std::move (vertices), std::move (indices));

            } // namespace loaders
        }     // namespace loaders
    }         // namespace assetsystem
} // namespace mix