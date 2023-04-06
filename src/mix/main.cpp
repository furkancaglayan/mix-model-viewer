#include "editor/mixEditor.h"
#include <GL/glew.h>
#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <imgui.h>
#include <iostream>
#include <memory>
#include <stb_image.h>

// Include all GLM extensions
#include <glm/ext.hpp> // perspective, translate, rotate

glm::mat4 transform (glm::vec2 const& Orientation, glm::vec3 const& Translate, glm::vec3 const& Up)
{
    glm::mat4 Proj = glm::perspective (glm::radians (45.f), 1.33f, 0.1f, 10.f);
    glm::mat4 ViewTranslate = glm::translate (glm::mat4 (1.f), Translate);
    glm::mat4 ViewRotateX = glm::rotate (ViewTranslate, Orientation.y, Up);
    glm::mat4 View = glm::rotate (ViewRotateX, Orientation.x, Up);
    glm::mat4 Model = glm::mat4 (1.0f);
    return Proj * View * Model;
}

int main ()
{
    int width, height, channels;
    unsigned char* img = stbi_load ("sky.jpg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf ("Error in loading the image\n");
        exit (1);
    }
    printf ("Loaded image with a width of %dpx, a height of %dpx and %d "
            "channels\n",
            width, height, channels);

    GLenum err;
    if (!glfwInit ())
    {
        std::cout << "GLFW INIT ERROR!";
    }
    glewExperimental = true;
    if ((err = glewInit ()) != GLEW_OK)
    {
        std::cout << glewGetErrorString (err) << std::endl;
    }

    mix::mixEditor::create_new ();
    while (mix::mixEditor::_instance->_should_run)
    {
        mix::mixEditor::_instance->run ();
    }
}