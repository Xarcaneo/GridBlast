#include "Engine.h"

Engine::Engine(const char* windowTitle, int width, int height)
    : window(nullptr), isRunning(true), lastTime(0.0), nbFrames(0) {
    // Create and initialize the Window instance
    window = new Window(windowTitle, width, height);
}

Engine::~Engine() {
    Cleanup();
}

void Engine::Run() {
    while (isRunning && !window->ShouldClose()) {
        ProcessInput();
        Update();
        Render();

        window->SwapBuffers();
        window->PollEvents();

        // FPS calculation
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) {
            std::cout << 1000.0 / double(nbFrames) << " ms/frame\n";
            nbFrames = 0;
            lastTime += 1.0;
        }
    }

    Cleanup();
}

void Engine::ProcessInput() {
    if (glfwGetKey(window->GetGLFWwindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window->GetGLFWwindow(), true);
    }
}

void Engine::Update() {
    // Update game logic here
}

void Engine::Render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Render objects here

    // ...
}

void Engine::Cleanup() {
    delete window;
    window = nullptr;  // Avoid double deletion
}
