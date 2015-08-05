#pragma once

#include"opencv.hpp"
#include"vector"
#include"LeoRectTracker.h"
#include"Model.h"
#include"types.h"
class LeoPicture : public CWnd
{
public:
	LeoPicture(void);
	~LeoPicture(void);

	//{{AFX_MSG(CDendroCtl)
	afx_msg void		OnPaint();
	afx_msg BOOL		OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void	    OnMouseMove( UINT nFlags, CPoint point  );
	afx_msg void	    OnLButtonDown( UINT nFlags, CPoint point  );
	afx_msg void		OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void		OnRButtonDown(UINT nFlags, CPoint point);
	LRESULT				WindowProc(UINT mess, WPARAM wParam, LPARAM lParam);
	afx_msg int			OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual void		Draw(CDC *pDC);
	void				UpdateImage(cv::Mat image);
	cv::Point			ClientToImage(cv::Point &pt);
	cv::Point			ClientToImage(CPoint &pt);
	cv::Point			ImageToClient(cv::Point &pt);

	cv::Mat  m_img;
	cv::Rect RectRoi;
	LeoRectTracker		*m_RectTracker;


	LeoPicture & operator = (LeoPicture & other);
	LeoPicture(const LeoPicture& other) ; 
};

