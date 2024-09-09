#include "InputManager.h"

InputManager::InputManager() {
    // Initialize the state of the keys you care about (e.g., P, Enter, etc.)

    keyStates[GLFW_KEY_P] = false;
    keyStates[GLFW_KEY_ENTER] = false;
    keyStates[GLFW_MOUSE_BUTTON_LEFT] = false;
    keyStates[GLFW_KEY_W] = false;
    keyStates[GLFW_KEY_S] = false;
    keyStates[GLFW_KEY_A] = false;
    keyStates[GLFW_KEY_D] = false;
    keyStates[GLFW_KEY_ESCAPE] = false;

    keyPressed[GLFW_KEY_P] = false;
    keyPressed[GLFW_KEY_ENTER] = false;
    keyPressed[GLFW_MOUSE_BUTTON_LEFT] = false;
    keyPressed[GLFW_KEY_W] = false;
    keyPressed[GLFW_KEY_S] = false;
    keyPressed[GLFW_KEY_A] = false;
    keyPressed[GLFW_KEY_D] = false;
    keyPressed[GLFW_KEY_ESCAPE] = false;
}

void InputManager::Update(GLFWwindow* window) {
    // Iterate over the registered keys and mouse buttons
    for (auto& keyState : keyStates) {
        int key = keyState.first;
        bool& isPressed = keyState.second;

        // Check if it's a mouse button or a keyboard key
        if (key >= GLFW_MOUSE_BUTTON_1 && key <= GLFW_MOUSE_BUTTON_LAST) {
            // Mouse button handling
            if (glfwGetMouseButton(window, key) == GLFW_PRESS) {
                if (!isPressed) {
                    // Mouse button just transitioned from "not pressed" to "pressed"
                    isPressed = true;
                    keyPressed[key] = true;  // Set the one-time press signal
                }
                else {
                    // Mouse button is being held
                    keyPressed[key] = false;
                }
            }
            else {
                // Mouse button released, reset state
                isPressed = false;
                keyPressed[key] = false;
            }
        }
        else {
            // Keyboard key handling
            if (glfwGetKey(window, key) == GLFW_PRESS) {
                if (!isPressed) {
                    // Key just transitioned from "not pressed" to "pressed"
                    isPressed = true;
                    keyPressed[key] = true;  // Set the one-time press signal
                }
                else {
                    // Key is being held, not a new press
                    keyPressed[key] = false;
                }
            }
            else {
                // Key is released, reset state
                isPressed = false;
                keyPressed[key] = false;
            }
        }
    }
}


bool InputManager::IsKeyPressed(int key) {
    // Return true only if the key was just pressed
    return keyPressed[key];
}

bool InputManager::IsKeyHeld(int key) {
    // Return true if the key is currently being held down
    return keyStates[key];
}
