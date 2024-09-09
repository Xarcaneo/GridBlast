#pragma once

#include <functional>
#include <string>
#include <glm/glm.hpp>
#include <memory>
#include "Texture.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include <GLFW/glfw3.h>

// Enumeration for button states
enum class ButtonState {
    Default,
    Hovered,
    Selected,
    Disabled
};

class Button {
public:
    // Constructor to initialize button with label, texture, position, font, and label size
    Button(const std::string& label, const Texture& texture, const glm::vec2& position,
        std::shared_ptr<Font> font, unsigned int labelSize);

    // Render the button (texture and text)
    void Render() const;

    // Handle input and update button state
    void ProcessInput(GLFWwindow* window);

    // State management
    void SetState(ButtonState state);
    ButtonState GetState() const { return state; }

    // Set the action that will be triggered when the button is clicked
    void SetAction(std::function<void()> action);

private:
    // Button properties
    std::string label;                // Label displayed on the button
    glm::vec2 position;               // Button position in screen space
    const Texture& texture;           // Texture (sprite sheet) for the button
    ButtonState state;                // Current state (e.g., Default, Hovered, etc.)

    std::function<void()> action;     // Action to perform when button is clicked

    // Font and text rendering properties
    std::unique_ptr<TextRenderer> textRenderer;  // Renderer for the text
    std::shared_ptr<Font> font;                  // Font used for the button's label
    unsigned int labelSize;                      // Size of the label text

    // Static members shared across all buttons
    static SpriteRenderer spriteRenderer;        // Renderer for the button sprite
    static bool isRendererInitialized;           // Flag to ensure spriteRenderer is initialized once

    // Private helper methods
    std::pair<int, int> GetTextureRowAndColumn() const; // Get the texture coordinates based on button state
    bool IsMouseOver(double mouseX, double mouseY) const; // Check if the mouse is over the button
    glm::vec2 GetScaledMousePosition(GLFWwindow* window) const; // Get mouse position scaled to screen

    // Render methods for button parts
    void RenderButton(const glm::vec2& buttonSize) const;  // Render button texture
    void RenderCenteredText(const glm::vec2& buttonSize) const; // Render centered label text
};
