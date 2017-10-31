#pragma once
#include <string>

namespace MyPaint
{
	class Convert
	{
	private:
		static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	public:
		static bool HDCToBMP(std::wstring filePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24);
		static void BMPToHDC(HWND hwnd, HINSTANCE hInst, std::wstring &filePath);
		static bool HDCToPNG(std::wstring filePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24);
		static void PNGToHDC(HWND hwnd, HINSTANCE hInst, std::wstring &filePath);
	};
}