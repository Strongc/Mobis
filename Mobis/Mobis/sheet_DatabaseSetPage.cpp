// sheet_DatabaseSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mobis.h"
#include "sheet_DatabaseSetPage.h"
#include "afxdialogex.h"


// sheet_DatabaseSetPage dialog

IMPLEMENT_DYNAMIC(sheet_DatabaseSetPage, CPropertyPage)

	sheet_DatabaseSetPage::sheet_DatabaseSetPage()
	: CPropertyPage(sheet_DatabaseSetPage::IDD)
	, m_SaveDays(100)
	, m_PicType(0)
{

}

BOOL sheet_DatabaseSetPage::OnInitDialog()
{
	m_PicType=::GetPrivateProfileInt("数据保存设置","图像格式",0,".//setting.ini");
	m_SaveDays=::GetPrivateProfileInt("数据保存设置","保存天数",100,".//setting.ini");
	UpdateData(false);
	return true;
}

sheet_DatabaseSetPage::~sheet_DatabaseSetPage()
{
}

void sheet_DatabaseSetPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Edit_SaveDays, m_SaveDays);
	DDV_MinMaxInt(pDX, m_SaveDays, 1, 365);
	DDX_Radio(pDX, IDC_RADIO1, m_PicType);
}


BEGIN_MESSAGE_MAP(sheet_DatabaseSetPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &sheet_DatabaseSetPage::OnBnClickedButton1)
END_MESSAGE_MAP()

int sheet_DatabaseSetPage::getData(CMobisDlg*pMaindata)
{

	m_pMaindata  = pMaindata;
	return true;
}



void sheet_DatabaseSetPage::OnBnClickedButton1()
{

	UpdateData(true);

	CString str;
	str.Format("%d",m_PicType);
	::WritePrivateProfileString("数据保存设置","图像格式",str,".//setting.ini"); 

	CString days;
	days.Format("%d",m_SaveDays);
	::WritePrivateProfileString("数据保存设置","保存天数",days,".//setting.ini"); 

	m_pMaindata->m_DataSave.UpdateParm();
}

