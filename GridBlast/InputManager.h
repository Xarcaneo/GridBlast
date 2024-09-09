#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputManager {
public:
    // Constructor
    InputManager();

    // Update method to be called every frame to process inputs
    void Update(GLFWwindow* window);

    // Check if key was pressed (one-time signal until key is released)
    bool IsKeyPressed(int key);

    // Check if key is currently held down
    bool IsKeyHeld(int key);

private:
    std::unordered_map<int, bool> keyStates;      // Tracks whether each key is currently pressed
    std::unordered_map<int, bool> keyPressed;     // Tracks if the key was just pressed (one-time signal)
};
