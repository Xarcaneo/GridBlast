#include "Button.h"
#include "ServiceRegistry.h"
#include "IRenderService.h"
#include <iostream>

// Static members initialization
SpriteRenderer Button::spriteRenderer;
bool Button::isRendererInitialized = false;

// Constructor
Button::Button(const std::string& label, const Texture& texture, const glm::vec2& position,
    std::shared_ptr<Font> font, unsigned int labelSize)
    : label(label), texture(texture), position(position), state(ButtonState::Default),
    font(font), labelSize(labelSize), action(nullptr) {
    // Initialize the sprite renderer if it's not already initialized
    if (!isRendererInitialized) {
        spriteRenderer.Initialize();
        isRendererInitialized = true;
    }

    // Initialize the TextRenderer and load the font
    textRenderer = std::make_unique<TextRenderer>();
    font->SetFontSize(labelSize);  // Set the font size for the label
    textRenderer->Load(font);  // Load the font that is passed from outside
}

// Set the action callback for the button
void Button::SetAction(std::function<void()> action) {
    this->action = action;
}

void Button::Render() const {
    glm::vec2 buttonSize(64.0f, 16.0f);  // Temporary fixed size for buttons

    // Render the button's texture
    RenderButton(buttonSize);

    // Render the centered text
    RenderCenteredText(buttonSize);
}

void Button::RenderButton(const glm::vec2& buttonSize) const {
    // Get the texture coordinates based on the button state (row/column in texture)
    int row = 0, column = 0;
    std::tie(row, column) = GetTextureRowAndColumn();

    // Render the button texture using the SpriteRenderer
    spriteRenderer.Render(texture, position, buttonSize, 0.0f, glm::vec3(1.0f), row, column);
}

void Button::RenderCenteredText(const glm::vec2& buttonSize) const {
    // Get text size
    glm::vec2 textSize = textRenderer->GetTextSize(label);

    // Calculate the centered position for the text
    float centeredX = position.x + (buttonSize.x - textSize.x) / 2;
    float centeredY = position.y + (buttonSize.y - textSize.y) / 2;

    // Render the text centered
    textRenderer->RenderText(label, centeredX, centeredY, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
}

// Set the button state (Normal, Hovered, Selected, Disabled)
void Button::SetState(ButtonState newState) {
    state = newState;
}

void Button::ProcessInput(GLFWwindow* window) {
    // Get and scale mouse position
    glm::vec2 mousePos = GetScaledMousePosition(window);

    // Check if the cursor is hovering over the button
    if (IsMouseOver(mousePos.x, mousePos.y)) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            SetState(ButtonState::Selected);  // Change state if clicked

            // If the button is selected and has an action, execute it
            if (action) {
                action();
            }
        }
        else {
            SetState(
                ButtonState::Hovered);  // Change state if hovered but not clicked
        }
    }
    else {
        SetState(ButtonState::Default);  // Set to default if not hovered
    }
}

// Helper function to get the scaled mouse position
glm::vec2 Button::GetScaledMousePosition(GLFWwindow* window) const {
    // Retrieve the viewport size from the render service
    std::shared_ptr<IRenderService> retrievedRenderService = ServiceRegistry::getInstance().getService<IRenderService>();
    glm::vec2 viewport = retrievedRenderService->getViewportSize();

    // Get the current mouse position
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Get the current window size
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    // Scale mouse position to the viewport size
    mouseX = (mouseX / windowWidth) * viewport.x;
    mouseY = (mouseY / windowHeight) * viewport.y;

    return glm::vec2(mouseX, mouseY);
}

// Check if the mouse is hovering over the button
bool Button::IsMouseOver(double mouseX, double mouseY) const {
    glm::vec2 buttonSize(64.0f, 16.0f);  // Fixed size
    return (mouseX >= position.x && mouseX <= position.x + buttonSize.x &&
        mouseY >= position.y && mouseY <= position.y + buttonSize.y);
}

// Calculate the texture coordinates offset based on the button's state
std::pair<int, int> Button::GetTextureRowAndColumn() const {
    switch (state) {
    case ButtonState::Default:
        return { 0, 0 };  // First part of the texture (row 0, column 0)
    case ButtonState::Hovered:
        return { 1, 0 };  // Second part (row 1, column 0)
    case ButtonState::Selected:
        return { 2, 0 };  // Third part (row 2, column 0)
    case ButtonState::Disabled:
        return { 3, 0 };  // Fourth part (row 3, column 0)
    default:
        return { 0, 0 };  // Default to normal
    }
}
