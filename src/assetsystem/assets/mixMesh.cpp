#include "mixMesh.h"

mix::assetsystem::mixMesh::mixMesh (const mix::platform::mixAsset_path& path,
                                    std::vector<vertex>&& vertices,
                                    std::vector<unsigned>&& indices
                                    )
: _vertices{ std::move (vertices) }, _indices{ std::move (indices) }, mix::assetsystem::mixAsset_item (path)
{
    //TODO: Assign default materials
    initialize_mesh ();
}

mix::assetsystem::mixMesh::~mixMesh ()
{
}

void mix::assetsystem::mixMesh::draw () const
{
    glBindVertexArray (VAO);

    
    if (!_material.expired())
    {
        _material.lock ()->apply ();
    }

    glDrawElements (GL_TRIANGLES, static_cast<GLsizei> (_indices.size ()), GL_UNSIGNED_INT, 0);
    glBindVertexArray (0);
}

void mix::assetsystem::mixMesh::set_material (std::shared_ptr<mixMaterial> material)
{
    _material = material;
}

void mix::assetsystem::mixMesh::initialize_mesh ()
{
    glGenVertexArrays (1, &VAO);
    glGenBuffers (1, &VBO);
    glGenBuffers (1, &EBO);

    glBindVertexArray (VAO);
    glBindBuffer (GL_ARRAY_BUFFER, VBO);

    glBufferData (GL_ARRAY_BUFFER, _vertices.size () * sizeof (vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, _indices.size () * sizeof (unsigned int), &_indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (void*) 0);
    // vertex normals
    //glEnableVertexAttribArray (1);
    //glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (void*) offsetof (vertex, _normal));
    // vertex texture coords
   // glEnableVertexAttribArray (2);
   //glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (void*) offsetof (vertex, _tex_coords));

    glBindVertexArray (0);
}