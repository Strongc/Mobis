#pragma once
#include "afxcmn.h"


// LoadManage dialog

class LoadManage : public CDialogEx
{
	DECLARE_DYNAMIC(LoadManage)

public:
	LoadManage(CWnd* pParent = NULL);   // standard constructor
	virtual ~LoadManage();

	// Dialog Data
	enum { IDD = IDD_LOADMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	_ConnectionPtr	m_pConnection;
	_RecordsetPtr	m_pRecordset;

	CListCtrl m_list_password;
	CString m_add_name;
	CString m_add_password;

	void exchangDatabase(bool direct=true);
	void dump_com_error(_com_error &e);
	void openRecordset();
	void closeRecordset();
	afx_msg BOOL OnInitDialog();
	afx_msg void OnDestroy()  ;
	afx_msg void OnBnClickedDeleteZhaohao();
	afx_msg void OnBnClickedAddZhaohao();

};
