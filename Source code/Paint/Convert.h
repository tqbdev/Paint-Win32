#pragma once
#include <string>
#include <gdiplus.h>

namespace MyPaint
{
	class ImageConvert
	{
	private:
		static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
		static Gdiplus::Image *image;
	public:
		static bool HDCToBMP(std::wstring filePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24);
		static bool HDCToPNG(std::wstring filePath, HDC Context, RECT Area, uint16_t BitsPerPixel = 24);
		static void ImgToHDC(/*HDC hdc*/ Gdiplus::Graphics *gp);
		static void LoadImg(std::wstring &filePath);
		static void ClearImg();
	};
}