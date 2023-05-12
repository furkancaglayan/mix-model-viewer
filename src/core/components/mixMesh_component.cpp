#include "mixMesh_component.h"

mix::components::mixMesh_component::mixMesh_component (std::shared_ptr<mixMesh> mesh) : _mesh{ mesh }
{
}

void mix::components::mixMesh_component::render ()
{
    if (!_mesh.expired())
    {
        _mesh.lock ()->draw ();
    }
}
