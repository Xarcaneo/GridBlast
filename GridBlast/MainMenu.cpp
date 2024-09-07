#include "MainMenu.h"
#include "MenuManager.h"
#include <iostream>

void MainMenu::OnStart() {
    // Custom initialization logic for MainMenu
    std::cout << "Main Menu Initialized" << std::endl;
}

void MainMenu::OnOpenMenu() {
    // Custom actions when the MainMenu is opened
    std::cout << "Main Menu Opened" << std::endl;
}

void MainMenu::Render() const {
    // Render the main menu elements

    // Placeholder: Implement actual rendering logic here for buttons, background, etc.
    // For example, spriteRenderer.Render(buttonTexture, buttonPosition, buttonSize, 0.0f, color);
}

void MainMenu::ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        std::cout << "Enter key pressed in Main Menu" << std::endl;
    }
    // Add more input handling for menu options

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        MenuManager::Instance().OpenMenu("GameMenu");
    }
}
