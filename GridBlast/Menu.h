#ifndef MENU_H
#define MENU_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "InputManager.h"

class Menu {
public:
    virtual ~Menu() = default;
    virtual void OnStart() {} // Called when the menu is initialized
    virtual void OnOpenMenu() {} // Called when the menu is opened
    virtual void Render() const = 0; // Pure virtual method for rendering the menu  
    virtual void Update() {} 

    // New: Process input for the menu
    virtual void ProcessInput(InputManager& inputManager) {}

    void SetActive(bool active) { isActive = active; }
    bool IsActive() const { return isActive; }

private:
    bool isActive = false; // Is the menu currently active
};
#endif // MENU_H