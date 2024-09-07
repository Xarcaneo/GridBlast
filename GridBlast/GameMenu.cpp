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

    gridMap = std::make_unique<GridMap>(18, 15);
}

void GameMenu::Render() const {
    // Render the game menu elements

    // Placeholder: Implement actual rendering logic here for buttons, background, etc.
    // For example, spriteRenderer.Render(buttonTexture, buttonPosition, buttonSize, 0.0f, color);

    //// Render objects here
    gridMap->Render();
}

void GameMenu::ProcessInput(GLFWwindow* window) {
   
    gridMap->GetPlayer()->ProcessInput(window);

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        std::cout << "Enter key pressed in Game Menu" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        MenuManager::Instance().OpenMenu("MainMenu");
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        MenuManager::Instance().OpenMenu("PauseMenu");
    }
}