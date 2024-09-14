#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>  // For glm::value_ptr

Shader::Shader(const std::string& id, const std::string& vertexPath, const std::string& fragmentPath)
    : Resource(id), vertexPath(vertexPath), fragmentPath(fragmentPath), programID(0) {
}

Shader::~Shader() {
    Unload();
}

bool Shader::Load() {
    // Load vertex and fragment shader source code from files
    std::ifstream vertexFile(vertexPath);
    std::ifstream fragmentFile(fragmentPath);
    std::stringstream vertexStream, fragmentStream;

    if (!vertexFile.is_open() || !fragmentFile.is_open()) {
        std::cerr << "Failed to open shader file(s): " << vertexPath << ", " << fragmentPath << std::endl;
        return false;
    }

    vertexStream << vertexFile.rdbuf();
    fragmentStream << fragmentFile.rdbuf();
    std::string vertexCode = vertexStream.str();
    std::string fragmentCode = fragmentStream.str();

    // Compile shaders
    GLuint vertexShader = CompileShader(vertexCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = CompileShader(fragmentCode, GL_FRAGMENT_SHADER);

    // Link the shaders into a program
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Check for linking errors
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Delete the shaders as they're linked into the program now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

GLuint Shader::CompileShader(const std::string& shaderCode, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    const char* code = shaderCode.c_str();
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    // Check for compile errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

void Shader::Use() const {
    glUseProgram(programID);
}

GLuint Shader::GetProgramID() const {
    return programID;
}

// Set a mat4 uniform in the shader
void Shader::SetMatrix4(const std::string& name, const glm::mat4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

// Set a vec3 uniform in the shader
void Shader::SetVector3f(const std::string& name, const glm::vec3& value) const {
    glUniform3f(glGetUniformLocation(programID, name.c_str()), value.x, value.y, value.z);
}

// Set a float uniform in the shader
void Shader::SetFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::Unload() {
    if (programID) {
        glDeleteProgram(programID);
        programID = 0;
    }
}
