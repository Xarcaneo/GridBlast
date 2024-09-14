#ifndef SHADER_H
#define SHADER_H

#include "Resource.h"
#include <string>
#include <GL/glew.h>
#include <memory>
#include <glm/glm.hpp>

class Shader : public Resource {
public:
    Shader(const std::string& id, const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    bool Load() override;  // Load and compile shaders
    void Use() const;      // Activate the shader program
    GLuint GetProgramID() const;  // Getter for the shader program ID

    // Utility functions to set shader uniforms
    void SetMatrix4(const std::string& name, const glm::mat4& matrix) const;
    void SetVector3f(const std::string& name, const glm::vec3& value) const;
    void SetFloat(const std::string& name, float value) const;

private:
    std::string vertexPath;   // Path to the vertex shader file
    std::string fragmentPath; // Path to the fragment shader file
    GLuint programID;         // OpenGL shader program ID

    GLuint CompileShader(const std::string& shaderCode, GLenum shaderType);
    void Unload();            // Cleanup the shader program
};

#endif // SHADER_H
