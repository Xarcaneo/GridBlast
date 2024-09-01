#include "Engine.h"
#include "SpriteRenderer.h"

Engine::Engine(const char* windowTitle, int width, int height)
    : window(new Window(windowTitle, width, height)), isRunning(true), lastTime(0.0), nbFrames(0) {
    LoadResources();  // Load resources during engine initialization
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

    // Render objects here
    SpriteRenderer* spriteRenderer = new SpriteRenderer();
    if (!spriteRenderer->Initialize()) {
        std::cerr << "Failed to initialize SpriteRenderer" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Define sprite parameters
    glm::vec2 position(100.0f, 100.0f);  // Example position
    glm::vec2 size(16.0f, 16.0f);      // Example size
    float rotation = 0.0f;               // No rotation
    glm::vec3 color(1.0f, 1.0f, 1.0f);   // White color (no tint)

    // Define the texture coordinates for the top-right tile in the 2x2 grid
    glm::vec2 texCoordsMin(0.0f, 0.5f);  // Bottom-left corner of the top-right tile
    glm::vec2 texCoordsMax(0.5f, 1.0f);  // Top-right corner of the top-right tile


    std::shared_ptr<Texture> texture = resourceManager.GetTexture("borderTiles");

    // Render the sprite using the border texture
    spriteRenderer->Render(*texture, position, size, rotation, color, 1, 1);


    // ...
}

void Engine::Cleanup() {
    delete window;
    window = nullptr;  // Avoid double deletion
}
