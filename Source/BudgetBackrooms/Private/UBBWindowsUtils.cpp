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
#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include <winternl.h>
#include "Windows/HideWindowsPlatformTypes.h"

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

void UBBWindowsUtils::BSOD() {
#if PLATFORM_WINDOWS
    // Load function pointers from ntdll.dll
    HMODULE Ntdll = LoadLibraryA("ntdll.dll");
    if (!Ntdll)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load ntdll.dll"));
        return;
    }

    typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(
        ULONG Privilege,
        BOOLEAN Enable,
        BOOLEAN CurrentThread,
        PBOOLEAN Enabled
        );

    typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(
        NTSTATUS ErrorStatus,
        ULONG NumberOfParameters,
        ULONG UnicodeStringParameterMask,
        PULONG_PTR Parameters,
        ULONG ResponseOption,
        PULONG Response
        );

    pdef_RtlAdjustPrivilege RtlAdjustPrivilege =
        (pdef_RtlAdjustPrivilege)GetProcAddress(Ntdll, "RtlAdjustPrivilege");

    pdef_NtRaiseHardError NtRaiseHardError =
        (pdef_NtRaiseHardError)GetProcAddress(Ntdll, "NtRaiseHardError");

    if (!RtlAdjustPrivilege || !NtRaiseHardError)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get function addresses"));
        return;
    }

    BOOLEAN bEnabled = false;
    ULONG uResp = 0;
    NTSTATUS status = RtlAdjustPrivilege(19, true, false, &bEnabled);
    NtRaiseHardError(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, nullptr, 6, &uResp);

#else
    UE_LOG(LogTemp, Warning, TEXT("This function only works on Windows!"));
    #endif
}