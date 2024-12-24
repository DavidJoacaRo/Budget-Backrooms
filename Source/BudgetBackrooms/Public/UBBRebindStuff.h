#include "CoreMinimal.h"
#include "GameFramework/PlayerInput.h"
#include "UBBRebindStuff.generated.h"

UCLASS()
class BUDGETBACKROOMS_API UBBRebindStuff : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Input|Reset")
    static void ResetInputsToDefault();

private:
    static void SetupDefaultActionMappings(TArray<FInputActionKeyMapping>& ActionMappings);
    static void SetupDefaultAxisMappings(TArray<FInputAxisKeyMapping>& AxisMappings);
    static void ApplyMappingsToPlayerInput(APlayerController* PlayerController,
        const TArray<FInputActionKeyMapping>& ActionMappings,
        const TArray<FInputAxisKeyMapping>& AxisMappings);
};