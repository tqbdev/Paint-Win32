#pragma once
#include "CEllipse.h"
#include "CRectangle.h"
#include "CLine.h"
#include <vector>

namespace MyPaint
{
	class CShapeCache
	{
	private:
		static std::vector<MyPaint::IShape*> shapeMap_;
	public:
		static void LoadCache();
		static void ClearCache();
		static IShape* GetShape(int shapeId);
	};
}