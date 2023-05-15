// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
#include "framework.h"
#include "Client.h"

#define MAX_LOADSTRING 100
// 전역 변수: 함수 외부에 선언되어 있는 변수들
HINSTANCE hInst;                                // 현재 인스턴스입니다.
// main함수가 시작할 때 받아온 변수 hInstance 를
// InitInstance() 함수에서 인자값으로 받아와 hInst에 대입해준다.

// [WCHAR 타입]
// 2Byte 문자열 자료형(wchar_t)
// wchar_t 자료형을 재정의 해둔것
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
// wchar_t 100개짜리 문자배열
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
// 전방선언
// 정의부는 main함수 아래부분에 되어있다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// main함수
// 일반적인 main함수와는 달리 여러가지 인자를 받아온다.
// 우리는 Windows에서 실행되는 Windows 전용 프로그램을 만드는 것이다.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         // 실행 된 프로세스의 메모리상 시작 주소
                     _In_opt_ HINSTANCE hPrevInstance,  // Prev : 이전
                     _In_ LPWSTR    lpCmdLine,          // 
                     _In_ int       nCmdShow)           // 
// [_In_, _In_opt]
// 'SAL(소스코드주석언어)'라고 한다. ('msdn'사이트를 참고하자)
// source-code annotation language 
// 변수의 용도,의미를 적어준것 떄문에 코드로서 의미가 없다.
// 매번 모든 변수에 주석을 달아주기 힘들다
// 어느정도 함축된 의미로 키워드를 달아줌으로써 주석을대체한다.
// _In_ : 데이터가 이 함수에 입력됨을 의미한다.
// _In_opt_ : '부가적인 데이터', '잉여 데이터' 임을 나타낸다.
/*  
    'hPrevInstance'의 존재 이유 : 
    아마도 Windows가 오래된 프로그램이다보니 
    main함수의 구조를 바꿀 수 없지 않았을까? 라는 의견...
*/
{
    // [UNREFERENCED_PARAMETER]
    // 별다른 의미가 없음을 의미한다.
    // 컴파일러도 바보가 아니기에 아래 두줄은 무시해버린다.
    // 최종적으로 컴파일된 코드를 보면 아래 두줄은 존재하지 않게된다.
    // 왜 존재하는가? : hPrevInstance 와 lpCmdLine가 참조되지 않는 변수임을 알려줄 뿐
    // 주석으로 적었어도 됐을 코드이다. 그냥 무시해도 된다.
    UNREFERENCED_PARAMETER(hPrevInstance);  // UNREFERENCED_PARAMETER(hPrevInstance) == hPrevInstance
    UNREFERENCED_PARAMETER(lpCmdLine);      // UNREFERENCED_PARAMETER(lpCmdLine) == lpCmdLine

    // TODO: 여기에 코드를 입력합니다.
    
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
