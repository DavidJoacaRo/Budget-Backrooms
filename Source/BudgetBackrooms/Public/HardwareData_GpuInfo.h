

#pragma once

#include "CoreMinimal.h"
#include <Math/Float32.h>
#include "HardwareData_GpuInfo.generated.h"

USTRUCT(BlueprintType)
struct FHardwareData_GpuInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardwareData")
        FString PrimaryGpuBrand;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardwareData")
        FString ProviderName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardwareData")
        FString DriverVersion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardwareData")
        FString DriverDate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardwareData")
        FString RHIName;
};
