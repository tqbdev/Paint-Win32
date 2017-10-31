#pragma once
#include "CEllipse.h"
#include "CRectangle.h"
#include "CLine.h"

namespace MyPaint
{
	class CShapeFactory
	{
	public:
		IShape* GetShape(int shapeId);
	};
}