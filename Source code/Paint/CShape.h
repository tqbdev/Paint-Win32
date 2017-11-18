#pragma once
#include "IShape.h"

namespace MyPaint
{
	class CShape : public IShape
	{
	public:
		virtual void Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF color, DashStyle penStyle, double penWidth, BOOL bSetRop = TRUE) = 0;
		virtual void ReDraw(Graphics *gp);
		virtual void SetValue(POINT leftTop, POINT rightBottom, COLORREF color = RGB(0, 0, 0), DashStyle penStyle = DashStyle::DashStyleSolid, double penWidth = 1.0F);
		virtual void WriteBinary(std::ofstream &out);
		virtual void ReadBinary(std::ifstream &in);
	};
}