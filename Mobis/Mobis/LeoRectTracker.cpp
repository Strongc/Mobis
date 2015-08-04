#include "stdafx.h"
#include "LeoRectTracker.h"


LeoRectTracker::LeoRectTracker(void)
{
	m_nStyle=CRectTracker::resizeInside|CRectTracker::solidLine;//����RectTracker��ʽ
	m_nHandleSize = 6; //���Ʊ������ش�С
}


LeoRectTracker::~LeoRectTracker(void)
{
}

void LeoRectTracker::Draw(CDC* pDC) 
{

	CPen penBrown(PS_SOLID,1, RGB(192,110,0));
	CPen penGreen(PS_SOLID,2, RGB(0,192,0));
	CPen* pOldPen;
	// draw lines    // �߿���ɫ
	if ((m_nStyle & (dottedLine|solidLine)) != 0)
	{
		if (m_nStyle & dottedLine)
		{

			pOldPen = pDC->SelectObject(&penGreen);

		}
		else
		{
			pOldPen = pDC->SelectObject(&penBrown);
		}
		CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		pDC->Rectangle(&m_rect);

		//�����ĵ�
		SIZE size = {2,2};
		CRect centerRect(m_rect.CenterPoint(), size);
		pDC->FillSolidRect(centerRect,RGB(255,125,0));
	}



	// draw resize handles    // �˸��ڽǵ���ɫ
	if ((m_nStyle & (resizeInside|resizeOutside)) != 0)
	{
		UINT mask = GetHandleMask();
		CRect rect;
		for (int i = 0; i < 8; ++i)
		{
			if (mask & (1<<i))
			{
				GetHandleRect((TrackerHit)i, &rect);
				pDC->FillSolidRect(rect, RGB(125,125,0));    // RGB(0, 0, 0));
			}
		}
	}
}
