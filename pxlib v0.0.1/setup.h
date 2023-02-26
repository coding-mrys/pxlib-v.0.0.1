#pragma once
#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <windows.h>
#include <stdint.h>
#include <cmath>
#include <string>

using namespace std;

//bitmap var - set pointer
typedef uint32_t u32;

void* BitmapMemory;

int BitmapWidth;
int BitmapHeight;

int ClientWidth;
int ClientHeight;

//base functions
void pixel(int x, int y, u32 color) {
    if (x > 0 && x < 1400 && y > 0 && y < 700) {
        u32* Pixel = (u32*)BitmapMemory;
        Pixel += y * BitmapWidth + x;
        *Pixel = color;
    }
}

void ClearScreen(u32 Color) {
    u32* Pixel = (u32*)BitmapMemory;
    for (int Index = 0;
        Index < BitmapWidth * BitmapHeight;
        ++Index) {
        *Pixel++ = Color;
    }
}

//key events
class keyEvent {
public:
    string value = " ";
    bool up = true;

    void pressed(string key_value) {
        value = key_value;
    }
    void update() {
        if (up) {
            value = " ";
        }
    }
};
keyEvent key;

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {


    switch (Message) {
    case WM_KEYDOWN: {
        bool up = false;

        switch (WParam) {

        case 'Q': {
            DestroyWindow(Window);
        };
        }} break;

    case WM_DESTROY: {
        PostQuitMessage(0); } break;

    case WM_KEYUP: {
        bool up = true;
    }

    default: { return DefWindowProc(Window, Message, WParam, LParam); }
    }

    return 0;

}

//mouse 
POINT cursorPosition;

void getMousePos() {
    GetCursorPos(&cursorPosition); // update mouse position
}

class mouse {
public:
    int x = cursorPosition.x;
    int y = cursorPosition.y;
};

//background
void background(u32 color) {
    ClearScreen(color); //create colored background
}