#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"
#include "UBBControllerUtils.generated.h"

UCLASS()
class BUDGETBACKROOMS_API UBBControllerUtils : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Function to check if a controller is connected
    UFUNCTION(BlueprintPure, Category = "Budget Controller Utils", meta = (Keywords = "Check Gamepad Connection", ToolTip = "Check if any Gamepad is connected & detected by the OS driver. :nerd:"))
        static void IsGamepadConnected(bool& IsGamepadAttached);

    UFUNCTION(BlueprintCallable, Category = "Budget Controller Utils", meta = (Keywords = "Rumble Gamepad", ToolTip = "Rumbles the connected gamepad for an amount of ms"))
        static void SetControllerVibration(int32 ControllerId, float Intensity, float Duration);
};
