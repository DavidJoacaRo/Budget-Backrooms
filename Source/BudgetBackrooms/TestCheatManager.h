#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "TestCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class BUDGETBACKROOMS_API UTestCheatManager : public UCheatManager
{
	GENERATED_BODY()

		UFUNCTION(Exec, Category = ExecFunctions)
		void something();
	
};
