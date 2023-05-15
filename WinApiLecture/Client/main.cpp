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
                     _In_opt_ HINSTANCE hPrevInstance,  // 해당 시스템의 이전 주소, 
                                                        // 가상메모리 사용 이전에는 사용되었으나 현 시스템에선 사용안함 때문에 opt(optional)이 붙게됨
                     _In_ LPWSTR    lpCmdLine,          // 프로그램 실행시 실행파일이 아닌 명령 프롬프트로 실행시킬때 추가적인 인자로 문자열을 넣어주면 해당 아규먼트를 통해서 받아올 수 있다.
                    /*
                        [LPWSTR]
                        - wchar_t 의 포인터 타입 (whcar_t*)
                        - 2Byte 문자열의 주소값
                    */
                     _In_ int       nCmdShow)           // 
 /*
     [_In_, _In_opt]
     'SAL(소스코드주석언어)'라고 한다. ('msdn'사이트를 참고하자)
     source-code annotation language 
     변수의 용도,의미를 적어준것 떄문에 코드로서 의미가 없다.
     매번 모든 변수에 주석을 달아주기 힘들다
     어느정도 함축된 의미로 키워드를 달아줌으로써 주석을대체한다.
     _In_ : 데이터가 이 함수에 입력됨을 의미한다.
     _In_opt_ : '부가적인 데이터', '잉여 데이터' 임을 나타낸다.
 */
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
    LoadStringW(hInstance, IDS_APP_TITLE/*103*/, szTitle, MAX_LOADSTRING);  // szTitle에 String Table에서 가져온 프로젝트명을 넣어준다.
                                                                            // 해당 값은 실행시 나오는 창의 타이틀로 사용된다.
                                                                            // CreateWindowW()함수에서 직접 타이틀을 입력해줘도 되기에 안해줘도 되는 작업이다.
    LoadStringW(hInstance, IDC_CLIENT/*109*/, szWindowClass, MAX_LOADSTRING);   // 키 값으로 사용한다.
    /* 
        [LoadStringW()]
        - Windows에서 제공해주는 함수
        - 프로젝트 리소스 테이블인 String Table에서 103, 109에 해당하는 문자열을 가져와서 배열에 넣어주는 함수
    */
    MyRegisterClass(hInstance); // 아래 정의부가 있다.
                                // 윈도우(창)의 정보를 등록한다. (윈도우가 어떤 정보를 띄울것인지 정보를 setting 한다.

    // 애플리케이션 초기화를 수행합니다.
    // 윈도우(창)를 생성한다.
    // MyRegisterClass() 함수에서 setting된 정보를 바탕으로 창을 생성한다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // 해당 윈도우가 종료된다고 판단된다면 while 반복문이 종료되면서 main함수가 종료되는 구조
        // 즉, 윈도우(창)가 종료되면 프로그램도 종료되는 구조다.
        // 이 때문에 윈도우와 프로세스가 운명을 같이한다는 느낌을 받을 수 있으나.
        // 실제론 그러하지 않다. 윈도우는 인터페이스중 하나일 뿐이고
        // 창을 가지지 않는 프로세스들도 존재하기에 "프로세스가 곧 윈도우다."라고 생각하면 안된다.(프로세스 != 윈도우)
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
ATOM MyRegisterClass(HINSTANCE hInstance)   // WNDCLASSEXW 구조체의 멤버들에 값을 채우고 있다.
{
    WNDCLASSEXW wcex;
    /*
        [WNDCLASSEXW]
        - 구조체
    */

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr; // MAKEINTRESOURCEW(IDC_CLIENT); // '메뉴 바'
    wcex.lpszClassName = szWindowClass;//L"Key";    // 키 값 등록
                                                    // 창의 타이틀명과 동일하게 굳이 String Table에서 값을 받아와주는 작업을 해줄 필요없이
                                                    // 직접 키 값을 등록해줘도 된다.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // RegisterClassExW() 함수는 Windows에서 제공하는 함수
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

   HWND hWnd = CreateWindowW(szWindowClass/*L"Key"*/, szTitle/*Client*/, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    /*
        [CreateWindowW()]
        - 해당 함수를 통해 창이 생성된다.
        - szTitle에 들어있는 문자열로 창의 타이틀명이 결정된다.
        - 굳이 String Table에서 값을 받아와 szTitle에 문자열 값을 넣어줄 필요없이 szTitle 위치에 직접 문자열 값을 넣어줘도 된다.
        - 처음 프로젝트를 생성했을 때 어떤 이름을 지정해줄지 알지못하기에 기본값으로 프로젝트명을 가져와 지정해준것 뿐
    */

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
