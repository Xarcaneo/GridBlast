#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "IResourceService.h"
#include "InputManager.h" 
#include <chrono>

class Engine {
public:
    // Constructor and Destructor
    Engine(const char* windowTitle, int width, int height);
    ~Engine();

    // Public Methods
    void Run();           // Starts the main loop

private:
    void ProcessInput();  // Input handling
    void Update();        // Game logic update
    void Render();        // Rendering logic
    void Cleanup();       // Cleanup resources
    void CalculateDeltaTime(); // New method for delta time calculation

    // Private Members
    Window* window;       // Pointer to the Window object
    bool isRunning;       // Is the engine running?

    // FPS tracking
    double lastTime;
    int nbFrames;

    std::chrono::high_resolution_clock::time_point lastFrameTime;
    double deltaTime;        // Member variable to store delta time

    InputManager inputManager;  // InputManager to handle all input
};

#endif // ENGINE_H
