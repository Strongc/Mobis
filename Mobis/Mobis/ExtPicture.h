// zoomctrl.h
//---------------------------------------------------------------------
#ifndef EXTPICTURE_H
#define EXTPICTURE_H
#include"opencv.hpp"



//---------------------------------------------------------------------
class ExtPicture : public CWnd
{
public:
	ExtPicture();
	~ExtPicture();
	void loadImage(cv::Mat image);
	

	afx_msg void		OnPaint();
	afx_msg void	    OnLButtonDown( UINT nFlags, CPoint point  );
	afx_msg void		OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void		OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void		OnMenuAdd(); 
	afx_msg void		OnMenuDelete();
	afx_msg void        OnMenuAddPosition();
	LRESULT				WindowProc(UINT mess, WPARAM wParam, LPARAM lParam);
	afx_msg int			OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual void		Draw(CDC *pDC);

	DECLARE_MESSAGE_MAP()
public:
	cv::Mat  m_img;
	int m_ID;
};
//---------------------------------------------------------------------
#endif 
