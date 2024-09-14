#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D sdfTexture;
uniform vec3 textColor;

void main() {
    float distance = texture(sdfTexture, TexCoords).r;
    float alpha = smoothstep(0.5 - 0.1, 0.5 + 0.1, distance);  // Adjust the 0.1 value for sharpness
    FragColor = vec4(textColor, alpha);
}