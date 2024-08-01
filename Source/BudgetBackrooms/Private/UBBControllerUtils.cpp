#include "UBBControllerUtils.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/InputSettings.h"
#include "GenericPlatform/GenericPlatformDriver.h"

void UBBControllerUtils::IsGamepadConnected(bool& IsGamepadAttached)
{
    auto genericApplication = FSlateApplication::Get().GetPlatformApplication();

    IsGamepadAttached = genericApplication.Get() != nullptr && genericApplication->IsGamepadAttached();

}
