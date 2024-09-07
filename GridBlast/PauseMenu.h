#pragma once

#include "Menu.h"

class PauseMenu : public Menu
{
    public:
        PauseMenu() = default;
        void OnStart() override; // Initialize the game menu
        void OnOpenMenu() override; // Actions when the game menu is opened
        void Render() const override; // Render the main menu
        void ProcessInput(GLFWwindow* window) override;
};

