#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

class Window {
public:
    // Constructor and Destructor
    Window(const char* title, int width, int height);
    ~Window();

    // Public Methods
    void SwapBuffers();   // Swap buffers (double buffering)
    void PollEvents();    // Poll for input events
    bool ShouldClose();   // Check if the window should close
    glm::mat4 GetProjectionMatrix() const;  // Get the current projection matrix

    // Getters
    GLFWwindow* GetGLFWwindow();  // Get the GLFW window

private:
    const char* title;    // Window title
    int width, height;    // Window dimensions
    GLFWwindow* window;   // Pointer to the GLFW window
    glm::mat4 projectionMatrix; // Projection matrix

    // Private Methods
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    void UpdateProjectionMatrix();
};

#endif // WINDOW_H
