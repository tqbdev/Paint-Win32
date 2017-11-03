#pragma once
#include "IShape.h"

namespace MyPaint
{
	class CEllipse : public IShape
	{
	public:
		CEllipse();
		~CEllipse();

		void Draw(HWND hWnd, POINT leftTop, POINT rightBottom, BOOL bSetRop = TRUE, HDC hdc = NULL);
		void ReDraw(HWND hWnd, HDC hdc = NULL);
		void WriteBinary(std::ofstream &out);
		void ReadBinary(std::ifstream &in);
	};
}