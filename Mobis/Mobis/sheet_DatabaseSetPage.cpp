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
	, m_dataPath(_T(""))
{

}

BOOL sheet_DatabaseSetPage::OnInitDialog()
{
	m_PicType=::GetPrivateProfileInt("���ݱ�������","ͼ���ʽ",0,".//setting.ini");
	m_SaveDays=::GetPrivateProfileInt("���ݱ�������","��������",100,".//setting.ini");
	::GetPrivateProfileString("���ݱ�������","���ݱ���·��",".//data",m_dataPath.GetBuffer(MAX_PATH),MAX_PATH,".//setting.ini");
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
	DDX_Text(pDX, IDC_EDIT1, m_dataPath);
}


BEGIN_MESSAGE_MAP(sheet_DatabaseSetPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &sheet_DatabaseSetPage::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_ChosePath, &sheet_DatabaseSetPage::OnBnClickedChosepath)
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
	::WritePrivateProfileString("���ݱ�������","ͼ���ʽ",str,".//setting.ini"); 

	CString days;
	days.Format("%d",m_SaveDays);
	::WritePrivateProfileString("���ݱ�������","��������",days,".//setting.ini"); 

	::WritePrivateProfileStringA("���ݱ�������","���ݱ���·��",m_dataPath,".//setting.ini"); 
	m_pMaindata->m_DataSave.UpdateParm();
}



void sheet_DatabaseSetPage::OnBnClickedChosepath()
{


	char szSelected[MAX_PATH];//��������ļ���·��
	BROWSEINFO bi= {NULL};
	LPITEMIDLIST pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.lpszTitle = "ѡ������ļ�·��";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	if((pidl = SHBrowseForFolder(&bi))!=NULL)
	{
		if(SUCCEEDED(SHGetPathFromIDList(pidl,szSelected)))
		{
			m_dataPath = szSelected; 
			UpdateData(false);
		}
	}

	
}