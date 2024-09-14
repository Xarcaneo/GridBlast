#include "PauseMenu.h"
#include <iostream>
#include "MenuManager.h"
#include "IResourceService.h"
#include "ServiceRegistry.h"

void PauseMenu::OnStart() {
    // Custom initialization logic for PauseMenu
    InitializeButtons();
    std::cout << "Pause Menu Initialized" << std::endl;
}

void PauseMenu::OnOpenMenu() {
    // Custom actions when the PauseMenu is opened
    std::cout << "Pause Menu Opened" << std::endl;
}

void PauseMenu::Render() const {
    // Render the pause menu elements
    for (const auto& button : buttons) {
        button->Render();
    }
}

void PauseMenu::ProcessInput(InputManager& inputManager) {

    if (inputManager.IsKeyPressed(GLFW_KEY_P) || inputManager.IsKeyPressed(GLFW_KEY_ESCAPE)) {
        MenuManager::Instance().CloseMenu();  // Close the pause menu and return to the game
    }
    // Loop through all buttons and process input for each one
    for (const auto& button : buttons) {
        button->ProcessInput(inputManager);  // Pass window for hover and click detection
    }
}

// Initialize buttons with positions, sizes, and actions
void PauseMenu::InitializeButtons() {
    // Retrieve texture from the resource manager
    std::shared_ptr<Texture> texture = ServiceRegistry::getInstance().getService<IResourceService>()->GetTexture("buttonTexture");
    std::shared_ptr<Font> font = ServiceRegistry::getInstance().getService<IResourceService>()->GetFont("cruiserFont");

    // Create and add buttons to the menu
    auto startButton = std::make_shared<Button>("Resume", *texture, glm::vec2(448.0f, 240.0f), font, 8);
    auto exitButton = std::make_shared<Button>("Main Menu", *texture, glm::vec2(448.0f, 276.0f), font, 8);


    // Assign actions to buttons
    startButton->SetAction([]() {
        // Resume from pause
        MenuManager::Instance().CloseMenu();
        });

    exitButton->SetAction([]() {
        // Code to exit the game
        MenuManager::Instance().OpenMenu("MainMenu");
        });


    // Add buttons to the container
    buttons.push_back(startButton);
    buttons.push_back(exitButton);
}