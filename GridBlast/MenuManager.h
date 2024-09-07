#pragma once
#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <memory>
#include <stack>
#include <unordered_map>
#include <string>

class Menu;

class MenuManager {
public:
    static MenuManager& Instance(); // Singleton instance

    void InitializeMenus(); // Initialize the menus
    void OpenMenu(const std::string& menuName); // Open a menu by name
    void CloseMenu(); // Close the current menu

    // Publicly accessible current menu
    std::shared_ptr<Menu> CurrentMenu() const;  // Getter for the current menu

private:
    MenuManager() = default; // Private constructor for singleton
    std::stack<std::shared_ptr<Menu>> menuStack; // Stack for managing menus
    std::unordered_map<std::string, std::shared_ptr<Menu>> menus; // Dictionary for menu lookup

    void LoadMenus(); // Load and initialize the menus
};

#endif // MENU_MANAGER_H
