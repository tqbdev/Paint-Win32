#pragma once
#include "CShape.h"

namespace MyPaint
{
	class CEllipse : public CShape
	{
	public:
		CEllipse();
		~CEllipse();

		void Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF colorOutline, DashStyle penStyle, double penWidth, COLORREF colorFill);
		void WriteBinary(std::ofstream &out);
	};
}