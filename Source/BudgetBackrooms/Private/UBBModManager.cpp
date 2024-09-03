#include "UBBModManager.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "Interfaces/IPluginManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "PakFile/Public/IPlatformFilePak.h"

TArray<FString> UBBModManager::LoadedMods;

void UBBModManager::LoadAllMods(const FString& ModsDirectory)
{
    // Ensure we have a PakPlatformFile instance
    FPakPlatformFile* PakPlatformFile = new FPakPlatformFile();

    // Chain it with the lower level platform file
    PakPlatformFile->Initialize(&FPlatformFileManager::Get().GetPlatformFile(), TEXT(""));

    // Set it as the current platform file
    FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);

    TArray<FString> PakFiles;

    // Find all .pak files in the specified directory
    IFileManager::Get().FindFilesRecursive(PakFiles, *ModsDirectory, TEXT("*.pak"), true, false);

    if (PakFiles.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No .pak files found in directory: %s"), *ModsDirectory);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Found %d .pak files in directory: %s"), PakFiles.Num(), *ModsDirectory);
    }

    for (const FString& PakFile : PakFiles)
    {
        // Mount each .pak file using the PakPlatformFile instance
        if (PakPlatformFile->Mount(*PakFile, 0, nullptr))
        {
            UE_LOG(LogTemp, Log, TEXT("Mounted .pak file: %s"), *PakFile);
            LoadedMods.Add(FPaths::GetBaseFilename(PakFile));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to mount .pak file: %s"), *PakFile);
        }
    }
}

void UBBModManager::EnableMod(const FString& ModName)
{
    if (!LoadedMods.Contains(ModName))
    {
        FString ModPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Mods"), ModName + TEXT(".pak"));

        // Ensure we use the correct instance of PakPlatformFile
        FPakPlatformFile* PakPlatformFile = static_cast<FPakPlatformFile*>(&FPlatformFileManager::Get().GetPlatformFile());

        if (PakPlatformFile && PakPlatformFile->Mount(*ModPath, 0, nullptr))
        {
            UE_LOG(LogTemp, Log, TEXT("Enabled mod: %s"), *ModName);
            LoadedMods.Add(ModName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to enable mod: %s"), *ModName);
        }
    }
}

void UBBModManager::DisableMod(const FString& ModName)
{
    if (LoadedMods.Contains(ModName))
    {
        FString ModPath = FPaths::Combine(FPaths::ProjectDir(), TEXT("Mods"), ModName + TEXT(".pak"));

        // Use PakPlatformFile to unmount the .pak file
        FPakPlatformFile* PakPlatformFile = static_cast<FPakPlatformFile*>(&FPlatformFileManager::Get().GetPlatformFile());

        if (PakPlatformFile && PakPlatformFile->Unmount(*ModPath))
        {
            UE_LOG(LogTemp, Log, TEXT("Disabled mod: %s"), *ModName);
            LoadedMods.Remove(ModName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to disable mod: %s"), *ModName);
        }
    }
}

void UBBModManager::ListMods(TArray<FString>& ModList)
{
    ModList = LoadedMods;
}
