// Omok.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Omok.h"
#define X_COUNT 19
#define Y_COUNT 19

//화면과 바둑판의 거리
#define START_X 50
#define START_Y 50

//줄 사이의 간격 - 바둑돌의 지름
#define INTERVAL 26

#define HALF_INTERVAL INTERVAL/2

#define XPOS(x)	(START_X +(x)* INTERVAL)	
#define YPOS(Y)	(START_Y +(Y)* INTERVAL)	

unsigned char g_dol[Y_COUNT][X_COUNT];

unsigned char g_step;




void OnPaint(HWND ah_wnd)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(ah_wnd, &ps);

	for (int x = 0; x < X_COUNT; x++) {
		MoveToEx(h_dc, XPOS(x), YPOS(0), NULL);
		LineTo(h_dc, XPOS(x), YPOS(Y_COUNT - 1));
	}

	for (int y = 0; y < Y_COUNT; y++) {
		MoveToEx(h_dc, XPOS(0), YPOS(y), NULL);
		LineTo(h_dc, XPOS(X_COUNT - 1), YPOS(y));
	}

	for (int y = 0; y < Y_COUNT; y++) {
		for (int x = 0; x < X_COUNT; x++) {
			if (g_dol[y][x] > 0) {
				if (g_dol[y][x] == 1) SelectObject(h_dc, GetStockObject(BLACK_BRUSH));
				else SelectObject(h_dc, GetStockObject(WHITE_BRUSH));

				Ellipse(h_dc, XPOS(x) - HALF_INTERVAL, YPOS(y) - HALF_INTERVAL,
					XPOS(x) + HALF_INTERVAL, YPOS(y) + HALF_INTERVAL
				);
			}
		}
	}



	EndPaint(ah_wnd, &ps);
}
//왼쪽 마우스 클릭했을 경우 사용할 코드
void OnLButtonDown(HWND ah_wnd, int a_x, int a_y) {
	//바둑판 영역에만 돌을 놓을 수 있도록 클릭한 위치가 바둑판 영역인지 체크 
	if (a_x > (XPOS(0) - HALF_INTERVAL) && a_y > (YPOS(0) - HALF_INTERVAL)
		&& a_x < (XPOS(X_COUNT - 1) + HALF_INTERVAL) && a_y < (YPOS(Y_COUNT - 1) + HALF_INTERVAL)) {


	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT) {
		OnPaint(hWnd);
		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN) {
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		OnLButtonDown(hWnd, x, y);
	}
	else if (uMsg == WM_DESTROY) PostQuitMessage(0);
	

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"tipssoft";

	HBRUSH h_bk_brush = CreateSolidBrush(RGB(244, 176, 77));

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = h_bk_brush;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"www.sj.com",
		WS_OVERLAPPEDWINDOW, 100, 90, 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DeleteObject(h_bk_brush);

	return msg.wParam;
}