#define WIN32_LEAN_AND_MEAN

// #include <windows.h>
#include "main.h"
#include <stdio.h>

typedef enum
{
    false,
    true
} bool;

/*  Windows Procedure Event Handler*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT paintStruct;

    /* Rendering Context */
    static HGLRC hRC;
    /*  Device Context*/
    static HDC hDC;

    char string[] = "HELLO WORLD!";
    /*  Switch message, condition that is met will execute*/
    switch (message)
    {
    /*  Window is being created*/
    case WM_CREATE:
    {
        hDC = GetDC(hwnd);
        hRC = wglCreateContext(hDC);
        wglMakeCurrent(hDC, hRC);
        return 0;
        break;
    }
    /*  Window is closing*/
    case WM_CLOSE:
    {
        PostQuitMessage(0);
        return 0;
        break;
    }
    /*  Window needs update*/
    case WM_PAINT:
    {
        hDC = BeginPaint(hwnd, &paintStruct);
        /*  Set txt color to blue*/
        SetTextColor(hDC, 0x00FF0000);
        /* Display Text in middle of the window */
        TextOut(hDC, 150, 150, string, sizeof(string) - 1);
        EndPaint(hwnd, &paintStruct);
        return 0;
        break;
    }
    default:
    {
        break;
    }
    }
    return (DefWindowProc(hwnd, message, wParam, lParam));
}

void initWindow(WNDCLASSEX *windowClass, HINSTANCE hInstance)
{
    windowClass->cbSize = sizeof(WNDCLASSEX);
    windowClass->style = CS_HREDRAW | CS_VREDRAW;
    windowClass->lpfnWndProc = WndProc;
    windowClass->cbClsExtra = 0;
    windowClass->cbWndExtra = 0;
    windowClass->hInstance = hInstance;
    windowClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass->hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass->hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    windowClass->lpszMenuName = NULL;
    windowClass->lpszClassName = "ChessOnline";
    windowClass->lpszMenuName = NULL;
    windowClass->hIconSm = LoadIcon(NULL, IDI_WINLOGO);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX windowClass; // window class
    HWND hwnd;              // window handle
    MSG msg;                // message
    bool done;              // flag saying when app is complete
    initWindow(&windowClass, hInstance);

    if (!RegisterClassEx(&windowClass))
    {
        printf("Error:%d\n", GetLastError());
        return 0;
    }

    hwnd = CreateWindowEx(NULL,
                          "ChessOnline",
                          "Chess Online",
                          WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU,
                          100,
                          100,
                          400,
                          400,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
    if (!hwnd)
    {
        printf("Error:%d\n", GetLastError());
        return 0;
    }

    done = false;

    while (!done)
    {
        PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
        if (msg.message == WM_QUIT)
        {
            done = true;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}