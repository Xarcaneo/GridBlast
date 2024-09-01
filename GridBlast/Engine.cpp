#include "Engine.h"
#include "SpriteRenderer.h"
#include "GameConfig.h"

Engine::Engine(const char* windowTitle, int width, int height)
    : window(new Window(windowTitle, width, height)), isRunning(true), lastTime(0.0), nbFrames(0) {
    LoadResources();  // Load resources during engine initialization
    GameConfig::SetTileSize(glm::vec2(16.0f, 16.0f));

    //Initialize GridMap with the resource manager
    gridMap = std::make_unique<GridMap>(20, 20, resourceManager);
    gridMap->Initialize();
}

Engine::~Engine() {
    Cleanup();
}
void Engine::LoadResources() {
    // Example of loading a texture
    resourceManager.LoadTexture("borderTiles", "D:/GitHub/GridBlast/Resource Files/Textures/border_tiles.png");

    // Load other resources like sound effects or fonts when added
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

    //// Render objects here
    gridMap->Render();

    // ...
}

void Engine::Cleanup() {
    delete window;
    window = nullptr;  // Avoid double deletion
}
