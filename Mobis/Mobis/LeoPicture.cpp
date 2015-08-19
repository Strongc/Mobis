#include "stdafx.h"
#include "LeoPicture.h"
#include "CvvImage.h"
#include"resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LeoPicture::LeoPicture(void)
{
	m_RectTracker=NULL;
	InitializeCriticalSection(&m_protect4m_img); 
}


LeoPicture::~LeoPicture(void)
{

}

//---------------------------------------------------------------------
BEGIN_MESSAGE_MAP(LeoPicture, CWnd)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEACTIVATE()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

//---------------------------------------------------------------------

//--------------------------------------------------------------------

void LeoPicture::OnPaint()
{
	
	CPaintDC dc(this);
	EnterCriticalSection(&m_protect4m_img); 
	Draw(&dc);
	LeaveCriticalSection(&m_protect4m_img); 
}

//---------------------------------------------------------------------
BOOL LeoPicture::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	ScreenToClient(&pt);
	cv::Point pt_source = ClientToImage(pt);

	double m_zoomFactor = (double)RectRoi.width/(double)m_img.cols;

	zDelta =zDelta/120;
	if(zDelta<0)
	{
		zDelta = -zDelta;
		m_zoomFactor =m_zoomFactor*pow( 0.9,zDelta);
	}		
	else
	{
		m_zoomFactor = m_zoomFactor*pow((1/0.9),zDelta);
	}
	if(m_zoomFactor>1)
		m_zoomFactor=1;
	else if(m_zoomFactor<0.01)
		m_zoomFactor=0.01;




	CRect rClient;
	GetClientRect(rClient);
	double img_x = (m_zoomFactor*(double)m_img.cols/(double)rClient.Width())*pt.x+RectRoi.x;
	double img_y = (m_zoomFactor*(double)m_img.rows/(double)rClient.Height())*pt.y+RectRoi.y;
	Point pt_change = Point(img_x,img_y);


	cv::Point direct = pt_source -  pt_change;
	int show_OX = RectRoi.x+direct.x;
	int show_OY = RectRoi.y+direct.y;
	int show_width =m_zoomFactor* (double)m_img.cols;
	int show_height =m_zoomFactor* (double)m_img.rows;
	cv::Point pt1(show_OX,show_OY);
	cv::Point pt2(show_OX+show_width,show_OY+show_height);



	cv::Rect m_rect = cv::Rect(0,0,m_img.cols,m_img.rows); 
	if(m_rect.contains(pt1)&&m_rect.contains(pt2))
		RectRoi = cv::Rect(show_OX,show_OY,show_width,show_height);
	else if(!m_rect.contains(pt1)&&m_rect.contains(pt2))
	{
		if(pt1.x<=0)
			pt1.x=0;
		if(pt1.y<=0)
			pt1.y=0;
		RectRoi = cv::Rect(pt1,cv::Size(show_width,show_height));
	}
	else if(m_rect.contains(pt1)&&!m_rect.contains(pt2))
	{
		if(pt2.x>m_img.cols)
			pt2.x=m_img.cols;
		if(pt2.y>m_img.rows)
			pt2.y=m_img.rows;
		RectRoi = cv::Rect(cv::Point(pt2.x-show_width,pt2.y-show_height),pt2);
	}
	else if(!m_rect.contains(pt1)&&!m_rect.contains(pt2))
	{
		if(pt1.x<=0)
			pt1.x=0;
		if(pt1.y<=0)
			pt1.y=0;

		if(pt2.x>m_img.cols)
			pt2.x=m_img.cols;
		if(pt2.y>m_img.rows)
			pt2.y=m_img.rows;
		RectRoi = cv::Rect(pt1,pt2);
	}
	Invalidate();
	return true;
}
//---------------------------------------------------------------------
void LeoPicture::OnLButtonDown( UINT nFlags, CPoint point  )
{
	if(m_RectTracker!=NULL)
	{
		CRect cwrect;
		GetWindowRect(&cwrect); //��ȡ�����пؼ�������
		ScreenToClient(&cwrect); //ת��Ϊ��������CRect  if(point.x>cwrect.left && point.y>cwrect.top    //ȷ�����µ������ڿؼ�������   && point.x
		{
			if(m_RectTracker->HitTest(point)<0)     //���δ���о���ѡ���,���»�ѡ���
			{             
				m_RectTracker->TrackRubberBand(this,point,TRUE);
				m_RectTracker->m_rect.NormalizeRect();   //���滯���Σ��������滯���������н��ܣ�
			}
			else           //������о���ѡ���
			{  
				m_RectTracker->Track(this,point,TRUE);
				m_RectTracker->m_rect.NormalizeRect();   //���滯����
				//SendMessage(WM_LBUTTONUP,NULL,NULL);
			}
			Invalidate();   //ˢ�´�������ʹ��CrectTracker�����ػ浽������
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void LeoPicture::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(m_RectTracker!=NULL)
	{
		HWND  Hparent = ::GetParent(m_hWnd);
		::SendMessageA(Hparent,WM_ZOOMCTRL_LDCLICK,0,0);
	}
}
//---------------------------------------------------------------------
void LeoPicture::OnRButtonDown(UINT nFlags, CPoint point)
{
	if(m_RectTracker!=NULL)
	{
		HWND  Hparent = ::GetParent(m_hWnd);
		::SendMessageA(Hparent,WM_ZOOMCTRL_RCLICK,0,0);
	}
}
//---------------------------------------------------------------------
void LeoPicture::OnMouseMove( UINT nFlags, CPoint point  )
{

	long x = point.x;
	long y = point.y;

}
//---------------------------------------------------------------------
LRESULT LeoPicture::WindowProc(UINT msg, WPARAM wParam, LPARAM lParam) 
{
	// necessary for getting h/vscroll msgs
	if (msg == WM_NCHITTEST || msg == WM_NCLBUTTONDOWN || msg == WM_NCLBUTTONDBLCLK) 
		return ::DefWindowProc(m_hWnd, msg, wParam, lParam); 
	return CWnd::WindowProc(msg, wParam, lParam); 
} 
//---------------------------------------------------------------------
int LeoPicture::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// necessary for getting mousewheel messages
	int status = CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	SetFocus();
	return status;
}
//---------------------------------------------------------------------


void LeoPicture::Draw(CDC *pDC)
{
	if (m_img.empty())
		return;


	cv::Mat showMat=m_img.clone();
	cv::Mat showImage(showMat,RectRoi); //��ȡ��չ��ͼ��

	CRect rClient;
	GetClientRect(&rClient);			//ȡ�ÿͻ����ߴ�

	IplImage* img=&(IplImage)showImage;	//��ͼ��ת��ΪIplImage��ʽ������ͬһ���ڴ棨ǳ������
	CvvImage iimg;						//����һ��CvvImage����
	iimg.CopyOf(img);

	HDC hDC=pDC->GetSafeHdc();	
	iimg.DrawToHDC(hDC,&rClient);


	if(m_RectTracker!=NULL)
		m_RectTracker->Draw(pDC);


}

cv::Point LeoPicture::ClientToImage(CPoint &pt)
{
	cv::Point ppt = cv::Point(pt.x,pt.y);
	return ClientToImage(ppt);
}

cv::Point LeoPicture::ClientToImage(cv::Point &pt)
{

	//��ȡpicture�ؼ���С
	CRect rClient;
	GetClientRect(rClient);
	//��ȡҪ��ʾͼ��ʵ�ʴ�С�����أ�	
	CRect rImage(0,0,m_img.cols,m_img.rows);

	double img_x = ((double)RectRoi.width/(double)rClient.Width())*pt.x+RectRoi.x;
	double img_y = ((double)RectRoi.height/(double)rClient.Height())*pt.y+RectRoi.y;
	return cv::Point(img_x,img_y);
}

cv::Point LeoPicture::ImageToClient(cv::Point &pt)
{

	//��ȡpicture�ؼ���С
	CRect rClient;
	GetClientRect(rClient);
	//��ȡҪ��ʾͼ��ʵ�ʴ�С�����أ�	
	CRect rImage(0,0,m_img.cols,m_img.rows);

	//get pt���Ӧͼ�������
	double img_x = ((double)rClient.Width() /(double)RectRoi.width )*(pt.x-RectRoi.x);
	double img_y = ((double)rClient.Height()/(double)RectRoi.height)*(pt.y-RectRoi.y);

	return cv::Point(img_x,img_y);
}

void LeoPicture::UpdateImage(cv::Mat image)
{
	EnterCriticalSection(&m_protect4m_img); 
	Mat tempShow = image.clone();//��ʾʱת��Ϊ��ɫͼ��
	if(image.channels()==1)
		cvtColor(tempShow,tempShow,CV_GRAY2RGB);
	if(tempShow.rows==m_img.rows&&tempShow.cols==m_img.cols)
	{
		m_img=tempShow;
	}
	else 
	{
		m_img=tempShow;
		RectRoi = Rect(0,0,m_img.cols,m_img.rows);
	}
	LeaveCriticalSection(&m_protect4m_img); 


	CRect rect;
	GetClientRect(rect);  
	InvalidateRect(rect);
	//Invalidate();
	/*CClientDC dc(this);
	EnterCriticalSection(&m_protect4m_img); 
	Draw(&dc);
	LeaveCriticalSection(&m_protect4m_img); */
}


LeoPicture & LeoPicture::operator = (LeoPicture & other)
{
	return *this;
}

//�������캯��  
LeoPicture::LeoPicture(const LeoPicture& other)  
{  
	;
}  


