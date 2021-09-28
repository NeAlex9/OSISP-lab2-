#include <Windows.h>
#include <commctrl.h>

char name[3][12] = { "Дима","Вова","Саша" };
char mail[3][22] = { "dima@mail.ru","vova@mail.ru","sasha@mail.ru" };
char passwd[3][12] = { "qwerty","uiop","asdff" };

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
#pragma region 
	const wchar_t CLASS_NAME[] = L"Sample Window Class";
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);
	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Learn to Program Windows",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX ^ WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		return 0;
	}
#pragma endregion CreatingMainWindow
	ShowWindow(hwnd, nCmdShow);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
LRESULT CALLBACK WindowProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
    static HWND hListView;
    LVCOLUMN lvc;//Столбцы
    LVITEM lvi;//Строки
    switch (msg) {
    case WM_CREATE:
    {
//        hListView = CreateWindow(WC_LISTVIEW, L"GOOD",
//            LVS_REPORT | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | LVS_AUTOARRANGE,
//            0, 0, 225, 180, hw,
//            (HMENU)1010, hInstance, NULL);
//
//        if (hListView == NULL)
//            MessageBox(hw, L"", L"", MB_OK);
//        // Вставляем столбцы
//                              ////////////////////////////////////////
//                                // Вставляем столбцы
//        //memset(&lvc, 0, sizeof(lvc));//закидать нулями  первые 0 байт
//
//        lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_FMT;//Стиль таблицы
//        //Как будет смотреться заголовок столбца , в моем случае 
//        //выравнивание по левому краю
//        lvc.fmt = LVCFMT_LEFT;
//        lvc.cx = 75;//Длина столбца относительно левого края 
//
//        lvc.iSubItem = 0;//Индекс столбца
//        lvc.pszText = L"Name";//Название столбца
//        ListView_InsertColumn(hListView, 0, &lvc);//Функция вставки столбцов
//
//        lvc.iSubItem = 1;
//        lvc.pszText = "Mail";
//        ListView_InsertColumn(hListView, 1, &lvc);
//
//        lvc.iSubItem = 2;
//        lvc.pszText = L"Password";
//        ListView_InsertColumn(hListView, 2, &lvc);
//        ////////////////////////////////////////
//// Вставляем строки
//        memset(&lvi, 0, sizeof(lvi));
//
//        lvi.mask = LVIF_TEXT | LVIF_TEXT;
//
//        for (int i = 0; i < 9; i++)
//        {
//            lvi.iItem = i;
//            lvi.iSubItem = 0;
//            ListView_InsertItem(hListView, &lvi);
//
//            lvi.iItem = i;
//            lvi.iSubItem = 1;
//            ListView_InsertItem(hListView, &lvi);
//
//            lvi.iItem = i;
//            lvi.iSubItem = 2;
//            ListView_InsertItem(hListView, &lvi);
//        }
//        ///////////////////////////////////////////////
//        //Вставить Данные способ ver_1
//        for (int i = 0; i < 3; i++)
//            ListView_SetItemText(hListView, i, 0, name[i]);//Вставить в строку i столбца 0 из массива name
//        for (int i = 0; i < 3; i++)
//            ListView_SetItemText(hListView, i, 1, mail[i]);//Вставить в строку i столбца 1 из массива mail
//        for (int i = 0; i < 3; i++)
//            ListView_SetItemText(hListView, i, 2, passwd[i]);//Вставить в строку i столбца 2 из массива passwd
//            ///////////////////////////////////////////////
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hw, msg, wp, lp);
}