#include "stdafx.h"
#include "CLine.h"

namespace MyPaint
{
	CLine::CLine()
	{
	}


	CLine::~CLine()
	{
	}

	void CLine::Draw(HWND hWnd, POINT leftTop, POINT rightBottom, BOOL bSetRop, HDC hdc)
	{
		this->leftTop_ = leftTop;
		this->rightBottom_ = rightBottom;

		BOOL fCheck = FALSE;
		if (hdc == NULL)
		{
			hdc = GetDC(hWnd);
			fCheck = TRUE;
		}

		if (bSetRop == TRUE) SetROP2(hdc, R2_MERGEPENNOT); // Chế độ vẽ không làm ảnh hưởng đến các hình đã vẽ

		MoveToEx(hdc, leftTop.x, leftTop.y, NULL);
		LineTo(hdc, rightBottom.x, rightBottom.y);

		if (fCheck) ReleaseDC(hWnd, hdc);
	}

	void CLine::ReDraw(HWND hWnd, HDC hdc)
	{
		Draw(hWnd, this->leftTop_, this->rightBottom_, TRUE, hdc);
	}

	void CLine::WriteBinary(std::ofstream &out)
	{
		int id = 0;
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

	void CLine::ReadBinary(std::ifstream &in)
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