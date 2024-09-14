#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "GridMap.h"
#include "Menu.h"

class GameMenu : public Menu {
public:
    GameMenu() = default;
    void OnStart() override; // Initialize the game menu
    void OnOpenMenu() override; // Actions when the game menu is opened
    void Render() const override; // Render the main menu
    void Update(float deltaTime) override;
    void ProcessInput(InputManager& inputManager) override;

private:
    std::unique_ptr<GridMap> gridMap; // Grid map instance

    void UpdateCamera();
};

#endif // GAME_MENU_H
