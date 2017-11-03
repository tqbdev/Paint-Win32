#pragma once
#include <string>
#include <gdiplus.h>

extern Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
extern ULONG_PTR					gdiplusToken;
extern Gdiplus::Image				*imagePNG;

namespace MyPaint
{
	class Convert
	{
	private:
		static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	public:
		static bool HDCToBMP(std::wstring filePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24);
		static void BMPToHDC(HWND hwnd, HINSTANCE hInst, std::wstring &filePath, HDC hdc = NULL);
		static void BMPToHDC(HBITMAP file, HDC hdc);
		static bool HDCToPNG(std::wstring filePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24);
		static void PNGToHDC(HWND hwnd, HINSTANCE hInst, std::wstring &filePath, HDC hdc = NULL);
		static void PNGToHDC(HDC hdc);
		static void LoadPNG(std::wstring &filePath);

		static void GDIPlusInit();
		static void GDIPlusDestroy();
	};
}