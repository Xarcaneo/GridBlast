#pragma once

#include "Menu.h"
#include "Button.h"

class PauseMenu : public Menu
{
    public:
        PauseMenu() = default;
        void OnStart() override; // Initialize the game menu
        void OnOpenMenu() override; // Actions when the game menu is opened
        void Render() const override; // Render the main menu
        void ProcessInput(InputManager& inputManager) override;
private:
    std::vector<std::shared_ptr<Button>> buttons;  // Container for buttons
    void InitializeButtons();  // Helper function to initialize buttons

};

