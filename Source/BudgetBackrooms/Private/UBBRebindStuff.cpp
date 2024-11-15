#include "UBBRebindStuff.h"
#include "GameFramework/PlayerController.h"

void UBBRebindStuff::ResetInputsToDefault()
{
    if (GEngine)
    {
        if (APlayerController* PC = GEngine->GetFirstLocalPlayerController(GWorld))
        {
            TArray<FInputActionKeyMapping> DefaultActionMappings;
            TArray<FInputAxisKeyMapping> DefaultAxisMappings;

            SetupDefaultActionMappings(DefaultActionMappings);
            SetupDefaultAxisMappings(DefaultAxisMappings);

            ApplyMappingsToPlayerInput(PC, DefaultActionMappings, DefaultAxisMappings);

            // Save the changes
            PC->PlayerInput->SaveConfig();
        }
    }
}

void UBBRebindStuff::SetupDefaultActionMappings(TArray<FInputActionKeyMapping>& ActionMappings)
{

    ActionMappings.Add(FInputActionKeyMapping(FName("debug"), EKeys::Semicolon));


    ActionMappings.Add(FInputActionKeyMapping(FName("Flashlight"), EKeys::F));
    ActionMappings.Add(FInputActionKeyMapping(FName("Flashlight"), EKeys::Gamepad_RightTrigger));
    ActionMappings.Add(FInputActionKeyMapping(FName("Flashlight"), EKeys::RightMouseButton));


    ActionMappings.Add(FInputActionKeyMapping(FName("Interaction"), EKeys::E));
    ActionMappings.Add(FInputActionKeyMapping(FName("Interaction"), EKeys::Gamepad_FaceButton_Left));


    ActionMappings.Add(FInputActionKeyMapping(FName("Jump"), EKeys::Gamepad_FaceButton_Bottom));
    ActionMappings.Add(FInputActionKeyMapping(FName("Jump"), EKeys::SpaceBar));


    ActionMappings.Add(FInputActionKeyMapping(FName("Pause Menu Key"), EKeys::Escape));
    ActionMappings.Add(FInputActionKeyMapping(FName("Pause Menu Key"), EKeys::Gamepad_Special_Right));
    ActionMappings.Add(FInputActionKeyMapping(FName("Pause Menu Key"), EKeys::P));


    ActionMappings.Add(FInputActionKeyMapping(FName("Peek Behind Key"), EKeys::Gamepad_LeftShoulder));
    ActionMappings.Add(FInputActionKeyMapping(FName("Peek Behind Key"), EKeys::V));


    ActionMappings.Add(FInputActionKeyMapping(FName("Run"), EKeys::Gamepad_RightShoulder));
    ActionMappings.Add(FInputActionKeyMapping(FName("Run"), EKeys::LeftShift));


    ActionMappings.Add(FInputActionKeyMapping(FName("Zoom"), EKeys::C));
    ActionMappings.Add(FInputActionKeyMapping(FName("Zoom"), EKeys::Gamepad_LeftTrigger));
}

void UBBRebindStuff::SetupDefaultAxisMappings(TArray<FInputAxisKeyMapping>& AxisMappings)
{

    AxisMappings.Add(FInputAxisKeyMapping(FName("FW/BW"), EKeys::Gamepad_LeftStick_Down, -1.0f));
    AxisMappings.Add(FInputAxisKeyMapping(FName("FW/BW"), EKeys::Gamepad_LeftStick_Up, 1.0f));
    AxisMappings.Add(FInputAxisKeyMapping(FName("FW/BW"), EKeys::S, -1.0f));
    AxisMappings.Add(FInputAxisKeyMapping(FName("FW/BW"), EKeys::W, 1.0f));


    AxisMappings.Add(FInputAxisKeyMapping(FName("LookUp"), EKeys::Gamepad_RightY, 1.0f));
    AxisMappings.Add(FInputAxisKeyMapping(FName("LookUp"), EKeys::MouseY, -1.0f));


    AxisMappings.Add(FInputAxisKeyMapping(FName("R/L"), EKeys::A, -1.0f));
    AxisMappings.Add(FInputAxisKeyMapping(FName("R/L"), EKeys::D, 1.0f));
    AxisMappings.Add(FInputAxisKeyMapping(FName("R/L"), EKeys::Gamepad_LeftStick_Left, -1.0f));
    AxisMappings.Add(FInputAxisKeyMapping(FName("R/L"), EKeys::Gamepad_LeftStick_Right, 1.0f));


    AxisMappings.Add(FInputAxisKeyMapping(FName("Turn"), EKeys::Gamepad_RightX, 1.0f));
    AxisMappings.Add(FInputAxisKeyMapping(FName("Turn"), EKeys::MouseX, 1.0f));
}

void UBBRebindStuff::ApplyMappingsToPlayerInput(APlayerController* PlayerController,
    const TArray<FInputActionKeyMapping>& ActionMappings,
    const TArray<FInputAxisKeyMapping>& AxisMappings)
{
    if (!PlayerController || !PlayerController->PlayerInput)
        return;

    UPlayerInput* PlayerInput = PlayerController->PlayerInput;

    // Clear existing mappings
    PlayerInput->ActionMappings.Empty();
    PlayerInput->AxisMappings.Empty();

    // Apply new default mappings
    for (const FInputActionKeyMapping& Mapping : ActionMappings)
    {
        PlayerInput->AddActionMapping(Mapping);
    }

    for (const FInputAxisKeyMapping& Mapping : AxisMappings)
    {
        PlayerInput->AddAxisMapping(Mapping);
    }

    // Rebuild input mappings
    PlayerInput->ForceRebuildingKeyMaps();
}