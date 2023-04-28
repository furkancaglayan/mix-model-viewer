#version 330 core
layout (location = 0) in vec3 pos;   // the position variable has attribute position 0
layout (location = 1) in vec4 color; // the color variable has attribute position 1
uniform mat4 Model = mat4(1);
uniform mat4 View = mat4(1);
uniform mat4 Projection = mat4(1);  
out vec4 ourColor; // output a color to the fragment shader

void main()
{
    mat4 MVP = Projection * View * Model;

    gl_Position = MVP * vec4(pos, 1);
	
    ourColor = color; // set ourColor to the input color we got from the vertex data
} 