#include "Window.h"
#include <glm/gtc/matrix_transform.hpp>

Window::Window(const char* title, int width, int height)
    : title(title), width(width), height(height), window(nullptr) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);  // Alternatively, you could throw an exception
    }

    // Set GLFW options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);  // Alternatively, you could throw an exception
    }

    // Set the OpenGL context to the window
    glfwMakeContextCurrent(window);

    // Set the window user pointer to this instance for callback usage
    glfwSetWindowUserPointer(window, this);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);  // Alternatively, you could throw an exception
    }

    // Set the viewport and initial projection matrix
    glViewport(0, 0, width, height);
    UpdateProjectionMatrix();

    // Set the callback for window resize
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

void Window::PollEvents() {
    glfwPollEvents();
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(window);
}

GLFWwindow* Window::GetGLFWwindow() {
    return window;
}

glm::mat4 Window::GetProjectionMatrix() const {
    return projectionMatrix;
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Adjust the viewport and projection matrix when the window is resized
    glViewport(0, 0, width, height);
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (win) {
        win->UpdateProjectionMatrix();
    }
}

void Window::UpdateProjectionMatrix() {
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    // Set orthoHeight based on your window's height (360 units)
    float orthoHeight = static_cast<float>(height);  // Set to 360.0f for 360 units height
    float orthoWidth = static_cast<float>(width);    // Set to 640.0f for 640 units width

    // Set the projection matrix
    projectionMatrix = glm::ortho(0.0f, orthoWidth, orthoHeight, 0.0f, -1.0f, 1.0f);
}
