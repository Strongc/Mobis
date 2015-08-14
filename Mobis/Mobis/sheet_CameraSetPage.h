#pragma once
#include"resource.h"
#include"MobisDlg.h"
// sheet_CameraSetPage dialog

class sheet_CameraSetPage : public CPropertyPage
{
	DECLARE_DYNAMIC(sheet_CameraSetPage)

public:
	sheet_CameraSetPage();
	virtual ~sheet_CameraSetPage();

	// Dialog Data
	enum { IDD = IDD_Cam_set };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	int getData(CMobisDlg*pMaindata);
public:
	afx_msg void OnBnClickedAppytrigertype();
	afx_msg void OnBnClickedConnectCam();
	afx_msg void OnCustomdrawSliderExposure(NMHDR *pNMHDR, LRESULT *pResult);

	CMobisDlg* m_pMaindata;
	int m_trigerType;
	NODE_HANDLE     m_hGainNode;                        // Handle to "GainRaw" node
	NODE_HANDLE     m_hExposureNode;                    // Handle to "ExposureTimeRaw" node
	afx_msg void OnCustomdrawSliderGain(NMHDR *pNMHDR, LRESULT *pResult);
};
