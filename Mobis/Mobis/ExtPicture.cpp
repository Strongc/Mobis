
#include "stdafx.h"
#include "ExtPicture.h"
#include "CvvImage.h"
#include"resource.h"
#include "types.h"
//---------------------------------------------------------------------
ExtPicture::ExtPicture()
{
	m_ID =0;
}

void ExtPicture::loadImage(cv::Mat image)
{
	m_img=image;
	this->Invalidate();
}
//---------------------------------------------------------------------
ExtPicture::~ExtPicture()
{
}
//---------------------------------------------------------------------

BEGIN_MESSAGE_MAP(ExtPicture, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEACTIVATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENU_ADD, OnMenuAdd) 
	ON_COMMAND(ID_MENU_DELETE, OnMenuDelete) 
	ON_COMMAND(ID_MENU_ADD_POSITION, OnMenuAddPosition) 
END_MESSAGE_MAP()

//---------------------------------------------------------------------
void ExtPicture::Draw(CDC *pDC)
{
	CRect myrect;
	GetClientRect(&myrect);	//ȡ�ÿͻ����ߴ�
	if(m_img.data==NULL)
	{
		pDC->Rectangle(&myrect);
		return;
	}

	else 
	{
		IplImage* img=&(IplImage)(m_img);		//��ͼ��ת��ΪIplImage��ʽ������ͬһ���ڴ棨ǳ������
		CvvImage iimg;								//����һ��CvvImage����
		iimg.CopyOf(img);

		HDC hDC=pDC->GetSafeHdc();	
		iimg.DrawToHDC(hDC,&myrect);
	}
}
//---------------------------------------------------------------------
void ExtPicture::OnPaint()
{
	CPaintDC dc(this);
	Draw(&dc);
}
//---------------------------------------------------------------------
void ExtPicture::OnLButtonDown( UINT nFlags, CPoint point  )
{

	CWnd::OnLButtonDown(nFlags, point);
}
//---------------------------------------------------------------------
void ExtPicture::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	HWND  Hparent = ::GetParent(m_hWnd);
	::SendMessageA(Hparent,WM_EXTPICMENU_ADD,0,m_ID);


}
void ExtPicture::OnMenuAdd()
{
	HWND  Hparent = ::GetParent(m_hWnd);
	::SendMessageA(Hparent,WM_EXTPICMENU_ADD,0,m_ID);
}
void ExtPicture::OnMenuDelete()
{
	HWND  Hparent = ::GetParent(m_hWnd);
	::SendMessageA(Hparent,WM_EXTPICMENU_DELETE,0,m_ID);
}
void ExtPicture::OnMenuAddPosition()
{
	HWND  Hparent = ::GetParent(m_hWnd);
	::SendMessageA(Hparent,WM_EXTPICMENU_ADD_POSITON,0,m_ID);
}
//---------------------------------------------------------------------
void ExtPicture::OnContextMenu(CWnd* pWnd, CPoint pos)
{
	CMenu menu1;
	menu1.CreatePopupMenu();     //��̬��������ʽ�˵�����
	menu1.AppendMenu(MF_STRING,ID_MENU_ADD," ���ģ��");
	menu1.AppendMenu(MF_STRING,ID_MENU_DELETE," ɾ��ģ��");
	menu1.AppendMenu(MF_STRING,ID_MENU_ADD_POSITION," ����λ�����ģ��");
	CPoint pt;
	GetCursorPos(&pt);
	menu1.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);

	menu1.DestroyMenu();

	//CMenu menu,*pSubMenu;//��������Ҫ�õ���cmenu����  	//   menu.LoadMenu(IDR_MENU1);//װ���Զ�����Ҽ��˵�  	//   pSubMenu=menu.GetSubMenu(0);//��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�  	//   CPoint oPoint;//����һ������ȷ�����λ�õ�λ��  	//   GetCursorPos(&oPoint);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����  	//   pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this);   //��ָ��λ����ʾ�����˵�
	CWnd::OnContextMenu(pWnd, pos);
	int x=0;
}
//---------------------------------------------------------------------
LRESULT ExtPicture::WindowProc(UINT msg, WPARAM wParam, LPARAM lParam) 
{

	if (msg == WM_NCHITTEST || msg == WM_NCLBUTTONDOWN || msg == WM_NCLBUTTONDBLCLK) 
		return ::DefWindowProc(m_hWnd, msg, wParam, lParam); 
	return CWnd::WindowProc(msg, wParam, lParam); 
}	
//---------------------------------------------------------------------
int ExtPicture::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// necessary for getting mousewheel messages
	int status = CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
	SetFocus();
	return status;
}
//---------------------------------------------------------------------
