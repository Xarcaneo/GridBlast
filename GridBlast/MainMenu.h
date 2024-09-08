#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.h"
#include "Button.h"
#include <vector>
#include <memory> 

class MainMenu : public Menu {
public:
    MainMenu() = default;
    void OnStart() override; // Initialize the main menu
    void OnOpenMenu() override; // Actions when the main menu is opened
    void Render() const override; // Render the game menu
    void ProcessInput(GLFWwindow* window) override;

private:
    std::vector<std::shared_ptr<Button>> buttons;  // Container for buttons
    void InitializeButtons();  // Helper function to initialize buttons
};

#endif // MAIN_MENU_H
