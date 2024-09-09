#include "MainMenu.h"
#include "MenuManager.h"
#include <iostream>
#include "ServiceRegistry.h"
#include "IResourceService.h"

void MainMenu::OnStart() {
    // Custom initialization logic for MainMenu
    InitializeButtons();
    std::cout << "Main Menu Initialized" << std::endl;
}

void MainMenu::OnOpenMenu() {
    // Custom actions when the MainMenu is opened
    std::cout << "Main Menu Opened" << std::endl;
}

void MainMenu::Render() const {
    for (const auto& button : buttons) {
        button->Render();
    }
}

void MainMenu::ProcessInput(GLFWwindow* window) {
    // Loop through all buttons and process input for each one
    for (const auto& button : buttons) {
        button->ProcessInput(window);  // Pass window for hover and click detection
    }
}

// Initialize buttons with positions, sizes, and actions
void MainMenu::InitializeButtons() {
    // Retrieve texture from the resource manager
    std::shared_ptr<Texture> texture = ServiceRegistry::getInstance().getService<IResourceService>()->GetTexture("buttonTexture");
    std::shared_ptr<Font> font = ServiceRegistry::getInstance().getService<IResourceService>()->GetFont("cruiserFont");

    // Create and add buttons to the menu
    auto startButton = std::make_shared<Button>("Start Game", *texture, glm::vec2(448.0f, 240.0f), font, 8);
    auto exitButton = std::make_shared<Button>("Exit", *texture, glm::vec2(448.0f, 276.0f), font, 8);


    // Assign actions to buttons
    startButton->SetAction([]() {
        // Switch to GameMenu or start a new game here
        MenuManager::Instance().OpenMenu("GameMenu");
        });

    exitButton->SetAction([]() {
        // Code to exit the game
        glfwSetWindowShouldClose(glfwGetCurrentContext(), true);  // Close the window
        });


    // Add buttons to the container
    buttons.push_back(startButton);
    buttons.push_back(exitButton);
}