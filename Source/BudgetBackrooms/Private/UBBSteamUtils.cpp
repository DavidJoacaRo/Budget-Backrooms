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
}

void UBBSteamUtils::SetSteamRichPresence(const FString& Key, const FString& Value)
{
    if (SteamAPI_Init()) {


        SteamFriends()->SetRichPresence(TCHAR_TO_UTF8(*Key), TCHAR_TO_UTF8(*Value));
        UE_LOG(LogTemp, Log, TEXT("Steam Rich Presence set: %s = %s"), *Key, *Value);
    }
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Steam API calls are disabled in the Editor."));
    UE_LOG(LogTemp, Warning, TEXT("Steam API calls are disabled in the Editor."));
}


void UBBSteamUtils::OpenSteamOverlayWithURL(const FString& URL)
{
    if (SteamFriends() != nullptr) {  


        const char* SteamURL = TCHAR_TO_ANSI(*URL);


        SteamFriends()->ActivateGameOverlayToWebPage(SteamURL);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Steam API calls are disabled in the Editor."));
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
        UE_LOG(LogTemp, Warning, TEXT("Steam API Initialization failed."));
}
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Steam API calls are disabled in the Editor."));
    UE_LOG(LogTemp, Warning, TEXT("Steam API calls are disabled in the Editor."));
    
}





//Toggles the player's Steam Overlay, nothing fancy.
void UBBSteamUtils::ToggleSteamOverlay()
{
    if (SteamAPI_Init()) {

        SteamFriends()->ActivateGameOverlay("");
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Steam API Initialization failed."));
    }
    UE_LOG(LogTemp, Warning, TEXT("Steam API calls are disabled in the Editor."));
}



//Checks if the player has steam open
void UBBSteamUtils::CheckSteamConnection(bool& bIsConnected)
{
    if (SteamAPI_Init()) {

        bIsConnected = SteamAPI_IsSteamRunning() && SteamUser()->BLoggedOn();
    }
    else {
        bIsConnected = false;
    }
}
