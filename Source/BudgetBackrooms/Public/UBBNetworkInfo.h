#pragma once
/*
*
* Credits to github.com/Chippy4/NetworkInformation for the original code. 
*
* I just "adapted" it into the game's C++ files because I was too lazy to install the plugins.
* "Adapted" here by DavidJoacaRo
* 
* 
* To be used inside BBWidgetNetworkInfo as a BP/Widget for the variables to work.
* 
*/


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/NetConnection.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UBBNetworkInfo.generated.h"



UCLASS()
class BUDGETBACKROOMS_API UBBNetworkInfo : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Budget Networking");
	int32 OutPacketsPerSecond;

	UPROPERTY(BlueprintReadOnly, Category = "Budget Networking");
	int32 InPacketsPerSecond;

	UPROPERTY(BlueprintReadOnly, Category = "Budget Networking");
	int32 OutBytesPerSecond;

	UPROPERTY(BlueprintReadOnly, Category = "Budget Networking");
	int32 InBytesPerSecond;

	UPROPERTY(BlueprintReadOnly, Category = "Budget Networking");
	int32 OutPacketLoss;

	UPROPERTY(BlueprintReadOnly, Category = "Budget Networking");
	int32 InPacketLoss;

	UPROPERTY(BlueprintReadOnly, Category = "Budget Networking");
	bool bHasValidNetConnection;

	UFUNCTION(BlueprintCallable, Category = "Budget Networking")
	void UpdateNetStats();
};
