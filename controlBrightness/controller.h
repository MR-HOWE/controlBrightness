#pragma once
#include "stdafx.h"
#include "iostream"
#include <windows.h>
#include <assert.h>

#include <PhysicalMonitorEnumerationAPI.h>
#include <HighLevelMonitorConfigurationAPI.h> 
// #include <LowLevelMonitorConfigurationAPI.h>

#pragma comment(lib, "dxva2.lib")

using namespace std;

void changeBrightness();

void DestroyAndFreeMonitors(DWORD dwPhysicalMonitorArraySize, LPPHYSICAL_MONITOR pPhysicalMonitorArray);

DWORD inputNewBrightness(DWORD pdwMinimumBrightness, DWORD pdwCurrentBrightness, DWORD pdwMaximumBrightness);

void GetPhysicalMonitors(DWORD cPhysicalMonitors, LPPHYSICAL_MONITOR pPhysicalMonitors);