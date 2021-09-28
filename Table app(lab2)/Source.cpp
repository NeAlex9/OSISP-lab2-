#include <Windows.h>
#include <commctrl.h>
#include <ios>
#include <string>
#include <vector>
#define UNICODE
using namespace std;

#define PADDING 20
#define REPAINT_TABLE 4
#define CHANGE_COL 5
#define CHANGE_ROW 6
#define MAX_COL 10
#define MAX_ROW 7

int cols = 4, rows = 4;

RECT rect;
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void CreateTable(HDC, int, int, int, int, int);
vector<string> stringMatrix = {
	"a", "dkkkkkkkkkkkkkyghjiuygyвывввывuвыаываыfghi7ygudasdasdasdsadd", "sdf", "ds",
	"a", "d", "s", "d",
	"", "", "", "",
	"adыыыыыыыыыыыs", "dsыффффффффффффффффффfsd", "sdf", "ds",
	"a", "d", "s", "d",
	"a", "dkkkkkkkkkkkkkyghjiuygyвывввывuвыаываыfghi7ygudasdasdasdsadd", "sdf", "ds",
	"a", "dkkkkkkkkkkkkkyghjiuygyвывввывuвыаываыfghi7ygudasdasdasdsadd", "sdf", "ds"
};

static HBRUSH hBrush = CreateSolidBrush(RGB(32, 23, 233));

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

	hWnd = CreateWindow(
		L"TableBuilderClass",
		L"Flexible Table",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX ^ WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 1000, 700,
		NULL,
		NULL,
		hInstance, NULL
	);

	HWND hWndEditRow = CreateWindow(
		L"Edit",
		L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
		70, 50, 120, 20,
		hWnd, /*(HMENU)CHANGE_ROW*/NULL, NULL, NULL);

	HWND hWndEditColumn = CreateWindow(
		L"Edit",
		L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
		230, 50, 120, 20,
		hWnd, (HMENU)CHANGE_COL, NULL, NULL);

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
	int xStart = 0;
	int yEnd = 0;
	int tableWidth = 0;
	int d;
	switch (msg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
		TextOut(hdc, 90, 30, L"Row", lstrlen(L"Row"));
		TextOut(hdc, 250, 30, L"Column", lstrlen(L"Column"));
		GetClientRect(hwnd, &rect);
		xStart = 30;
		yEnd = 30;
		tableWidth = rect.right - rect.left - xStart - yEnd;
		CreateTable(hdc, xStart, 100, tableWidth, cols, rows);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case REPAINT_TABLE:
			cols += 1;
			InvalidateRect(hwnd, &rect, NULL);
			break;
		case CHANGE_COL:
			switch (HIWORD(wp))
			{
			case EN_CHANGE:
			{
				wchar_t wc[255];
				LPWSTR buff;
				GetWindowText((HWND)lp, wc, 255);
				std::wstring ws(wc);
				std::string s = std::string(ws.begin(), ws.end());
				if (s != "")
					cols = std::stoi(s);
				else
					cols = 0;
				if (cols < MAX_COL)
				{
					InvalidateRect(hwnd, &rect, NULL);
				}
			}
			}
			break;

		case CHANGE_ROW:
			switch (HIWORD(wp))
			{
			case EN_CHANGE:
			{
				wchar_t wc[255];
				LPWSTR buff;
				GetWindowText((HWND)lp, wc, 255);
				std::wstring ws(wc);
				std::string s = std::string(ws.begin(), ws.end());
				if (s != "")
					rows = std::stoi(s);
				else
					rows = 0;
				if (rows < MAX_ROW)
				{
					InvalidateRect(hwnd, &rect, NULL);
				}
			}
			}
			break;
		}
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

void SetTextBlock(HDC hdc, string text, int xStart, int yStart, int height, int width)
{
	RECT rect;
	rect.top = yStart;
	rect.left = xStart;
	rect.right = xStart + width;
	rect.bottom = yStart + height;

	DrawText(hdc, s2ws(text).c_str(),
		text.length(),
		&rect,
		DT_WORDBREAK | DT_EDITCONTROL | DT_CENTER);
}

int GetRowHeight(HDC hdc, vector<string> row, int colWidth)
{
	string longestString = GetLongestString(row, row.size());
	RECT nonDrawableBlock;
	nonDrawableBlock.left = 0;
	nonDrawableBlock.top = 0;
	nonDrawableBlock.bottom = 1;
	nonDrawableBlock.right = colWidth;
	int height = DrawText(hdc, s2ws(longestString).c_str(), longestString.length(), &nonDrawableBlock,
		DT_CALCRECT | DT_WORDBREAK | DT_EDITCONTROL | DT_CENTER) + PADDING;

	return  height;
}

HFONT GetFont(int height, int width)
{
	HFONT hFont = CreateFont(height, width, 0, 0, 2, 0,
		false, FALSE, RUSSIAN_CHARSET, 20,
		20, 20, 20,
		TEXT("Times New Roman"));

	return hFont;
}

void CreateTable(HDC hdc, int xStart, int yStart, int tableWidth, int rowsCount, int colCount)
{
	SelectObject(hdc, GetFont(20, 6));
	int count = 0;
	for (int i = 0; i < rowsCount; i++)
	{
		int xPos = xStart;
		DrawLine(hdc, xPos, yStart, xPos + tableWidth, yStart);
		int height = GetRowHeight(hdc, stringMatrix[i], tableWidth / colCount - PADDING);
		for (int j = 0; j < colCount; j++)
		{
			SetTextBlock(hdc, stringMatrix[i][j], xPos + PADDING / 2, yStart + PADDING / 2, height - PADDING / 2, tableWidth / colCount - PADDING);
			DrawLine(hdc, xPos, yStart, xPos, yStart + height);
			xPos += tableWidth / colCount;
		}

		DrawLine(hdc, xPos, yStart, xPos, yStart + height);
		yStart += height;
	}

	DrawLine(hdc, xStart, yStart, xStart + tableWidth, yStart);
}