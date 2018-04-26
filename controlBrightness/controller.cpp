#include "stdafx.h"
#include "controller.h"

void changeBrightness()
{
	HMONITOR hMonitor = NULL;
	DWORD cPhysicalMonitors;
	LPPHYSICAL_MONITOR pPhysicalMonitors = NULL;

	// Get the monitor handle.
	hMonitor = MonitorFromWindow(NULL, MONITOR_DEFAULTTOPRIMARY);

	// Get the number of physical monitors.
	BOOL bSuccess = GetNumberOfPhysicalMonitorsFromHMONITOR(
		hMonitor,
		&cPhysicalMonitors
	);

	if (bSuccess)
	{
		// Allocate the array of PHYSICAL_MONITOR structures.
		pPhysicalMonitors = (LPPHYSICAL_MONITOR)malloc(
			cPhysicalMonitors * sizeof(PHYSICAL_MONITOR));

		if (pPhysicalMonitors != NULL)
		{
			// Get the array.
			bSuccess = GetPhysicalMonitorsFromHMONITOR(
				hMonitor, cPhysicalMonitors, pPhysicalMonitors);

			DWORD pdwMinimumBrightness, pdwCurrentBrightness, pdwMaximumBrightness;

			GetMonitorBrightness(pPhysicalMonitors->hPhysicalMonitor,
				&pdwMinimumBrightness, &pdwCurrentBrightness, &pdwMaximumBrightness);

			DWORD dwNewBrightness = inputNewBrightness(
				pdwMinimumBrightness, pdwCurrentBrightness, pdwMaximumBrightness);

			SetMonitorBrightness(pPhysicalMonitors->hPhysicalMonitor, dwNewBrightness);

			cout << "Success! Now the brightness is " << dwNewBrightness << endl;

			DestroyAndFreeMonitors(cPhysicalMonitors, pPhysicalMonitors);
		}
	}
}


DWORD inputNewBrightness(DWORD pdwMinimumBrightness, DWORD pdwCurrentBrightness, DWORD pdwMaximumBrightness)
{
	cout << "Current brightness: " << pdwCurrentBrightness << endl;
	cout << "The brightness range: [" << pdwMinimumBrightness << "," << pdwMaximumBrightness << "] " << endl;
	cout << "Please input the new brightness you want: " << endl;
	DWORD dwNewBrightness;
	cin >> dwNewBrightness;

	while (dwNewBrightness < pdwMinimumBrightness || dwNewBrightness > pdwMaximumBrightness)
	{
		cout << "Out of range. Please input the new brightness again: " << endl;
		cin >> dwNewBrightness;
	}

	assert(dwNewBrightness >= pdwMinimumBrightness);
	assert(dwNewBrightness <= pdwMaximumBrightness);
	return dwNewBrightness;
}

void DestroyAndFreeMonitors(DWORD dwPhysicalMonitorArraySize, LPPHYSICAL_MONITOR pPhysicalMonitorArray)
{
	// Close the monitor handles.
	DestroyPhysicalMonitors(dwPhysicalMonitorArraySize, pPhysicalMonitorArray);
	
	// Free the array.
	free(pPhysicalMonitorArray);
}