#include "stdafx.h"
#include "sheet_Seting.h"


sheet_Seting::sheet_Seting(void)
{
	AddPage(&m_CameraSetPage);
	AddPage(&m_DatabaseSetPage);
	AddPage(&m_LightSetPage);
}
sheet_Seting::sheet_Seting(CMobisDlg* pMaindata)
{
	m_CameraSetPage.getData(pMaindata);
	m_DatabaseSetPage.getData(pMaindata);
	m_LightSetPage.getData(pMaindata);
	AddPage(&m_CameraSetPage);
	AddPage(&m_DatabaseSetPage);
	AddPage(&m_LightSetPage);


	m_psh.pszCaption=_T("����"); //�������Ա���� 
	m_psh.dwFlags |= PSH_NOAPPLYNOW ; //ȥ����Ӧ�á���ť 

}


BOOL sheet_Seting::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	CWnd *pWnd2 = GetDlgItem( IDHELP );
	pWnd2->ShowWindow( FALSE );
	//CWnd *pWnd = GetDlgItem( IDCANCEL );
	//pWnd->ShowWindow( FALSE );
	//CWnd *pWnd3 = GetDlgItem( IDOK );
	//pWnd3->ShowWindow( FALSE );
	
	return bResult;

}
sheet_Seting::~sheet_Seting(void)
{


}
