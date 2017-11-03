#pragma once
#include <windows.h>
#include <fstream>

namespace MyPaint
{
	// Interface for all shapes
	class IShape
	{
	protected:
		POINT leftTop_;
		POINT rightBottom_;

	public:
		virtual void Draw(HWND hWnd, POINT leftTop, POINT rightBottom, BOOL bSetRop = TRUE, HDC hdc = NULL) = 0;
		virtual void ReDraw(HWND hWnd, HDC hdc = NULL) = 0;
		virtual void WriteBinary(std::ofstream &out) = 0;
		virtual void ReadBinary(std::ifstream &in) = 0;
	};
}