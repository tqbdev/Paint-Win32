#pragma once
#include "IShape.h"

namespace MyPaint
{
	class CRectangle : public IShape
	{
	public:
		CRectangle();
		~CRectangle();

		void Draw(HWND hWnd, POINT leftTop, POINT rightBottom, BOOL bSetRop = TRUE);
		void ReDraw(HWND hWnd);
		void WriteBinary(std::ofstream &out);
		void ReadBinary(std::ifstream &in);
	};
}