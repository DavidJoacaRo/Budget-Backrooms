#pragma once

#include "OnlineSubsystemSteam.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"
#include "ThirdParty/Steamworks/Steamv151/sdk/public/steam/steam_api.h"
#include "UBBSteamUtils.generated.h"



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
    GENERATED_BODY()

public:
    UBBSteamUtils();  // Constructor declaration

    UFUNCTION(BlueprintCallable, Category = "Steam")
    static void SetSteamOverlayNotificationPosition(ESteamNotificationPosition Position);
};
