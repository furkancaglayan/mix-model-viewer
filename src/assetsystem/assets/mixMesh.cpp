#include "mixMesh.h"

mix::assetsystem::mixMesh::mixMesh (const mix::platform::mixAsset_path& path,
                                    std::vector<vertex>&& vertices,
                                    std::vector<unsigned>&& indices,
                                    mixMaterial&& material)
: _vertices{ std::move (vertices) }, _indices{ std::move (indices) }, _material{ std::move (material) }, mix::assetsystem::mixAsset_item (path)
{
}

mix::assetsystem::mixMesh::~mixMesh ()
{
}

void mix::assetsystem::mixMesh::load ()
{
}
