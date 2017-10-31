#include "stdafx.h"
#include "CRectangle.h"

namespace MyPaint
{
	CRectangle::CRectangle()
	{
	}


	CRectangle::~CRectangle()
	{
	}

	void CRectangle::Draw(HWND hWnd, POINT leftTop, POINT rightBottom, BOOL bSetRop)
	{
		this->leftTop_ = leftTop;
		this->rightBottom_ = rightBottom;

		HDC hdc = GetDC(hWnd);

		if (bSetRop == TRUE) SetROP2(hdc, R2_MERGEPENNOT); // Chế độ vẽ không làm ảnh hưởng đến các hình đã vẽ

		SelectObject(hdc, GetStockObject(NULL_BRUSH)); // Nền trong suốt

		Rectangle(hdc, leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

		ReleaseDC(hWnd, hdc);
	}

	void CRectangle::ReDraw(HWND hWnd)
	{
		Draw(hWnd, this->leftTop_, this->rightBottom_);
	}

	void CRectangle::WriteBinary(std::ofstream &out)
	{
		int id = 1;
		out.write((const char*)&id, sizeof(int));
		int leftTopX = leftTop_.x;
		int leftTopY = leftTop_.y;
		int rightBottomX = rightBottom_.x;
		int rightBottomY = rightBottom_.y;
		out.write((const char*)&leftTopX, sizeof(int));
		out.write((const char*)&leftTopY, sizeof(int));
		out.write((const char*)&rightBottomX, sizeof(int));
		out.write((const char*)&rightBottomY, sizeof(int));
	}

	void CRectangle::ReadBinary(std::ifstream &in)
	{
		int leftTopX, leftTopY, rightBottomX, rightBottomY;
		in.read((char*)&leftTopX, sizeof(int));
		in.read((char*)&leftTopY, sizeof(int));
		in.read((char*)&rightBottomX, sizeof(int));
		in.read((char*)&rightBottomY, sizeof(int));

		leftTop_.x = leftTopX;
		leftTop_.y = leftTopY;
		rightBottom_.x = rightBottomX;
		rightBottom_.y = rightBottomY;
	}
}