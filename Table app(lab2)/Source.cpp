#include <Windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#define UNICODE
#define DELTA 3
using namespace std;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void CreateTable(HDC, int, int, int);
vector<vector<string>> stringMatrix = {
	{"ads", "dsfsd", "sdf", "ds"},
	{"ads", "dsfsd", "sdf", "ds"},
	{"ads", "dsfsd", "sdf", "ds"},
	{"ads", "dsfsd", "sdf", "ds"}
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG msg;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"TableBuilderClass";
	wcex.hIconSm = wcex.hIcon;
	RegisterClassEx(&wcex);

	hWnd = CreateWindow(L"TableBuilderClass", L"Flexible Table",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL, CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		RECT rec;
		GetWindowRect(hwnd, &rec);
		CreateTable(hdc, rec.right - rec.left, 4, 4);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

string GetLongestString(vector<string> row, size_t count)
{
	string longestString = row[0];
	for (size_t j = 0; j < count; j++)
	{
		if (row[j].length() > longestString.length())
			longestString = row[j];
	}

	return longestString;
}

int GetRowHeight(HDC hdc, vector<string> row, int rowsWidth)
{
	string longestString = GetLongestString(row, row.size());
	RECT nonDrawableBlock;
	nonDrawableBlock.left = 0;
	nonDrawableBlock.top = 0;
	nonDrawableBlock.bottom = 1;
	nonDrawableBlock.right = rowsWidth;
	int height = DrawText(hdc, s2ws(longestString).c_str(), longestString.length(), &nonDrawableBlock,
		DT_CALCRECT | DT_WORDBREAK | DT_EDITCONTROL | DT_CENTER) + DELTA;

	return  height;
}

void CreateTable(HDC hdc, int tableWidth, int rowsCount, int colCount)
{
	int yStart = 0;
	yStart += 10;
	for (int i = 0; i < rowsCount; i++)
	{
		int xStart = 0;
		int yEnd = 0;
		int xEnd = 0;
		DrawLine(hdc, xStart, yStart, tableWidth, yStart);
		int height = GetRowHeight(hdc, stringMatrix[i], tableWidth);
		for (int j = 0; j < colCount; j++)
		{
			///code
		}

		yStart += 60;
	}
	DrawLine(hdc, 0, yStart, tableWidth, yStart);
}