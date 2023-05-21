#include "mixMesh_component.h"

mix::components::mixMesh_component::mixMesh_component (std::shared_ptr<mix::assetsystem::mixMesh> mesh)
: _mesh{ mesh }, mixComponent ()
{
}

void mix::components::mixMesh_component::render (/*mix::scene_management::mixScene* scene,*/ 
                                                 mix::rendering::rendering_context* rendering,
                                                 const mix::core::mixTransform* transform)
{
    if (!_mesh.expired())
    {
        glBindVertexArray (_mesh.lock ()->get_vao ());
     
        rendering->_active_program = _material.lock ()->apply ();
        
        rendering->set_mat4 ("_model", transform->get_model_mat ());
        mix::scene_management::mixScene::_instance->set_parameters (rendering);

        glDrawElements (GL_TRIANGLES, static_cast<GLsizei> (_mesh.lock ()->get_indices ().size ()), GL_UNSIGNED_INT, 0);
        glBindTexture (GL_TEXTURE_2D, 0);
        glBindVertexArray (0);
    }
}

void mix::components::mixMesh_component::set_material (std::shared_ptr<mix::assetsystem::mixMaterial> material)
{
    _material = material;
}

void mix::components::mixMesh_component::update ()
{
}
