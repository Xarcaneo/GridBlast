#include "Bootstrapper.h"
#include "IRenderService.h"
#include "RenderService.h"
#include "IResourceService.h"
#include "ResourceManager.h"
#include "ICameraService.h"
#include "CameraService.h"

void Bootstrapper::Setup()
{
    // Initialize the default service locator.
    ServiceRegistry::getInstance();

    // Register Services.
    ServiceRegistry::getInstance().registerService<IRenderService>(std::make_shared<RenderService>());
    ServiceRegistry::getInstance().registerService<IResourceService>(std::make_shared<ResourceManager>());
    ServiceRegistry::getInstance().registerService<ICameraService>(std::make_shared<CameraService>());
}
