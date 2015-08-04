//// zoomctrl.h
////---------------------------------------------------------------------
//#ifndef _H_ZoomCtrl
//#define _H_ZoomCtrl
//#include"opencv.hpp"
//#include "LeoRectTracker.h"
//#include"vector"
//#include"Model.h"
////---------------------------------------------------------------------
//
//#define WM_ZOOMCTRL_LDCLICK WM_USER+103
//#define WM_ZOOMCTRL_RCLICK WM_USER+104
//class CZoomCtrl : public CWnd
//{
//public:
//	CZoomCtrl();
//	~CZoomCtrl();
//	
//
//	double				GetZoomFactor() const		{ return m_zoomFactor; }
//	void				SetZoomFactor(double d)		{ m_zoomFactor = d; }
//
//	//{{AFX_MSG(CDendroCtl)
//	afx_msg void		OnPaint();
//	afx_msg BOOL		OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//	afx_msg void	    OnMouseMove( UINT nFlags, CPoint point  );
//	afx_msg void	    OnLButtonDown( UINT nFlags, CPoint point  );
//	afx_msg void		OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg void		OnRButtonDown(UINT nFlags, CPoint point);
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
//
//	LRESULT				WindowProc(UINT mess, WPARAM wParam, LPARAM lParam);
//	afx_msg int			OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
//	afx_msg BOOL		OnEraseBkgnd(CDC* pDC);
//
//public:
//	virtual void		Draw(CDC *pDC);
//	cv::Point			ClientToImage(cv::Point &pt);
//	cv::Point			ClientToImage(CPoint &pt);
//	void				InitImage(cv::Mat image);
//	void				UpdateImage(cv::Mat image);
//	void				AddRelatedModel(Model* mod);
//
//
//	
//	cv::Mat  m_img;
//	cv::Rect RectRoi;
//	double	m_zoomFactor;
//
//	std::vector<Model*> ptr_models;
//	LeoRectTracker  *m_RectTracker;
//};
////---------------------------------------------------------------------
//#endif // _H_ZoomCtrl




#pragma once
#include "LeoPicture.h"
#include"opencv.hpp"
#include"vector"
#include"Model.h"
#include "CvvImage.h"

class LeoPicture_For_SelectDlg :public LeoPicture
{
public:
	LeoPicture_For_SelectDlg(void);
	~LeoPicture_For_SelectDlg(void);

public:
	virtual void Draw(CDC *pDC);
	void AddRelatedModel(Model mod);


	std::vector<Model>  models;
	int ID;
};