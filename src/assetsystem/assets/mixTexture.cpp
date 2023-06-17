#include "mixTexture.h"
#include <stb_image.h>
#include "../../library/debug.h"

mix::assetsystem::mixTexture::mixTexture (const mix::platform::mixAsset_path& path, texture::texture_type type)
: _id{ 0 }, _type{ type }, mixAsset_item (path)
{
    initialize (path, mix::texture::texture_format::rgb);
}

mix::assetsystem::mixTexture::~mixTexture ()
{
    glDeleteTextures (1, &_id);
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
    ASSERT (t != _type);
    glDeleteTextures (1, &_id);
    _type = t;
    initialize (_path, _format);
}

void mix::assetsystem::mixTexture::set_format (mix::texture::texture_format format)
{
    ASSERT (format != _format);
    glDeleteTextures (1, &_id);
    _format = format;
    initialize (_path, _format);
}

unsigned mix::assetsystem::mixTexture::get_id () const
{
    return _id;
}

void mix::assetsystem::mixTexture::initialize (const mix::platform::mixAsset_path& path, mix::texture::texture_format format)
{
    //TODO: move this to config or something like that
    stbi_set_flip_vertically_on_load (true);
    glGenTextures (1, &_id);
    bind ();
    // set the texture wrapping/filtering options (on the currently bound texture object)
    set_wrapping (texture::texture_wrapping::clamp_to_edge);
    set_filtering (mix::texture::texture_filtering::nearest, mix::texture::texture_filtering::nearest);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load (path.to_cstr (), &width, &height, &nrChannels, static_cast<int> (format));
    if (data)
    {
        unsigned f = nrChannels == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D (GL_TEXTURE_2D, 0, f, width, height, 0, f, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap (GL_TEXTURE_2D);
    }
    else
    {
        LOG_ERROR ("Failed to load texture at: " + path.get_name());
    }
    stbi_image_free (data);
}
