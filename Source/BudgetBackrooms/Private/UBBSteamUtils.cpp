

#include "UBBSteamUtils.h"
#include "CoreMinimal.h"
#include "ThirdParty/Steamworks/Steamv151/sdk/public/steam/steam_api.h"

// Define the constructor
UBBSteamUtils::UBBSteamUtils()
{
    // Constructor implementation (if needed)
}

void UBBSteamUtils::SetSteamOverlayNotificationPosition(ESteamNotificationPosition Position)
{
    // Function implementation
    ENotificationPosition steamPosition = k_EPositionBottomRight;

    switch (Position)
    {
    case ESteamNotificationPosition::TopLeft:
        steamPosition = k_EPositionTopLeft;
        break;
    case ESteamNotificationPosition::TopRight:
        steamPosition = k_EPositionTopRight;
        break;
    case ESteamNotificationPosition::BottomLeft:
        steamPosition = k_EPositionBottomLeft;
        break;
    case ESteamNotificationPosition::BottomRight:
        steamPosition = k_EPositionBottomRight;
        break;
    default:
        break;
    }

    SteamUtils()->SetOverlayNotificationPosition(steamPosition);
}
