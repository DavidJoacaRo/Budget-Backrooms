


#include "HardwareData.h"
#include <Windows.h>
#include ""

void UHardwareData::IsGamepadConnected(bool& IsGamepadConnected)
{

    auto genericApplication = FSlateApplication::Get().GetPlatformApplication();
    if (genericApplication.Get() == nullptr)
    {
        MessageBoxW(0, L"genericApplication not found", 0, 0);
    }
    
    if (genericApplication.Get() != nullptr && genericApplication->IsGamepadAttached())
    {
        IsGamepadConnected = true;
    }
    IsGamepadConnected = false;
}