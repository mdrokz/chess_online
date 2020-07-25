#include <windows.h>

int SetDisplaySettings(int width, int height, int bits);

void AdjustDisplay(RECT *windowRect, DWORD dwExStyle, DWORD dwStyle, BOOL fullscreen);

int GetDisplayAttributesFromWindow(int attributes[], HWND *hwnd);

int GetDisplayAttributesFromPoint(int attributes[], POINT *pt);