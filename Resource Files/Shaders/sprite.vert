#version 330 core

layout (location = 0) in vec3 aPos;       // Position attribute
layout (location = 1) in vec2 aTexCoord;  // Texture coordinate attribute

out vec2 TexCoord;  // Pass the texture coordinates to the fragment shader

uniform mat4 model;        // Model matrix (for object transformation)
uniform mat4 projection;   // Projection matrix (for orthographic or perspective projection)

void main()
{
    // Apply projection and model transformation
    gl_Position = projection * model * vec4(aPos, 1.0);
    
    // Pass the texture coordinates to the fragment shader
    TexCoord = aTexCoord;
}
