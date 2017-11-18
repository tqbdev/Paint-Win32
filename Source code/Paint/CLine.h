#pragma once
#include "CShape.h"

namespace MyPaint
{
	class CLine : public CShape
	{
	public:
		CLine();
		~CLine();

		void Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF color, DashStyle penStyle, double penWidth, BOOL bSetRop = TRUE);
		void WriteBinary(std::ofstream &out);
	};
}