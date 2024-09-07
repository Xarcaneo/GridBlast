#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.h"

class MainMenu : public Menu {
public:
    MainMenu() = default;
    void OnStart() override; // Initialize the main menu
    void OnOpenMenu() override; // Actions when the main menu is opened
    void Render() const override; // Render the game menu
    void ProcessInput(GLFWwindow* window) override;
};

#endif // MAIN_MENU_H
