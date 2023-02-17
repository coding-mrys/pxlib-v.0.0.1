#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <stdint.h>
#include "pxlib.h"

using namespace std;

typedef uint32_t u32;

//main window
int WINAPI main(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow) {

    //config
    WNDCLASS WindowClass = {};
    const wchar_t ClassName[] = L"mryspxlib v.0.0.1";
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = ClassName;
    WindowClass.hCursor = LoadCursor(0, IDC_CROSS);

    if (!RegisterClass(&WindowClass)) {
        return GetLastError();
    }

    HWND Window = CreateWindowEx(0, ClassName, L"pxlib001",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        0, 0, Instance, 0);


    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    ClientWidth = ClientRect.right - ClientRect.left;
    ClientHeight = ClientRect.bottom - ClientRect.top;

    BitmapWidth = ClientWidth;
    BitmapHeight = ClientHeight;

    int bpp = 4;

    BitmapMemory = VirtualAlloc(0,
        BitmapWidth * BitmapHeight * bpp,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );

    BITMAPINFO BitmapInfo;
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = BitmapWidth;
    BitmapInfo.bmiHeader.biHeight = -BitmapHeight;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;

    HDC DeviceContext = GetDC(Window);

    bool Running = true;

    //---

    //define plane as example_plane
    plane example_plane;

    //rotation angle
    float a = 0, b = 0, c = 0;
    float step = 0.5;

    //---


    while (Running) {
        MSG Message;
        while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
            if (Message.message == WM_QUIT) Running = false;
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        //---
        
        //set background color
        background(0x101010);   

        //init "raytracer" (in progress)
        cam.init(10, 10, 10, 1200, 600, 10);

        //build example plane and rotate
        example_plane.build(200,200,10,60,50,0xff00ff);

        a+=step, b+=step, c+=step;
        example_plane.rotate(a,b,c);

        //---

        StretchDIBits(DeviceContext,
            0, 0,
            BitmapWidth, BitmapHeight,
            0, 0,
            ClientWidth, ClientHeight,
            BitmapMemory, &BitmapInfo,
            DIB_RGB_COLORS, SRCCOPY);
    }

    return 0;
}
