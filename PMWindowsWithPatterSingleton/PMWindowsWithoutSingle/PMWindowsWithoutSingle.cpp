// PMWindows.cpp

#include "framework.h"
#include "PMWindowsWithoutSingle.h" 
#include "PasswordManager.h" 
#include <sstream>
#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
PasswordManager* manager = nullptr;

#define IDC_WEBSITE 1001
#define IDC_USERNAME 1002
#define IDC_PASSWORD 1003
#define IDC_ADD_BUTTON 1004
#define IDC_GET_BUTTON 1005
#define IDC_DELETE_BUTTON 1006
#define IDC_SHOW_BUTTON 1007
#define IDC_SAVE_BUTTON 1008
#define IDC_LOAD_BUTTON 1009
#define IDC_OUTPUT 1010

std::wstring toWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    manager = PasswordManager::getInstance();

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PMWINDOWSWITHOUTSINGLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PMWINDOWSWITHOUTSINGLE));

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = { 0 }; 

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PMWINDOWSWITHOUTSINGLE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PMWINDOWSWITHOUTSINGLE);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; 

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, 0, 400, 400, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hWebsite, hUsername, hPassword, hOutput;

    switch (message)
    {
    case WM_CREATE:

        CreateWindowW(L"STATIC", L"Website:", WS_CHILD | WS_VISIBLE,
            20, 20, 70, 20, hWnd, NULL, hInst, NULL);
        hWebsite = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            100, 20, 250, 25, hWnd, (HMENU)IDC_WEBSITE, hInst, NULL);

        CreateWindowW(L"STATIC", L"Username:", WS_CHILD | WS_VISIBLE,
            20, 55, 70, 20, hWnd, NULL, hInst, NULL);
        hUsername = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
            100, 55, 250, 25, hWnd, (HMENU)IDC_USERNAME, hInst, NULL);

        CreateWindowW(L"STATIC", L"Password:", WS_CHILD | WS_VISIBLE,
            20, 90, 70, 20, hWnd, NULL, hInst, NULL);
        hPassword = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD,
            100, 90, 250, 25, hWnd, (HMENU)IDC_PASSWORD, hInst, NULL);

        // Кнопки
        CreateWindowW(L"BUTTON", L"Add Password", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 130, 110, 30, hWnd, (HMENU)IDC_ADD_BUTTON, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Get Password", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            140, 130, 110, 30, hWnd, (HMENU)IDC_GET_BUTTON, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Delete", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            260, 130, 110, 30, hWnd, (HMENU)IDC_DELETE_BUTTON, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Show All", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 170, 110, 30, hWnd, (HMENU)IDC_SHOW_BUTTON, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            140, 170, 110, 30, hWnd, (HMENU)IDC_SAVE_BUTTON, hInst, NULL);
        CreateWindowW(L"BUTTON", L"Load", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            260, 170, 110, 30, hWnd, (HMENU)IDC_LOAD_BUTTON, hInst, NULL);

        hOutput = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
            20, 210, 350, 150, hWnd, (HMENU)IDC_OUTPUT, hInst, NULL);
        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_ADD_BUTTON:
        {
            wchar_t website[256], username[256], password[256];
            GetWindowTextW(hWebsite, website, 256);
            GetWindowTextW(hUsername, username, 256);
            GetWindowTextW(hPassword, password, 256);

            char websiteA[256], usernameA[256], passwordA[256];
            WideCharToMultiByte(CP_ACP, 0, website, -1, websiteA, 256, NULL, NULL);
            WideCharToMultiByte(CP_ACP, 0, username, -1, usernameA, 256, NULL, NULL);
            WideCharToMultiByte(CP_ACP, 0, password, -1, passwordA, 256, NULL, NULL);

            manager->addPassword(websiteA, usernameA, passwordA);
            std::string info = "Password added for " + std::string(websiteA) + " (" + usernameA + ")";
            SetWindowTextW(hOutput, toWString(info).c_str());
        }
        break;

        case IDC_GET_BUTTON:
        {
            wchar_t website[256], username[256];
            GetWindowTextW(hWebsite, website, 256);
            GetWindowTextW(hUsername, username, 256);

            char websiteA[256], usernameA[256];
            WideCharToMultiByte(CP_ACP, 0, website, -1, websiteA, 256, NULL, NULL);
            WideCharToMultiByte(CP_ACP, 0, username, -1, usernameA, 256, NULL, NULL);

            std::string pwd = manager->getPassword(websiteA, usernameA);
            std::string info = "Password: " + pwd;
            if (pwd != "Password not found :(") {
                info += "\nStrength: " + std::to_string(manager->getPasswordStrength(websiteA, usernameA)) +
                    "/10 - " + manager->getPasswordStrengthDescription(websiteA, usernameA);
            }
            SetWindowTextW(hOutput, toWString(info).c_str());
        }
        break;

        case IDC_DELETE_BUTTON:
        {
            wchar_t website[256], username[256];
            GetWindowTextW(hWebsite, website, 256);
            GetWindowTextW(hUsername, username, 256);

            char websiteA[256], usernameA[256];
            WideCharToMultiByte(CP_ACP, 0, website, -1, websiteA, 256, NULL, NULL);
            WideCharToMultiByte(CP_ACP, 0, username, -1, usernameA, 256, NULL, NULL);

            manager->deletePassword(websiteA, usernameA);
            std::string info = "Password deleted for " + std::string(websiteA) + " (" + usernameA + ")";
            SetWindowTextW(hOutput, toWString(info).c_str());
        }
        break;

        case IDC_SHOW_BUTTON:
        {
            std::string allWebsites = manager->getAllWebsitesString();
            SetWindowTextW(hOutput, toWString(allWebsites).c_str());
        }
        break;

        case IDC_SAVE_BUTTON:
            if (manager->saveToFile()) {
                SetWindowTextW(hOutput, L"Saved to passwords.dat");
            }
            else {
                SetWindowTextW(hOutput, L"Save failed!");
            }
            break;

        case IDC_LOAD_BUTTON:
            if (manager->loadFromFile()) {
                SetWindowTextW(hOutput, L"Loaded from passwords.dat");
            }
            else {
                SetWindowTextW(hOutput, L"Load failed!");
            }
            break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        delete manager; 
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

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