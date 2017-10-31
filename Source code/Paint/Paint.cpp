// Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Paint.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(ghWndMain, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	ghWndMain = hWnd;

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_KEYDOWN, OnKey);
		HANDLE_MSG(hWnd, WM_KEYUP, OnKey);
		HANDLE_MSG(hWnd, WM_MOVE, OnMove);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	// Load prototype
	MyPaint::CShapeCache::LoadCache();
	//
	// Status bar
	gStatusBar = new MyPaint::StatusBar;
	gStatusBar->Create(hwnd, IDC_STATUSBAR, hInst);
	//
	// Mặc định là vẽ đường thẳng
	HMENU hMenu = GetMenu(hwnd);
	CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_CHECKED);
	EnableMenuItem(hMenu, ID_EDIT_UNDO, MF_DISABLED);
	EnableMenuItem(hMenu, ID_EDIT_REDO, MF_DISABLED);
	gShapeType = 0;
	//
	//
	gStatusBar->Resize();
	SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Line");
	//
	SetWindowText(hwnd, L"Untitled - Paint");
	//
	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HMENU hMenu = GetMenu(hwnd);
	switch (id)
	{
	case ID_FILE_SAVE:
		SaveFileDialog(hwnd);
		break;
	case ID_FILE_OPEN:
	{
		int size1 = gShapesUndoRedo.size();
		int size2 = gShapes.size();

		if (size1 != 0 || size2 != 0)
		{
			int result = MessageBox(hwnd, L"Do you want to save changes?", L"Paint", MB_YESNOCANCEL);
			switch (result)
			{
			case IDNO:
				OpenFileDialog(hwnd);
				break;
			case IDYES:
				SaveFileDialog(hwnd);
				break;
			case IDCANCEL:
				return;
			}
		}
	}
		break;
	case ID_FILE_NEW:
	{
		int size1 = gShapesUndoRedo.size();
		int size2 = gShapes.size();

		if (size1 != 0 || size2 != 0)
		{
			int result = MessageBox(hwnd, L"Do you want to save changes?", L"Paint", MB_YESNOCANCEL);
			switch (result)
			{
			case IDNO:
				break;
			case IDYES:
				SaveFileDialog(hwnd);
				break;
			case IDCANCEL:
				return;
			}
		}

		gFileType = 1;
		for (int i = size2 - 1; i >= 0; i--)
		{
			delete gShapes[i];
			gShapes.pop_back();
		}

		for (int i = size1 - 1; i >= 0; i--)
		{
			delete gShapesUndoRedo[i];
			gShapesUndoRedo.pop_back();
		}

		EnableMenuItem(hMenu, ID_EDIT_UNDO, MF_DISABLED);
		EnableMenuItem(hMenu, ID_EDIT_REDO, MF_DISABLED);
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;
	case ID_SHAPE_LINE:
		SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Line");
		goto Check;
	case ID_SHAPE_RECTANGLE:
		SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Rectangle");
		goto Check;
	case ID_SHAPE_ELLIPSE:
		SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Ellipse");
		goto Check;
	Check:
		gShapeType = id - ID_SHAPE_LINE;
		for (int i = ID_SHAPE_LINE; i <= ID_SHAPE_ELLIPSE; i++)
		{
			CheckMenuItem(hMenu, i, !(id - i) ? MF_CHECKED : MF_UNCHECKED);
		}
		break;
	case ID_EDIT_UNDO:
	{
		int size = gShapes.size() - 1;
		gShapesUndoRedo.push_back(gShapes[size]);
		gShapes.pop_back();

		if (size == 0) EnableMenuItem(hMenu, ID_EDIT_UNDO, MF_DISABLED);

		EnableMenuItem(hMenu, ID_EDIT_REDO, MF_ENABLED);
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;
	case ID_EDIT_REDO:
	{
		int size = gShapesUndoRedo.size() - 1;
		gShapes.push_back(gShapesUndoRedo[size]);
		gShapesUndoRedo.pop_back();

		if (size == 0) EnableMenuItem(hMenu, ID_EDIT_REDO, MF_DISABLED);

		EnableMenuItem(hMenu, ID_EDIT_UNDO, MF_ENABLED);
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
		break;

	case IDM_EXIT:
		DestroyWindow(hwnd);
		break;
	}
}

void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	gStatusBar->Resize();
	RECT statusBar;
	GetWindowRect(GetDlgItem(hwnd, IDC_STATUSBAR), &statusBar);

	WCHAR text[30];
	gArea.x = cx - 1;
	gArea.y = cy - (statusBar.bottom - statusBar.top) - 1;
	wsprintf(text, L"%d, %dpx", gArea.x, gArea.y); // Trừ 1 do pixel bắt đầu từ 0
	SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 1, (LPARAM)text);
}

