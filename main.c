#define WIN32_LEAN_AND_MEAN

// #include <windows.h>
#include "main.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>

/* workaround for boolean type in C */
typedef enum
{
    false,
    true
} bool;

/* Function for setting up the pixel format for device context */
void SetupPixelFormat(HDC hDC)
{

    /* Pixel format index */
    int nPixelFormat;

    /* Pixel Format Descriptor */
    static PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR), // size of structure
        1,                             // default version
        PFD_DRAW_TO_WINDOW |           // window drawing support
            PFD_SUPPORT_OPENGL |       // opengl support
            PFD_DOUBLEBUFFER,          // double buffering support
        PFD_TYPE_RGBA,                 // RGBA color mode,
        32,                            // 32 bit color mode
        0, 0, 0, 0, 0, 0,              // ignore color bits
        0,                             // no alpha buffer
        0,                             // ignore shift bit
        0,                             // no accumulation buffer
        0, 0, 0, 0,                    // ignore accumulation bits
        16,                            // 16 bit z-buffer size
        0,                             // no stencil buffer
        0,                             // no aux buffer
        PFD_MAIN_PLANE,                // main drawing plane
        0,                             // reserved
        0, 0, 0                        // layer masks ignored
    };

    /* Choose best matching format */
    nPixelFormat = ChoosePixelFormat(hDC, &pfd);

    /* Set the pixel format to the device context */
    SetPixelFormat(hDC, nPixelFormat, &pfd);
}

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
        /* Get the device context */
        hDC = GetDC(hwnd);
        /* Set Pixel Format for the device context */
        SetupPixelFormat(hDC);
        /* Create OpenGl Context */
        hRC = wglCreateContext(hDC);
        /* Set current rendering context */
        wglMakeCurrent(hDC, hRC);
        break;
    }
    /* Window is being destroyed */
    case WM_DESTROY:
    {
        /* Set current rendering context to nothing */
        wglMakeCurrent(hDC, NULL);
        /* Destroy OpenGl Context */
        wglDeleteContext(hRC);
        /* Message code after application quits */
        PostQuitMessage(0);
        break;
    }
    /*  Window is closing*/
    case WM_CLOSE:
    {
        /* Message code after application quits */
        PostQuitMessage(0);
        return 0;
        break;
    }
    /*  Window needs update*/
    case WM_PAINT:
    {
        hDC = BeginPaint(hwnd, &paintStruct);
        /*  Set text color to blue*/
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
    /* Defines this function to be a windows procedure for processing Messages */
    return (DefWindowProc(hwnd, message, wParam, lParam));
}

void initWindow(WNDCLASSEX *windowClass, HINSTANCE hInstance)
{
    windowClass->cbSize = sizeof(WNDCLASSEX);                         // size for this structure
    windowClass->style = CS_HREDRAW | CS_VREDRAW;                     // drawing style for this class
    windowClass->lpfnWndProc = WndProc;                               // windows procedure for processing messages
    windowClass->cbClsExtra = 0;                                      // extra bytes for allocating the window class
    windowClass->cbWndExtra = 0;                                      // extra bytes for allocating the window instance
    windowClass->hInstance = hInstance;                               // application instance
    windowClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);             // handle to the class icon
    windowClass->hCursor = LoadCursor(NULL, IDC_ARROW);               // handle to the cursor icon for mouse
    windowClass->hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // handle to the class background brush this paints the background
    windowClass->lpszMenuName = NULL;                                 // resource name of the class menu
    windowClass->lpszClassName = "ChessOnline";                       // class name for creating the window handle using CreateWindowEx()
    windowClass->hIconSm = LoadIcon(NULL, IDI_WINLOGO);               // handle to a small icon associated with the window class
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX windowClass; // window class
    HWND hwnd;              // window handle
    DWORD dwExStyle;        // window extended style
    DWORD dwStyle;          // window style
    RECT windowRect;        // window rectangle
    MSG msg;                // message
    bool done;              // flag saying when app is complete

    int width = 800;
    int height = 600;
    int bits = 32;

    windowRect.left = (long)0;
    windowRect.right = (long)width;
    windowRect.top = (long)0;
    windowRect.bottom = (long)height;

    /* Initialize The Window Class */
    initWindow(&windowClass, hInstance);

    /* Registers Window Class for creating Window Handle */
    if (!RegisterClassEx(&windowClass))
    {
        printf("Error:%d\n", GetLastError());
        return 0;
    }

    /* Creates the Window Handle */
    hwnd = CreateWindowEx(NULL,                                          // draw extended style for the window
                          "ChessOnline",                                 // Class Name for window class
                          "Chess Online",                                // Window Title
                          WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_SYSMENU, // draw style for the window
                          0,                                             // x
                          0,                                             // y
                          windowRect.right - windowRect.left,            // width
                          windowRect.bottom - windowRect.top,            // height
                          NULL,                                          // Parent Handle
                          NULL,                                          // Menu Handle
                          hInstance,                                     // Application Handle
                          NULL);                                         // Params
    if (!hwnd)
    {
        printf("Error:%d\n", GetLastError());
        return 0;
    }

    done = false;

    while (!done)
    {
        /* Gets messages from the Windows Message Queue */
        PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
        if (msg.message == WM_QUIT)
        {
            done = true;
        }
        else
        {
            /* Translates Messages from the Windows Message Queue */
            TranslateMessage(&msg);
            /* Dispatches those Messages for PeekMessage */
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}