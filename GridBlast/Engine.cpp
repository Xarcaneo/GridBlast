#include "Engine.h"
#include "Bootstrapper.h"
#include "MenuManager.h"
#include "Menu.h"
#include "IRenderService.h"
#include "ICameraService.h"

Engine::Engine(const char* windowTitle, int width, int height)
    : window(new Window(windowTitle, width, height)),
    isRunning(true), lastTime(0.0), nbFrames(0) {
    LoadResources();  // Load resources during engine initialization

    auto retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    retrievedRenderService->setTileSize(glm::vec2(32.0f, 32.0f));
    retrievedRenderService->setProjectionMatrix(window->GetProjectionMatrix());
    retrievedRenderService->setViewportSize(glm::ivec2(width, height));
    retrievedRenderService->setWindow(window->GetGLFWwindow());
    retrievedRenderService->SetupMatricesForRendering(false);

    // Initialize and run the menu manager
    MenuManager::Instance().InitializeMenus();
}

Engine::~Engine() {
    Cleanup();
}
void Engine::LoadResources() {
    auto resourceService = ServiceRegistry::getInstance().getService<IResourceService>();

    // Load textures
    resourceService->LoadTexture("borderTiles", "D:/GitHub/GridBlast/Resource Files/Textures/border_tiles.png");
    resourceService->LoadTexture("buttonTexture", "D:/GitHub/GridBlast/Resource Files/Textures/Button.png");

    // Load fonts
    resourceService->LoadFont("cruiserFont", "D:/GitHub/GridBlast/Resource Files/Fonts/Cruiser.ttf");

    // Load shaders
    resourceService->LoadShader("spriteShader", "D:/GitHub/GridBlast/Resource Files/Shaders/sprite.vert", "D:/GitHub/GridBlast/Resource Files/Shaders/sprite.frag");
    resourceService->LoadShader("textShader", "D:/GitHub/GridBlast/Resource Files/Shaders/text.vert", "D:/GitHub/GridBlast/Resource Files/Shaders/text.frag");
}

void Engine::Run() {
    while (isRunning && !window->ShouldClose()) {
        ProcessInput();
        Update();
        Render();

        window->SwapBuffers();
        window->PollEvents();

        // FPS calculation
        //double currentTime = glfwGetTime();
        //nbFrames++;
        //if (currentTime - lastTime >= 1.0) {
        //    std::cout << 1000.0 / double(nbFrames) << " ms/frame\n";
        //    nbFrames = 0;
        //    lastTime += 1.0;
        //}
    }

    Cleanup();
}

void Engine::ProcessInput() {
    inputManager.Update(window->GetGLFWwindow());

    if (MenuManager::Instance().CurrentMenu()) {
        MenuManager::Instance().CurrentMenu()->ProcessInput(inputManager);
    }
}

void Engine::Update() {
    if (MenuManager::Instance().CurrentMenu()) {
        MenuManager::Instance().CurrentMenu()->Update();
    }
}

void Engine::Render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render game objects here (menus, sprites, etc.)
    if (MenuManager::Instance().CurrentMenu()) {
        MenuManager::Instance().CurrentMenu()->Render();
    }
}

void Engine::Cleanup() {
    delete window;
    window = nullptr;  // Avoid double deletion
}
