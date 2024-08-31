#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
public:
    // Constructor and Destructor
    Window(const char* title, int width, int height);
    ~Window();

    // Public Methods
    void SwapBuffers();   // Swap buffers (double buffering)
    void PollEvents();    // Poll for input events
    bool ShouldClose();   // Check if the window should close

    // Getters
    GLFWwindow* GetGLFWwindow();  // Get the GLFW window

private:
    const char* title;    // Window title
    int width, height;    // Window dimensions
    GLFWwindow* window;   // Pointer to the GLFW window
};

#endif // WINDOW_H
