//#define _CRT_SECURE_NO_WARNINGS

#include "UBBSteamUtils.h"
#include "CoreMinimal.h"
#include "ThirdParty/Steamworks/Steamv151/sdk/public/steam/steam_api.h"




UBBSteamUtils::UBBSteamUtils()
{
    // what
}


void UBBSteamUtils::MarkContentCorrupt(bool& bMissingFilesOnly) {
    if (SteamAPI_Init()) {
        bool bSuccess = SteamApps()->MarkContentCorrupt(bMissingFilesOnly);
	}
	else
	{

	}
}

void UBBSteamUtils::SetSteamRichPresence(const FString& Key, const FString& Value)
{
	if (SteamAPI_Init()) {
		SteamFriends()->SetRichPresence(TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value));
	}
	else
	{
		
	}
}

void UBBSteamUtils::ClearSteamRichPresence() {
		SteamFriends()->ClearRichPresence();
}


void UBBSteamUtils::OpenSteamOverlayWithURL(const FString& URL)
{
    if (SteamFriends() != nullptr) {  
        const char* SteamURL = TCHAR_TO_UTF8(*URL);
        SteamFriends()->ActivateGameOverlayToWebPage(SteamURL);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[BUDGET STEAM NETWORKING] Steam calls r disabled, why??"));
    }
}

// Notification Position stuff because yeah
void UBBSteamUtils::SetSteamOverlayNotificationPosition(ESteamNotificationPosition Position)
{
    if (SteamAPI_Init()) {

        ENotificationPosition steamPosition;
        switch (Position) {

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
            steamPosition = k_EPositionTopLeft;
            break;
        }

        SteamUtils()->SetOverlayNotificationPosition(steamPosition);
    }
    else
    {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Steam API Initialization failed."));
        UE_LOG(LogTemp, Warning, TEXT("[BUDGET STEAM NETWORKING] Steam API failed, why??"));
}
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Steam API calls are disabled in the Editor."));
    UE_LOG(LogTemp, Warning, TEXT("[BUDGET STEAM NETWORKING] Steam calls r disabled, why??"));
    
}





//Toggles the player's Steam Overlay, nothing fancy.
void UBBSteamUtils::ToggleSteamOverlay()
{
    if (SteamAPI_Init()) {

        SteamFriends()->ActivateGameOverlay("");
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[BUDGET STEAM NETWORKING] Steam API failed, why??"));
    }
    UE_LOG(LogTemp, Warning, TEXT("[BUDGET STEAM NETWORKING] Steam calls r disabled, why??"));
}



//Checks if the player has Steam open
void UBBSteamUtils::CheckSteamConnection(bool& bIsConnected)
{
    if (SteamAPI_Init()) {

        bIsConnected = SteamAPI_IsSteamRunning() && SteamUser()->BLoggedOn();
    }
    else {

    }

}
