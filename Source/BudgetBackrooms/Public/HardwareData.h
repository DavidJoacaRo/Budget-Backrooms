

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HardwareData_CpuInfo.h"
#include "HardwareData_GpuInfo.h"
#include "GenericPlatform/GenericPlatformDriver.h"
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

	UFUNCTION(BlueprintPure, Category = "HardwareData")
		static void GetCpuInformation(FHardwareData_CpuInfo& CpuInformation);

	UFUNCTION(BlueprintPure, Category = "HardwareData")
		static void GetGpuInformation(FHardwareData_GpuInfo& GpuInformation);
};
