// Copyright (C) 2022 Leon Etzel - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "UWPGameViewportClient.generated.h"

/**
 * This GameViewportClient catches the WindowCloseRequest and handles according to the set rule,
 * if the window is allowed to close (closes game) or not (fires a Handle so you know the player pressed ALT + F4, wanted to
 * close the game via the taskbar or the X of the Game Window)
 */
DECLARE_DYNAMIC_DELEGATE(FOnUserWindowCloseRequested);

static FOnUserWindowCloseRequested UserWindowCloseRequested;

UCLASS(BlueprintType, Category = "Ultimate Window Police")
class ULTIMATEWINDOWPOLICE_API UUWPGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()

	virtual bool WindowCloseRequested() override;

public:

	/**
	 * Allow / Disallow the user to close the window without being stopped.
	 */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Window Police")
	static void SetAllowWindowClose(bool bAllowWindowClose);

	/**
     * Can be used to check if the user is currently allowed to close the window without being stopped.
     */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Window Police")
	static bool GetAllowWindowClose();

	/**
     * Bind this Event for example in your UI, so when the user requests the close you can open up a
     * "Do you really want to quit?" window we all love.
     */
	UFUNCTION(BlueprintCallable, Category = "Ultimate Window Police")
	static void BindOnUserWindowCloseRequested(FOnUserWindowCloseRequested OnUserWindowCloseRequested);

private:
	static bool bAllowWindowClosing;
};