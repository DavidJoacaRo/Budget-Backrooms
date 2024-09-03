#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UBBModManager.generated.h"

UCLASS()
class BUDGETBACKROOMS_API UBBModManager : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Budget Modding")
    static void LoadAllMods(const FString& ModsDirectory);

    UFUNCTION(BlueprintCallable, Category = "Budget Modding")
    static void EnableMod(const FString& ModName);

    UFUNCTION(BlueprintCallable, Category = "Budget Modding")
    static void DisableMod(const FString& ModName);

    UFUNCTION(BlueprintCallable, Category = "Budget Modding")
    static void ListMods(TArray<FString>& ModList);

private:
    static TArray<FString> LoadedMods;
};

