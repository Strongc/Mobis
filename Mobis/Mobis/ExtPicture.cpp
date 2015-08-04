
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
	GetClientRect(&myrect);	//取得客户区尺寸
	if(m_img.data==NULL)
	{
		pDC->Rectangle(&myrect);
		return;
	}

	else 
	{
		IplImage* img=&(IplImage)(m_img);		//将图像转换为IplImage格式，共用同一个内存（浅拷贝）
		CvvImage iimg;								//创建一个CvvImage对象
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
	menu1.CreatePopupMenu();     //动态创建弹出式菜单对象
	menu1.AppendMenu(MF_STRING,ID_MENU_ADD," 添加模型");
	menu1.AppendMenu(MF_STRING,ID_MENU_DELETE," 删除模型");
	menu1.AppendMenu(MF_STRING,ID_MENU_ADD_POSITION," 根据位置添加模型");
	CPoint pt;
	GetCursorPos(&pt);
	menu1.TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);

	menu1.DestroyMenu();

	//CMenu menu,*pSubMenu;//定义下面要用到的cmenu对象  	//   menu.LoadMenu(IDR_MENU1);//装载自定义的右键菜单  	//   pSubMenu=menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单  	//   CPoint oPoint;//定义一个用于确定光标位置的位置  	//   GetCursorPos(&oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标  	//   pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this);   //在指定位置显示弹出菜单
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