void OnMove(HWND hwnd, int x, int y)
{
	InvalidateRect(hwnd, NULL, TRUE);
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hwnd, &ps);

	switch (gFileType)
	{
	case 2:
		MyPaint::Convert::BMPToHDC(hwnd, hInst, gFileLoadedPath);
		break;
	case 3:
		MyPaint::Convert::PNGToHDC(hwnd, hInst, gFileLoadedPath);
		break;
	}

	for (int i = 0; i < gShapes.size(); i++)
	{
		gShapes[i]->ReDraw(hwnd);
	}

	EndPaint(hwnd, &ps);
}

void OnClose(HWND hwnd)
{
	int size1 = gShapesUndoRedo.size();
	int size2 = gShapes.size();

	if (size1 != 0 || size2 != 0)
	{
		int result = MessageBox(hwnd, L"Do you want to save changes?", L"Paint", MB_YESNOCANCEL);
		switch (result)
		{
		case IDNO:
			DestroyWindow(hwnd);
			break;
		case IDYES:
			SaveFileDialog(hwnd);
			break;
		case IDCANCEL:
			return;
		}
	}

	for (int i = size1 - 1; i >= 0; i--)
	{
		delete gShapesUndoRedo[i];
		gShapesUndoRedo.pop_back();
	}

	for (int i = size2 - 1; i >= 0; i--)
	{
		delete gShapes[i];
		gShapes.pop_back();
	}

	delete gStatusBar;
	MyPaint::CShapeCache::ClearCache();
	DestroyWindow(hwnd);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	gDrawing = TRUE;

	gLeftTop.x = gRightBottom.x = x;
	gLeftTop.y = gRightBottom.y = y;
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (gDrawing)
	{
		if (keyFlags == MK_SHIFT + 1)
		{
			if (gShapeType == 0) // Line
			{

			}
			else
			{
				if (abs(gLeftTop.x - x) > abs(gLeftTop.y - y))
				{
					if (x - gLeftTop.x > 0)	x = gLeftTop.x + abs(y - gLeftTop.y);
					else x = gLeftTop.x - abs(y - gLeftTop.y);
				}
				else
				{
					if (y - gLeftTop.y > 0) y = gLeftTop.y + abs(x - gLeftTop.x);
					else y = gLeftTop.y - abs(x - gLeftTop.x);
				}
			}
		}

		MyPaint::IShape *preview = MyPaint::CShapeCache::GetShape(gShapeType);
		preview->Draw(hwnd, gLeftTop, gRightBottom);

		gRightBottom.x = x;
		gRightBottom.y = y;

		preview->Draw(hwnd, gLeftTop, gRightBottom);
	}

	WCHAR text[30];
	wsprintf(text, L"%d, %dpx", x, y);
	SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 0, (LPARAM)text);
}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (gDrawing)
	{
		MyPaint::IShape *obj = gShapeFact.GetShape(gShapeType);
		obj->Draw(hwnd, gLeftTop, gRightBottom, FALSE);
		gShapes.push_back(obj);

		EnableMenuItem(GetMenu(hwnd), ID_EDIT_UNDO, MF_ENABLED);

		gDrawing = FALSE;
		InvalidateRect(hwnd, NULL, TRUE);
	}
}

void OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags)
{
	if (vk == VK_SHIFT)
	{
		if (fDown)
		{
			switch (gShapeType)
			{
			case 0:
				SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Straight line");
				break;
			case 1:
				SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Square");
				break;
			case 2:
				SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Circle");
				break;
			}
		}
		else
		{
			switch (gShapeType)
			{
			case 0:
				SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Line");
				break;
			case 1:
				SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Rectangle");
				break;
			case 2:
				SendMessage(GetDlgItem(hwnd, IDC_STATUSBAR), SB_SETTEXT, 2, (LPARAM)L"Ellipse");
				break;
			}
		}
	}
}

void SaveFileDialog(HWND hwnd)
{
	OPENFILENAME ofn;
	WCHAR szFile[10260] = L"";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.nMaxFile = 10260;
	ofn.lpstrFile = szFile;

	ofn.lpstrFilter = L"Objects file (*.objpaint)\0*.objpaint\0Bitmap (*.bmp)\0*.bmp\0PNG (*.png)\0*.png\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		using namespace std;
		wstring buffer = ofn.lpstrFile;

		switch (ofn.nFilterIndex)
		{
		case 1:
		{
			if (ofn.nFileExtension == 0) buffer += L".objpaint";

			ofstream out;
			out.open(buffer, ios::binary);
			int size = gShapes.size();
			out.write((const char*)&size, sizeof(size));

			for (int i = 0; i < size; i++)
			{
				gShapes[i]->WriteBinary(out);
			}
		}
		break;
		case 2:
		{
			if (ofn.nFileExtension == 0) buffer += L".bmp";

			HDC dc = GetDC(hwnd);
			MyPaint::Convert::HDCToBMP(buffer, dc, { 0, 0, gArea.x, gArea.y });
			ReleaseDC(hwnd, dc);
		}
		break;
		case 3:
		{
			if (ofn.nFileExtension == 0)buffer += L".png";

			HDC dc = GetDC(hwnd);
			MyPaint::Convert::HDCToPNG(buffer, dc, { 0, 0, gArea.x, gArea.y });
			ReleaseDC(hwnd, dc);
		}
		break;
		}

		buffer += L" - Paint";
		SetWindowText(hwnd, const_cast<LPWSTR>(buffer.substr(ofn.nFileOffset).c_str()));
	}
}

void OpenFileDialog(HWND hwnd)
{
	OPENFILENAME ofn;
	WCHAR szFile[10260] = L"";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.nMaxFile = 10260;
	ofn.lpstrFile = szFile;

	ofn.lpstrFilter = L"Objects file (*.objpaint)\0*.objpaint\0Bitmap (*.bmp)\0*.bmp\0PNG (*.png)\0*.png\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		using namespace std;
		wstring buffer = ofn.lpstrFile;

		gFileType = ofn.nFilterIndex;

		// Clear content
		for (int i = gShapes.size() - 1; i >= 0; i--)
		{
			delete gShapes[i];
			gShapes.pop_back();
		}

		for (int i = gShapesUndoRedo.size() - 1; i >= 0; i--)
		{
			delete gShapesUndoRedo[i];
			gShapesUndoRedo.pop_back();
		}
		//
		switch (ofn.nFilterIndex)
		{
		case 1:
		{
			ifstream in;
			in.open(buffer, ios::binary);
			int size;
			in.read((char*)&size, sizeof(int));

			for (int i = 0; i < size; i++)
			{
				int id;
				in.read((char*)&id, sizeof(int));
				MyPaint::IShape* res = gShapeFact.GetShape(id);
				res->ReadBinary(in);
				gShapes.push_back(res);
			}

			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
		case 2:
			MyPaint::Convert::BMPToHDC(hwnd, hInst, buffer);
			break;
		case 3:
			MyPaint::Convert::PNGToHDC(hwnd, hInst, buffer);
			break;
		}
		gFileLoadedPath = buffer;

		buffer += L" - Paint";
		SetWindowText(hwnd, const_cast<LPWSTR>(buffer.substr(ofn.nFileOffset).c_str()));
	}
}