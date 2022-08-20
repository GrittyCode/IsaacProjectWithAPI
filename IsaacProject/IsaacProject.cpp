// IsaacProject.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include "stdafx.h"
#ifdef DEBUG
#include <vld.h>
#endif // DEBUG


#include "IsaacProject.h"

#define MAX_LOADSTRING 100


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


//EXTERN 변수
HWND g_hWnd;
HWND g_ToolDig;
HINSTANCE g_hInst;
float Scale = 1;
wchar_t OriginDirectory[256];
//

//GDI 설정
ULONG_PTR gdiplusToken;
GdiplusStartupInput gdiplusStartupInput;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ISAACPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    /*
    rt_Client.right / ;
    rt_Client.bottom;
    */
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ISAACPROJECT));

    MSG msg;
    msg.message = WM_NULL;
    
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    CGameMgr::GetInstance();
    CFrameMgr frame;
    frame.InitFrameMgr(65.0f);
    frame.InitFrameMgr(60.0f);
    // 기본 메시지 루프입니다:
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (frame.LimitFrame())
            {
                CGameMgr::GetInstance()->Update();
                CGameMgr::GetInstance()->FixedUpdate();
                CGameMgr::GetInstance()->Render();
            }
            frame.RenderFrame();
            //cout << CTimeMgr::GetInstance()->GetDeltaTime() << endl;
        }
    }

    CTimeMgr::DestroyInst();
    CGameMgr::GetInstance()->Release();
    CGameMgr::DestroyInst();

    //GDI 동적할당 해제
    GdiplusShutdown(gdiplusToken);
    return (int)msg.wParam;
}


//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ISAACPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;//MAKEINTRESOURCEW(IDC_ISAACPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


   g_hInst = hInst;
   g_hWnd = hWnd;

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        static POINT pt_mouse;

    case WM_CREATE:
        MoveWindow(hWnd, PADDING_X, PADDING_Y, WINDOW_X, WINDOW_Y, TRUE);
        return (INT_PTR)FALSE;
    case WM_GETMINMAXINFO:
    {
        RECT rt = {0,0,WINDOW_X ,WINDOW_Y };
        AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = rt.right - rt.left;
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = rt.bottom - rt.top;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = rt.right - rt.left;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = rt.bottom - rt.top;
        return (INT_PTR)FALSE;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_TOOL), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
        //타일 정보가 있다면 타일 정보를 찍고, 
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
