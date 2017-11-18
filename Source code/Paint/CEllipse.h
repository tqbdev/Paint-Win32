#pragma once
#include "CShape.h"

namespace MyPaint
{
	class CEllipse : public CShape
	{
	public:
		CEllipse();
		~CEllipse();

		void Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF color, DashStyle penStyle, double penWidth, BOOL bSetRop = TRUE);
		void WriteBinary(std::ofstream &out);
	};
}