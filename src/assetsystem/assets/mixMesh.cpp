#include "mixMesh.h"

mix::assetsystem::mixMesh::mixMesh (const mix::platform::mixAsset_path& path, std::vector<vertex>&& vertices, std::vector<unsigned>&& indices)
: _vertices{ std::move (vertices) }, _indices{ std::move (indices) }, mix::assetsystem::mixAsset_item (path)
{
    // TODO: Assign default materials
    initialize_mesh ();
}

mix::assetsystem::mixMesh::~mixMesh ()
{
    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1, &VBO);
    glDeleteBuffers (1, &EBO);
}


const std::vector<unsigned>& mix::assetsystem::mixMesh::get_indices () const
{
    return _indices;
}

const std::vector<vertex>& mix::assetsystem::mixMesh::get_vertices () const
{
    return _vertices;
}

const unsigned mix::assetsystem::mixMesh::get_vao () const
{
    return VAO;
}

const unsigned mix::assetsystem::mixMesh::get_ebo () const
{
    return EBO;
}

const unsigned mix::assetsystem::mixMesh::get_vbo () const
{
    return VBO;
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
    glEnableVertexAttribArray (1);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (void*) offsetof (vertex, _normal));
    // vertex texture coords
    glEnableVertexAttribArray (2);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof (vertex), (void*) offsetof (vertex, _tex_coords));
    // vertex tangents
    glEnableVertexAttribArray (3);
    glVertexAttribPointer (3, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (void*) offsetof (vertex, _tangent));
    // vertex bitangents
    glEnableVertexAttribArray (4);
    glVertexAttribPointer (4, 3, GL_FLOAT, GL_FALSE, sizeof (vertex), (void*) offsetof (vertex, _bitangent));
    glBindVertexArray (0);
}
