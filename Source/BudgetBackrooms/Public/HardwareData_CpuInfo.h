#pragma once

#include "CoreMinimal.h"
#include <Math/Float32.h>
#include "HardwareData_CpuInfo.generated.h"

USTRUCT(BlueprintType)
struct FHardwareData_CpuInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardwareData")
        FString CpuBrand;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardwareData")
        int32 CpuCores;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HardwareData")
        float CpuUsage;
};
