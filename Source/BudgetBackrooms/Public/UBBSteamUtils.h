

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"
//#include "UBBSteamUtils.generated.h"
/**



UENUM(BlueprintType)
enum class ESteamNotificationPosition : uint8
{
    TopLeft UMETA(DisplayName = "Top Left"),
    TopRight UMETA(DisplayName = "Top Right"),
    BottomLeft UMETA(DisplayName = "Bottom Left"),
    BottomRight UMETA(DisplayName = "Bottom Right")
};

UCLASS()
class BUDGETBACKROOMS_API UBBSteamUtils : public UBlueprintFunctionLibrary
{
    GENERATED_UCLASS_BODY() 

public:
    UBBSteamUtils(const FPostConstructInitializeProperties& PCIP);
    UFUNCTION(BlueprintCallable, Category = "Steam")
    static void SetSteamOverlayNotificationPosition(ESteamNotificationPosition Position);
};
 */
