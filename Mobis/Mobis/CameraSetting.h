#pragma once
#include "cmscomm.h"
#include "afxwin.h"

#define MAX_BUFFER_SIZE 1024
// CameraSetting dialog

class CameraSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CameraSetting)

public:
	CameraSetting(CWnd* pParent = NULL);   // standard constructor
	virtual ~CameraSetting();

// Dialog Data
	enum { IDD = IDD_CAMERASETTINDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedButton2();
	
	CString m_Edit;
	CString m_Edit2;
	CMSComm m_MSComm;
};
