#include "GameMenu.h"
#include <iostream>
#include "MenuManager.h"
#include "ServiceRegistry.h"
#include "IRenderService.h"
#include "ICameraService.h"

void GameMenu::OnStart() {
    // Custom initialization logic for GameMenu
    std::cout << "Game Menu Initialized" << std::endl;
}

void GameMenu::OnOpenMenu() {
    // Custom actions when the GameMenu is opened
    std::cout << "Game Menu Opened" << std::endl;

    gridMap = std::make_unique<GridMap>();
}

void GameMenu::Render() const {

    auto renderService = ServiceRegistry::getInstance().getService<IRenderService>();
    renderService->SetupMatricesForRendering(true);

    //Render gameplay screen
    gridMap->Render();

    renderService->SetupMatricesForRendering(false);
}

void GameMenu::ProcessInput(InputManager& inputManager) {

    if (gridMap->GetPlayer()) {
        gridMap->GetPlayer()->ProcessInput(inputManager);
    }

    if (inputManager.IsKeyPressed(GLFW_KEY_P) || inputManager.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        MenuManager::Instance().OpenMenu("PauseMenu");
    }
}

void GameMenu::Update(float deltaTime)
{
    gridMap->Update(deltaTime);
    UpdateCamera();
}

// New method to cleanly update the camera position
void GameMenu::UpdateCamera() {

    if (gridMap->GetPlayer()) {
        // Get player position and map size
        auto renderService = ServiceRegistry::getInstance().getService<IRenderService>();
        glm::vec2 tileSize = renderService->getTileSize();
        glm::vec2 playerPosition = gridMap->GetPlayer()->GetPosition();
        glm::vec2 mapSize(gridMap->getMapWidth() * tileSize.x, gridMap->getMapHeight() * tileSize.y);

        // Retrieve the CameraService and clamp the camera to the map bounds
        auto cameraService = ServiceRegistry::getInstance().getService<ICameraService>();
        cameraService->clampCameraToMapBounds(playerPosition, mapSize);
    }
}