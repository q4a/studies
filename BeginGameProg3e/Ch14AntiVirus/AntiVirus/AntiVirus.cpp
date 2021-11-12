// AntiVirus.cpp
//

#include "StdAfx.h"
#include "GameUtil.h"

// 资源目录
const LPCTSTR RES_DIR = _T("data");

// 初始化运行环境
void Init() {
    _tsetlocale(LC_ALL, _T(""));
    GU::g_ResDir = RES_DIR;
    if (IsDebuggerPresent())
        GU::g_ResDir = _T("..\\") + GU::g_ResDir;
}

// 清理运行环境
void Clean() {
    _CrtDumpMemoryLeaks();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch(msg) {
    case WM_DESTROY:
        GU::g_GameOver = TRUE;
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR cmdline, int cmdShow) {
    Init();

    // initialize window settings
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC) WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInst;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = GU::APPTITLE;
    wc.hIconSm       = NULL;
    RegisterClassEx(&wc);

    // create a new window
    HWND hwnd = CreateWindow(GU::APPTITLE, GU::APPTITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, GU::SCREENW, GU::SCREENH, NULL, NULL, hInst, NULL);
    if (hwnd == NULL)
        return -1;

    // display the window
    ShowWindow(hwnd, cmdShow);
    UpdateWindow(hwnd);

    // initialize the game
    if (!GU::Game_Init(hwnd)) {
        MessageBox(hwnd, _T("Game initialization failed, check resource existence."), _T("Initialization failed"), MB_ICONERROR | MB_OK);
        return -1;
    }

    // main message loop
    MSG msg;
    while (!GU::g_GameOver) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // process game loop
        GU::Game_Run(hwnd);
    }

    // shutdown
    GU::Game_End();
    Clean();
    return (int) msg.wParam;
}
