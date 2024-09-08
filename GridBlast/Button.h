#pragma once

#include <functional>
#include <string>
#include <glm/glm.hpp>
#include "Texture.h"
#include "SpriteRenderer.h"
#include <GLFW/glfw3.h>

enum class ButtonState {
    Default,
    Hovered,
    Selected,
    Disabled
};

class Button {
public:
    // Constructor
    Button(const std::string& label, const Texture& texture, const glm::vec2& position);

    // Render method to draw the button on the screen
    void Render() const;
    void ProcessInput(GLFWwindow* window);

    // State management
    void SetState(ButtonState state);
    ButtonState GetState() const { return state; }

    // Set the action to be performed when the button is selected
    void SetAction(std::function<void()> action);

private:
    std::string label;          // Button label text
    glm::vec2 position;         // Button position
    const Texture& texture;     // Button texture (sprite sheet)
    ButtonState state;          // Current state of the button

    std::function<void()> action;  // Function to be executed when the button is selected

    std::pair<int, int> GetTextureRowAndColumn() const; // Helper function to calculate texture coordinates
    bool IsMouseOver(double mouseX, double mouseY) const;

    static SpriteRenderer spriteRenderer; // Shared renderer for buttons
    static bool isRendererInitialized;    // Flag to ensure renderer is initialized once
};
