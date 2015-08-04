// sheet_CameraSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mobis.h"
#include "sheet_CameraSetPage.h"
#include "afxdialogex.h"


// sheet_CameraSetPage dialog

IMPLEMENT_DYNAMIC(sheet_CameraSetPage, CPropertyPage)

	sheet_CameraSetPage::sheet_CameraSetPage()
	: CPropertyPage(sheet_CameraSetPage::IDD)
	, m_trigerType(0)
{

}

sheet_CameraSetPage::~sheet_CameraSetPage()
{
}

void sheet_CameraSetPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_SOFTWARE, m_trigerType);
}


BEGIN_MESSAGE_MAP(sheet_CameraSetPage, CPropertyPage)
	ON_BN_CLICKED(IDC_AppyTrigerType, &sheet_CameraSetPage::OnBnClickedAppytrigertype)
	ON_BN_CLICKED(IDC_ConnectCam, &sheet_CameraSetPage::OnBnClickedConnectCam)
END_MESSAGE_MAP()



int sheet_CameraSetPage::getData(CMobisDlg*pMaindata)
{

	m_pMaindata  = pMaindata;
	return true;
}
// sheet_CameraSetPage message handlers


void sheet_CameraSetPage::OnBnClickedAppytrigertype()
{
	UpdateData(true);

	int num = m_pMaindata->m_cameraManage.m_cameraList.size();
	for (int i = 0; i < num; i++)
	{
		if(m_pMaindata->m_cameraManage.m_cameraList[i].m_TrigSetting!=m_trigerType)
			m_pMaindata->m_cameraManage.m_cameraList[i].changeAcquitionModel(m_trigerType);
	}

}


void sheet_CameraSetPage::OnBnClickedConnectCam()
{
	cameraManage &m_cameraManage = m_pMaindata->m_cameraManage;


	m_cameraManage.findCamera();
	if(m_cameraManage.m_cameraIDList.size()>=1)
	{
		//Sleep(10000);
		m_cameraManage.allocationCameraConnect();
	}



}


