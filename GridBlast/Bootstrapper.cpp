#include "Bootstrapper.h"
#include "IRenderService.h"
#include "RenderService.h"

void Bootstrapper::Setup()
{
    // Initialize the default service locator.
    ServiceRegistry::getInstance();

    // Register Game Mode Service.
    ServiceRegistry::getInstance().registerService<IRenderService>(std::make_shared<RenderService>());
}
