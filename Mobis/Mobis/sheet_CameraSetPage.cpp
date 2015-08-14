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
{
	m_hGainNode = NULL;
	m_hExposureNode = NULL;
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
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_EXPOSURE, &sheet_CameraSetPage::OnCustomdrawSliderExposure)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_GAIN, &sheet_CameraSetPage::OnCustomdrawSliderGain)
END_MESSAGE_MAP()


BOOL sheet_CameraSetPage::OnInitDialog()
{
	if(m_pMaindata->m_cameraManage.m_cameraList.empty())
	{
		GetDlgItem(IDC_SLIDER_GAIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SLIDER_EXPOSURE)->EnableWindow(FALSE);
		return TRUE;
	}

	if(!m_pMaindata->m_cameraManage.m_cameraList.empty())
		m_trigerType = m_pMaindata->m_cameraManage.m_cameraList[0].m_TrigSetting;
	UpdateData(FALSE);



	CAM_HANDLE  m_hCam=  m_pMaindata->m_cameraManage.m_cameraList[1].m_hCam;
	J_STATUS_TYPE   retval;
	NODE_HANDLE hNode;
	int64_t int64Val;
	CSliderCtrl* pSCtrl;
	// Get SliderCtrl for Gain
	pSCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_GAIN);

	// Get Gain Node

	retval = J_Camera_GetNodeByName(m_hCam, (int8_t*)"GainRaw", &m_hGainNode);
	if (retval == J_ST_SUCCESS)
	{
		int minGain = 0;
		int maxGain = 0;
		int currentGain = 0;

		// Get/Set Min
		retval = J_Node_GetMinInt64(m_hGainNode, &int64Val);
		pSCtrl->SetRangeMin((int)int64Val, TRUE);

		minGain = (int)int64Val;

		// Get/Set Max
		retval = J_Node_GetMaxInt64(m_hGainNode, &int64Val);
		pSCtrl->SetRangeMax((int)int64Val, TRUE);

		maxGain = (int)int64Val;

		// Get/Set Value
		retval = J_Node_GetValueInt64(m_hGainNode, TRUE, &int64Val);
		pSCtrl->SetPos((int)int64Val);

		currentGain = (int)int64Val;

		SetDlgItemInt(IDC_IMAGE_GAIN_EDIT, currentGain);


		pSCtrl->SetSelection(minGain, maxGain);
		pSCtrl->SetTicFreq((maxGain-minGain)/50);
	}
	else
	{
		pSCtrl->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_IMAGE_GAIN_EDIT)->ShowWindow(SW_HIDE);
	}

	//- Exposure time -----------------------------------------------

	// We have two possible ways of setting up Exposure time: JAI or GenICam SFNC
	// The JAI Exposure time setup uses a node called "ShutterMode" and the SFNC 
	// does not need to set up anything in order to be able to control the exposure time.
	// Therefor we have to determine which way to use here.
	// First we see if a node called "ShutterMode" exists.
	//retval = J_Camera_GetNodeByName(m_hCam, (int8_t*)"ShutterMode", &hNode);

	//// Does the "ShutterMode" node exist?
	//if ((retval == J_ST_SUCCESS) && (hNode != NULL))
	//{
	//	// Here we assume that this is JAI way so we do the following:
	//	// ShutterMode=ProgrammableExposure
	//	// Make sure that the ShutterMode selector is set to ProgrammableExposure
	//	retval = J_Camera_SetValueString(m_hCam, (int8_t*)"ShutterMode", (int8_t*)"ProgrammableExposure");
	//}

	// Get SliderCtrl for Exposure
	pSCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXPOSURE);

	// Get ExposureTimeRaw Node
	retval = J_Camera_GetNodeByName(m_hCam, (int8_t*)"ExposureTimeRaw", &m_hExposureNode);
	if (retval == J_ST_SUCCESS)
	{
		int minExposure = 0;
		int maxExposure = 0;
		int currentExposure = 0;

		// Get/Set Min
		retval = J_Node_GetMinInt64(m_hExposureNode, &int64Val);
		pSCtrl->SetRangeMin((int)int64Val, TRUE);

		minExposure = (int)int64Val;

		// Get/Set Max
		retval = J_Node_GetMaxInt64(m_hExposureNode, &int64Val);
		pSCtrl->SetRangeMax((int)int64Val, TRUE);

		maxExposure = (int)int64Val;

		// Get/Set Value
		retval = J_Node_GetValueInt64(m_hExposureNode, TRUE, &int64Val);
		pSCtrl->SetPos((int)int64Val);

		currentExposure = (int)int64Val;

		SetDlgItemInt(IDC_IMAGE_EXPOSURE_EDIT, currentExposure);
		pSCtrl->SetSelection(minExposure, maxExposure);
		pSCtrl->SetTicFreq((maxExposure-minExposure)/50);
	}
	else
	{
		pSCtrl->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_IMAGE_EXPOSURE_EDIT)->ShowWindow(SW_HIDE);
	}



	return true;
}

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
	if(!m_cameraManage.m_cameraIDList.empty())
	{
		//Sleep(10000);
		m_cameraManage.allocationCameraConnect();
	}



}




void sheet_CameraSetPage::OnCustomdrawSliderExposure(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;

	CSliderCtrl* pSCtrl;
	int iPos;
	J_STATUS_TYPE   retval;
	NODE_HANDLE hNode;

	// Get SliderCtrl for Exposure
	pSCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXPOSURE);
	// Is this scroll event from the Exposure Slider?

	// Get current slider position
	iPos = pSCtrl->GetPos();

	// Set Value
	retval = J_Node_SetValueInt64(m_hExposureNode, TRUE, (int64_t)iPos);

	// Update the Text Control with the new value
	SetDlgItemInt(IDC_IMAGE_EXPOSURE_EDIT, iPos);




}


void sheet_CameraSetPage::OnCustomdrawSliderGain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;

	CSliderCtrl* pSCtrl;
	int iPos;
	J_STATUS_TYPE   retval;
	NODE_HANDLE hNode;

	// Get SliderCtrl for Gain
	pSCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_GAIN);
	// Is this scroll event from the Gain Slider?

	// Get current slider position
	iPos = pSCtrl->GetPos();

	// Set Value
	retval = J_Node_SetValueInt64(m_hGainNode, TRUE, (int64_t)iPos);

	// Update the Text Control with the new value
	SetDlgItemInt(IDC_IMAGE_GAIN_EDIT, iPos);
}
