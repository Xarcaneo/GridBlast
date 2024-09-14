#include "GameMenu.h"
#include <iostream>
#include "MenuManager.h"

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
    // Render the game menu elements

    // Placeholder: Implement actual rendering logic here for buttons, background, etc.
    // For example, spriteRenderer.Render(buttonTexture, buttonPosition, buttonSize, 0.0f, color);

    //// Render objects here
    gridMap->Render();
}

void GameMenu::ProcessInput(InputManager& inputManager) {
   
    gridMap->GetPlayer()->ProcessInput(inputManager);

    if (inputManager.IsKeyPressed(GLFW_KEY_P) || inputManager.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        MenuManager::Instance().OpenMenu("PauseMenu");
    }
}