#include "PauseMenu.h"
#include <iostream>
#include "MenuManager.h"

void PauseMenu::OnStart() {
    // Custom initialization logic for PauseMenu
    std::cout << "Pause Menu Initialized" << std::endl;
}

void PauseMenu::OnOpenMenu() {
    // Custom actions when the PauseMenu is opened
    std::cout << "Pause Menu Opened" << std::endl;
}

void PauseMenu::Render() const {
    // Render the pause menu elements

    // Placeholder: Implement actual rendering logic here for buttons, background, etc.
    // For example:
    // spriteRenderer.Render(buttonTexture, buttonPosition, buttonSize, 0.0f, color);
}

void PauseMenu::ProcessInput(GLFWwindow* window) {
    // Process inputs for the pause menu
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        std::cout << "Unpausing the game from Pause Menu" << std::endl;
        MenuManager::Instance().CloseMenu();  // Close the pause menu and return to the game
    }
}
