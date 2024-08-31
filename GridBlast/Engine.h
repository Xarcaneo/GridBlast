#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"

class Engine {
public:
    // Constructor and Destructor
    Engine(const char* windowTitle, int width, int height);
    ~Engine();

    // Public Methods
    void Run();           // Starts the main loop
    void Update();        // Update method for game logic
    void Render();        // Render method for drawing

private:
    // Private Methods
    void ProcessInput();  // Handle user input
    void Cleanup();       // Cleanup and free resources

    // Private Members
    Window* window;       // Pointer to the Window object
    bool isRunning;       // Is the engine running?

    // FPS tracking
    double lastTime;
    int nbFrames;
};

#endif // ENGINE_H
