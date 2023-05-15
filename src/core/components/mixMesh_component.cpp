#include "mixMesh_component.h"

mix::components::mixMesh_component::mixMesh_component (std::shared_ptr<mix::assetsystem::mixMesh> mesh) : _mesh{ mesh }
{
}

void mix::components::mixMesh_component::render (/*mix::scene_management::mixScene* scene,*/ 
                                                 mix::rendering::rendering_context* rendering,
                                                 const mix::core::mixTransform* transform)
{
    if (!_mesh.expired())
    {
        glBindVertexArray (_mesh.lock ()->get_vao ());
        _mesh.lock ()->draw (rendering);
        rendering->set_mat3 ("_model", transform->get_model_mat ());
        //scene->set_parameters (rendering);
        glDrawElements (GL_TRIANGLES, static_cast<GLsizei> (_mesh.lock ()->get_indices ().size ()), GL_UNSIGNED_INT, 0);
        glBindVertexArray (0);
    }
}
