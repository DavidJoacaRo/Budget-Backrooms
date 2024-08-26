#include "HardwareData.h"

/*
void UHardwareData::IsGamepadConnected(bool& IsGamepadConnected)
{

    auto genericApplication = FSlateApplication::Get().GetPlatformApplication();
    
    IsGamepadConnected = genericApplication.Get() != nullptr && genericApplication->IsGamepadAttached();
}
*/

void UHardwareData::GetCpuInformation(FHardwareData_CpuInfo& CpuInformation)
{
    CpuInformation.CpuBrand = FPlatformMisc::GetCPUBrand();
    CpuInformation.CpuCores = FPlatformMisc::NumberOfCores();
    CpuInformation.CpuUsage = FPlatformTime::GetCPUTime().CPUTimePct;
}

void UHardwareData::GetGpuInformation(FHardwareData_GpuInfo& GpuInformation)
{
    FGPUDriverInfo driverInfo = FPlatformMisc::GetGPUDriverInfo(GRHIAdapterName);

    GpuInformation.PrimaryGpuBrand = FPlatformMisc::GetPrimaryGPUBrand();
    GpuInformation.ProviderName = driverInfo.ProviderName;
    GpuInformation.DriverVersion = driverInfo.UserDriverVersion;
    GpuInformation.DriverDate = driverInfo.DriverDate;
    GpuInformation.RHIName = GDynamicRHI->GetName();
}
