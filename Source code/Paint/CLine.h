#pragma once
#include "IShape.h"

namespace MyPaint
{
	class CLine : public IShape
	{
	public:
		CLine();
		~CLine();

		void Draw(HWND hWnd, POINT leftTop, POINT rightBottom, BOOL bSetRop = TRUE, HDC hdc = NULL);
		void ReDraw(HWND hWnd, HDC hdc = NULL);
		void WriteBinary(std::ofstream &out);
		void ReadBinary(std::ifstream &in);
	};
}