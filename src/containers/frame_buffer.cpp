#include "frame_buffer.h"
#include "../library/debug.h"

mix::containers::frame_buffer::frame_buffer (int w, int h)
{
    initialize (w, h);
}

mix::containers::frame_buffer::~frame_buffer ()
{
    glDeleteFramebuffers (1, &_fbo);
    glDeleteTextures (1, &_render_texture);
    glDeleteRenderbuffers (1, &_render_buffer);
}

void mix::containers::frame_buffer::bind () const
{
    glBindFramebuffer (GL_FRAMEBUFFER, _fbo);
}

void mix::containers::frame_buffer::unbind () const
{
    glBindFramebuffer (GL_FRAMEBUFFER, 0);
}

void mix::containers::frame_buffer::rescale (int w, int h) const
{
    glBindTexture (GL_TEXTURE_2D, _render_texture);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _render_texture, 0);

    glBindRenderbuffer (GL_RENDERBUFFER, _render_buffer);
    glRenderbufferStorage (GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _render_buffer);
}

unsigned mix::containers::frame_buffer::get_render_texture () const
{
    return _render_texture;
}

void mix::containers::frame_buffer::initialize (int w, int h)
{
    glGenFramebuffers (1, &_fbo);
    glBindFramebuffer (GL_FRAMEBUFFER, _fbo);

    glGenTextures (1, &_render_texture);
    glBindTexture (GL_TEXTURE_2D, _render_texture);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _render_texture, 0);


    glGenRenderbuffers (1, &_render_buffer);
    glBindRenderbuffer (GL_RENDERBUFFER, _render_buffer);
    glRenderbufferStorage (GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _render_buffer);


    if (glCheckFramebufferStatus (GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ERROR ("Framebuffer is not complete!");
    }
    glBindFramebuffer (GL_FRAMEBUFFER, 0);
    glBindTexture (GL_TEXTURE_2D, 0);
    glBindVertexArray (0);
}
