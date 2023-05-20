#include "mixTexture.h"
#include <stb_image.h>

mix::assetsystem::mixTexture::mixTexture (const mix::platform::mixAsset_path& path, texture::texture_type type)
: _id{ 0 }, _type{ type }, mixAsset_item (path)
{
    initialize (path);
}

void mix::assetsystem::mixTexture::set_wrapping (texture::texture_wrapping wrapping)
{
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int> (wrapping));
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int> (wrapping));
}

void mix::assetsystem::mixTexture::set_filtering (texture::texture_filtering filtering_min, texture::texture_filtering filtering_mag)
{
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int> (filtering_min));
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int> (filtering_mag));
}

void mix::assetsystem::mixTexture::bind () const
{
    glActiveTexture (GL_TEXTURE0 + static_cast<int> (_type));
    glBindTexture (GL_TEXTURE_2D, _id);
}

void mix::assetsystem::mixTexture::change_type (mix::texture::texture_type t)
{
    assert (t != _type);
    glDeleteTextures (1, &_id);
    _type = t;
    initialize (_path);
}

void mix::assetsystem::mixTexture::initialize (const mix::platform::mixAsset_path& path)
{
    glGenTextures (1, &_id);
    bind ();
    // set the texture wrapping/filtering options (on the currently bound texture object)
    set_wrapping (texture::texture_wrapping::clamp_to_edge);
    set_filtering (mix::texture::texture_filtering::nearest, mix::texture::texture_filtering::linear);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load (path.to_cstr (), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap (GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free (data);
}
