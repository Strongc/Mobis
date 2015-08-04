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

	DECLARE_MESSAGE_MAP()
public:
	int getData(CMobisDlg*pMaindata);
public:
	CMobisDlg* m_pMaindata;
	int m_trigerType;
	afx_msg void OnBnClickedAppytrigertype();
	afx_msg void OnBnClickedConnectCam();
};
