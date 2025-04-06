using UnrealBuildTool;

public class BudgetBackrooms : ModuleRules
{
	public BudgetBackrooms(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "RHI" });

        // Uncomment if you are using online features
        PublicDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemSteam", "Steamworks" });

        PublicDependencyModuleNames.AddRange(new string[] { "PakFile", "Projects" });


        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS"); // oh no unsafe code???
    }
}
