#pragma once
#include"resource.h"
#include"MobisDlg.h"
#include "cmscomm.h"
#include "afxwin.h"


class sheet_LightSetPage : public CPropertyPage
{
	DECLARE_DYNAMIC(sheet_LightSetPage)

public:
	sheet_LightSetPage();
	virtual ~sheet_LightSetPage();

	// Dialog Data
	enum { IDD = IDD_Light_set };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	int getData(CMobisDlg*pMaindata);
public:
	CMobisDlg* m_pMaindata;
	CMSComm m_MSComm;
	CString m_Edit_SendMessage;
	CString m_Edit_ReciveMessage;
	CButton m_openComm;		//ÇÐ»»°´Å¥
	BOOL m_openComm_check;

	DECLARE_EVENTSINK_MAP()
	void OnCommMscommLight();
	afx_msg void OnBnClickedOpencom();
	afx_msg void OnBnClickedbtnSendmessage();
};
