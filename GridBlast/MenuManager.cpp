#include "MenuManager.h"
#include "Menu.h"
#include <iostream>
#include "MainMenu.h"
#include "GameMenu.h"
#include "PauseMenu.h"

MenuManager& MenuManager::Instance() {
    static MenuManager instance;
    return instance;
}

void MenuManager::InitializeMenus() {
    LoadMenus();
    if (menus.find("MainMenu") != menus.end()) {
        OpenMenu("MainMenu");
    }
}

void MenuManager::LoadMenus() {
    menus["MainMenu"] = std::make_shared<MainMenu>();
    menus["GameMenu"] = std::make_shared<GameMenu>();
    menus["PauseMenu"] = std::make_shared<PauseMenu>();

    for (auto& pair : menus) {
        pair.second->OnStart();
        pair.second->SetActive(false); // Initially set all menus to inactive
    }
}

void MenuManager::OpenMenu(const std::string& menuName) {
    auto it = menus.find(menuName);
    if (it == menus.end()) {
        std::cerr << "MENUMANAGER OpenMenu ERROR: invalid menu name '" << menuName << "'" << std::endl;
        return;
    }

    if (!menuStack.empty()) {
        menuStack.top()->SetActive(false);
    }

    auto menuInstance = it->second;
    menuInstance->OnOpenMenu();
    menuInstance->SetActive(true);
    menuStack.push(menuInstance);
}

void MenuManager::CloseMenu() {
    if (menuStack.empty()) {
        std::cerr << "MENUMANAGER CloseMenu ERROR: No menus in stack!" << std::endl;
        return;
    }

    auto topMenu = menuStack.top();
    menuStack.pop();
    topMenu->SetActive(false);

    if (!menuStack.empty()) {
        auto nextMenu = menuStack.top();
        nextMenu->SetActive(true);
    }
}

// Getter for the current active menu
std::shared_ptr<Menu> MenuManager::CurrentMenu() const {
    if (!menuStack.empty()) {
        return menuStack.top();
    }
    return nullptr;
}

// Loop through all opened menus
void MenuManager::ForEachOpenedMenu(const std::function<void(std::shared_ptr<Menu>)>& callback) const {
    std::stack<std::shared_ptr<Menu>> tempStack = menuStack; // Copy the stack
    while (!tempStack.empty()) {
        callback(tempStack.top());
        tempStack.pop();
    }
}