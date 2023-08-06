#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiscordUtils.generated.h"

/**
 * 
 */
UCLASS()
class BUDGETBACKROOMS_API UDiscordUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category = "Discord Utils")
		static void ConvertDateToUnix(FDateTime date, int64& timestamp);

	UFUNCTION(BlueprintPure, Category = "Discord Utils")
		static void GetRandomString(int32 Length, FString& RandomString);
};
