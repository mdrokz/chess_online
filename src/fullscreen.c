#include <windows.h>

int SetDisplaySettings(int width, int height, int bits)
{

    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings); // size for the DEVMODE structure
    dmScreenSettings.dmPelsWidth = width;               // screen width
    dmScreenSettings.dmPelsHeight = height;             // screen height
    dmScreenSettings.dmBitsPerPel = bits;               // bits per pixel
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    /* Change our display settings using the dmScreenSetting struct */
    if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN !=
                                                     DISP_CHANGE_SUCCESSFUL))
    {
        /* Setting display mode failed, switch to windowed */
        MessageBox(NULL, "Display mode failed", NULL, MB_OK);
        return 0;
    }

    return 1;
}

void AdjustDisplay(RECT *windowRect, DWORD dwExStyle, DWORD dwStyle, BOOL fullscreen)
{
    if (fullscreen)
    {
        dwExStyle = WS_EX_APPWINDOW; // window extended style
        dwStyle = WS_POPUP;          // window style
        ShowCursor(FALSE);           // hide mouse pointer
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; // window extended style
        dwStyle = WS_OVERLAPPEDWINDOW;
    }

    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
}

int GetDisplayAttributesFromWindow(int attributes[], HWND *hwnd)
{
    HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);

    MONITORINFO monitorInfo;
    memset(&monitorInfo, 0, sizeof(monitorInfo));
    monitorInfo.cbSize = sizeof(monitorInfo);

    int success = GetMonitorInfo(hMonitor, &monitorInfo);

    if (success)
    {
        attributes[0] = monitorInfo.rcMonitor.right;
        attributes[1] = monitorInfo.rcMonitor.bottom;
    }

    return success;
}

void GetDisplayAttributesFromPoint(int attributes[], POINT *pt)
{
    HMONITOR hMonitor = MonitorFromPoint(*pt, MONITOR_DEFAULTTOPRIMARY);

    MONITORINFO monitorInfo;
    memset(&monitorInfo, 0, sizeof(monitorInfo));
    monitorInfo.cbSize = sizeof(monitorInfo);

    int success = GetMonitorInfo(hMonitor, &monitorInfo);

    if (success)
    {
        attributes[0] = monitorInfo.rcMonitor.right;
        attributes[1] = monitorInfo.rcMonitor.bottom;
    }

    return success;
}