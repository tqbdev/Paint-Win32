#include "stdafx.h"
#include "Convert.h"
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")

Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
ULONG_PTR						gdiplusToken;
Gdiplus::Image					*imagePNG;

namespace MyPaint
{
	bool Convert::HDCToBMP(std::wstring filePath, HDC Context, RECT Area, uint16_t BitsPerPixel)
	{
		uint32_t Width = Area.right - Area.left;
		uint32_t Height = Area.bottom - Area.top;
		BITMAPINFO Info;
		BITMAPFILEHEADER Header;
		memset(&Info, 0, sizeof(Info));
		memset(&Header, 0, sizeof(Header));
		Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		Info.bmiHeader.biWidth = Width;
		Info.bmiHeader.biHeight = Height;
		Info.bmiHeader.biPlanes = 1;
		Info.bmiHeader.biBitCount = BitsPerPixel;
		Info.bmiHeader.biCompression = BI_RGB;
		Info.bmiHeader.biSizeImage = Width * Height * (BitsPerPixel > 24 ? 4 : 3);
		Header.bfType = 0x4D42;
		Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		char* Pixels = NULL;
		HDC MemDC = CreateCompatibleDC(Context);
		HBITMAP Section = CreateDIBSection(Context, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
		DeleteObject(SelectObject(MemDC, Section));
		BitBlt(MemDC, 0, 0, Width, Height, Context, Area.left, Area.top, SRCCOPY);
		DeleteDC(MemDC);
		std::fstream hFile(filePath, std::ios::out | std::ios::binary);
		if (hFile.is_open())
		{
			hFile.write((char*)&Header, sizeof(Header));
			hFile.write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
			hFile.write(Pixels, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
			hFile.close();
			DeleteObject(Section);
			return true;
		}
		DeleteObject(Section);
		return false;
	}

	void Convert::BMPToHDC(HBITMAP file, HDC hdc)
	{
		static BITMAP bm;

		HDC hdcMem = CreateCompatibleDC(hdc);
		HANDLE hbmOld = SelectObject(hdcMem, file);

		GetObject(file, sizeof(bm), &bm);

		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
	}

	void Convert::BMPToHDC(HWND hwnd, HINSTANCE hInst, std::wstring &filePath, HDC hdc)
	{
		static BITMAP bm;
		static HBITMAP file = (HBITMAP)LoadImage(hInst, const_cast<LPWSTR>(filePath.c_str()), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		BOOL fCheck = FALSE;
		if (hdc == NULL)
		{
			hdc = GetDC(hwnd);
			fCheck = TRUE;
		}

		HDC hdcMem = CreateCompatibleDC(hdc);
		HANDLE hbmOld = SelectObject(hdcMem, file);

		GetObject(file, sizeof(bm), &bm);

		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
		DeleteObject(file);

		if (fCheck) ReleaseDC(hwnd, hdc);
	}

	int Convert::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
	{
		UINT  num = 0;          // number of image encoders
		UINT  size = 0;         // size of the image encoder array in bytes

		Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

		Gdiplus::GetImageEncodersSize(&num, &size);
		if (size == 0)
			return -1;  // Failure

		pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
		if (pImageCodecInfo == NULL)
			return -1;  // Failure

		GetImageEncoders(num, size, pImageCodecInfo);

		for (UINT j = 0; j < num; ++j)
		{
			if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
			{
				*pClsid = pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
				return j;  // Success
			}
		}

		free(pImageCodecInfo);
		return -1;  // Failure
	}


	bool Convert::HDCToPNG(std::wstring filePath, HDC Context, RECT Area, uint16_t BitsPerPixel)
	{
		uint32_t Width = Area.right - Area.left;
		uint32_t Height = Area.bottom - Area.top;
		BITMAPINFO Info;
		BITMAPFILEHEADER Header;
		memset(&Info, 0, sizeof(Info));
		memset(&Header, 0, sizeof(Header));
		Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		Info.bmiHeader.biWidth = Width;
		Info.bmiHeader.biHeight = Height;
		Info.bmiHeader.biPlanes = 1;
		Info.bmiHeader.biBitCount = BitsPerPixel;
		Info.bmiHeader.biCompression = BI_RGB;
		Info.bmiHeader.biSizeImage = Width * Height * (BitsPerPixel > 24 ? 4 : 3);
		Header.bfType = 0x4D42;
		Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		char* Pixels = NULL;
		HDC MemDC = CreateCompatibleDC(Context);
		HBITMAP Section = CreateDIBSection(Context, &Info, DIB_RGB_COLORS, (void**)&Pixels, 0, 0);
		DeleteObject(SelectObject(MemDC, Section));
		BitBlt(MemDC, 0, 0, Width, Height, Context, Area.left, Area.top, SRCCOPY);
		DeleteDC(MemDC);

		Gdiplus::Bitmap bmp(Section, (HPALETTE)0);
		CLSID pngClsid;
		GetEncoderClsid(L"image/png", &pngClsid);
		bmp.Save(const_cast<LPWSTR>(filePath.c_str()), &pngClsid, NULL);

		DeleteObject(Section);
		return true;
	}

	void Convert::PNGToHDC(HWND hwnd, HINSTANCE hInst, std::wstring &filePath, HDC hdc)
	{
		if (hdc == NULL) hdc = GetDC(hwnd);

		if (imagePNG != NULL) delete imagePNG;
		imagePNG = new Gdiplus::Image(const_cast<LPWSTR>(filePath.c_str()));
		Gdiplus::Graphics gp(hdc);
		static Gdiplus::Rect a = { 0,0, (INT)imagePNG->GetWidth(), (INT)imagePNG->GetHeight() };
		gp.DrawImage(imagePNG, a);
	}

	void Convert::LoadPNG(std::wstring &filePath)
	{
		if (imagePNG != NULL) delete imagePNG;
		imagePNG = new Gdiplus::Image(const_cast<LPWSTR>(filePath.c_str()));
	}

	void Convert::PNGToHDC(HDC hdc)
	{
		Gdiplus::Graphics gp(hdc);
		static Gdiplus::Rect a = { 0,0, (INT)imagePNG->GetWidth(), (INT)imagePNG->GetHeight() };
		gp.DrawImage(imagePNG, a);
	}

	void Convert::GDIPlusInit()
	{
		using namespace Gdiplus;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		imagePNG = NULL;
	}

	void Convert::GDIPlusDestroy()
	{
		using namespace Gdiplus;
		GdiplusShutdown(gdiplusToken);
	}
}