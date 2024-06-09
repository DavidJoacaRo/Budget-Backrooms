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

    UFUNCTION(BlueprintCallable, Category = "Steam", meta = (Keywords = "Steam Overlay Position", ToolTip = "Changes in which corner to show Steam Overlay notifications"))
    static void SetSteamOverlayNotificationPosition(ESteamNotificationPosition Position);


    UFUNCTION(BlueprintCallable, Category = "Steam", meta = (ToolTip = "Self-explanatory, toggles the Steam Overlay as if the user pressed SHIFT + TAB"))
    static void ToggleSteamOverlay();


    UFUNCTION(BlueprintCallable, Category = "Steam", meta = (Keywords = "Steam Connection", ToolTip = "Checks whether the player has Steam open, and if the game can do a handshake with the Steam API (aka Initialization)"))
    static void CheckSteamConnection(bool& bIsConnected);  // Updated function with out parameter

};
