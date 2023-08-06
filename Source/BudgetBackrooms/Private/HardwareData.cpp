


#include "HardwareData.h"

void UHardwareData::IsGamepadConnected(bool& IsGamepadConnected)
{

    auto genericApplication = FSlateApplication::Get().GetPlatformApplication();
    
    if (genericApplication.Get() != nullptr && genericApplication->IsGamepadAttached())
    {
        IsGamepadConnected = true;
    }
    IsGamepadConnected = false;
}


void UHardwareData::GetCpuInformation(FHardwareData_CpuInfo& CpuInformation)
{
    CpuInformation.CpuBrand = FGenericPlatformMisc::GetCPUBrand();
    CpuInformation.CpuCores = FGenericPlatformMisc::NumberOfCores();
    CpuInformation.CpuUsage = FGenericPlatformTime::GetCPUTime().CPUTimePct;

    
    
}

void UHardwareData::GetGpuInformation(FHardwareData_GpuInfo& GpuInformation)
{
    FGPUDriverInfo driverInfo = FGenericPlatformMisc::GetGPUDriverInfo(GRHIAdapterName);

    GpuInformation.PrimaryGpuBrand = FGenericPlatformMisc::GetPrimaryGPUBrand();
    GpuInformation.ProviderName = driverInfo.ProviderName;
    GpuInformation.DriverVersion = driverInfo.UserDriverVersion;
    GpuInformation.DriverDate = driverInfo.DriverDate;
    GpuInformation.RHIName = driverInfo.RHIName;
}