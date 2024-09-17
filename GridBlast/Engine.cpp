#include "Engine.h"
#include "Bootstrapper.h"
#include "MenuManager.h"
#include "Menu.h"
#include "IRenderService.h"
#include "ICameraService.h"

Engine::Engine(const char* windowTitle, int width, int height)
    : window(new Window(windowTitle, width, height)),
    isRunning(true), lastTime(0.0), nbFrames(0), deltaTime(0) {

    auto resourceService = ServiceRegistry::getInstance().getService<IResourceService>();
    resourceService->LoadResourcesFromJSON("../Resource Files/Data/Resources.json");

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

void Engine::Run() {
    while (isRunning && !window->ShouldClose()) {

        CalculateDeltaTime(); // Update deltaTime
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
        MenuManager::Instance().CurrentMenu()->Update(deltaTime);
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

void Engine::CalculateDeltaTime() {
    auto currentFrameTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = currentFrameTime - lastFrameTime;
    deltaTime = elapsedTime.count();  // deltaTime in seconds
    lastFrameTime = currentFrameTime;
}

void Engine::Cleanup() {
    delete window;
    window = nullptr;  // Avoid double deletion
}
