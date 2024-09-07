#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "IResourceService.h"

class Engine {
public:
    // Constructor and Destructor
    Engine(const char* windowTitle, int width, int height);
    ~Engine();

    // Public Methods
    void Run();           // Starts the main loop
    void LoadResources(); // Load all necessary resources

private:
    void ProcessInput();  // Input handling
    void Update();        // Game logic update
    void Render();        // Rendering logic
    void Cleanup();       // Cleanup resources

    // Private Members
    Window* window;       // Pointer to the Window object
    bool isRunning;       // Is the engine running?

    // FPS tracking
    double lastTime;
    int nbFrames;
};

#endif // ENGINE_H
