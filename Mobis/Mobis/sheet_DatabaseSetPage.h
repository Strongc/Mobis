#pragma once
#include"resource.h"
#include"MobisDlg.h"
// sheet_DatabaseSetPage dialog

class sheet_DatabaseSetPage : public CPropertyPage
{
	DECLARE_DYNAMIC(sheet_DatabaseSetPage)

public:
	sheet_DatabaseSetPage();
	virtual ~sheet_DatabaseSetPage();

	// Dialog Data
	enum { IDD = IDD_Database_set };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()



public:
	int getData(CMobisDlg*pMaindata);
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	int m_PicType;
	int m_SaveDays;
	CMobisDlg* m_pMaindata;
	CString m_dataPath;
	afx_msg void OnBnClickedChosepath();
};
