

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HardwareData.generated.h"

/**
 * 
 */
UCLASS()
class BUDGETBACKROOMS_API UHardwareData : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category = "HardwareData")
		static void IsGamepadConnected(bool& IsGamepadConnected);
};
