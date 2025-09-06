#include "UBBWindowsUtils.h"
#include "Windows/WindowsHWrapper.h"
#include "Misc/MessageDialog.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Windows/WindowsPlatformMisc.h"
#include "UBBWindowsUtils.h"
#include "Windows/WindowsHWrapper.h"
#include "Misc/MessageDialog.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Windows/WindowsPlatformMisc.h"


void UBBWindowsUtils::LockPC() {
    #if PLATFORM_WINDOWS
    ::LockWorkStation();
    #else

    #endif
};

bool UBBWindowsUtils::IsGameMinimized() {
#if PLATFORM_WINDOWS
    HWND hwnd = GetForegroundWindow();
    if (hwnd)
    {
        DWORD processID;
        GetWindowThreadProcessId(hwnd, &processID);
        return processID != GetCurrentProcessId();
    }
    return true;
#else
    return false;
#endif
}


void UBBWindowsUtils::ForceEnableHDR(bool bEnabled) {
#if PLATFORM_WINDOWS
    // Use Windows API to toggle HDR
    HDC hdc = GetDC(NULL);
    if (hdc)
    {
        DEVMODE devMode = {};
        devMode.dmSize = sizeof(DEVMODE);
        devMode.dmFields = DM_DISPLAYFIXEDOUTPUT;

        if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode))
        {
            if (bEnabled)
            {
                devMode.dmDisplayFixedOutput = DMDFO_DEFAULT;
            }
            else
            {
                devMode.dmDisplayFixedOutput = DMDFO_CENTER;
            }

            ChangeDisplaySettings(&devMode, CDS_UPDATEREGISTRY);
        }
        ReleaseDC(NULL, hdc);
    }
#else

#endif
};


int32 UBBWindowsUtils::ShowWindowsMessageBox(FString Message, FString Title, EWindowsMessageBoxButtons ButtonType) {
#if PLATFORM_WINDOWS
    UINT uType;

    switch (ButtonType)
    {
    case EWindowsMessageBoxButtons::OK:
        uType = MB_OK;
        break;
    case EWindowsMessageBoxButtons::OKCancel:
        uType = MB_OKCANCEL;
        break;
    case EWindowsMessageBoxButtons::YesNo:
        uType = MB_YESNO;
        break;
    case EWindowsMessageBoxButtons::YesNoCancel:
        uType = MB_YESNOCANCEL;
        break;
    case EWindowsMessageBoxButtons::RetryCancel:
        uType = MB_RETRYCANCEL;
        break;
    case EWindowsMessageBoxButtons::AbortRetryIgnore:
        uType = MB_ABORTRETRYIGNORE;
        break;
    default:
        uType = MB_OK;
        break;
    }

    int32 Result = MessageBox(
        NULL,
        *Message,
        *Title,
        uType | MB_ICONINFORMATION
    );

    return Result; // Return the result directly, so you can handle different cases in Blueprint
    #else
    // Fallback for non-Windows platforms
    FText Msg = FText::FromString(Message);
    FText TitleText = FText::FromString(Title);
    FMessageDialog::Open(EAppMsgType::Ok, Msg, &TitleText);
    return 0; // Default fallback value
    #endif
}
