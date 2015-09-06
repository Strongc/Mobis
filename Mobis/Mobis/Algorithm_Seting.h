#pragma once


// Algorithm_Seting dialog

class Algorithm_Seting : public CDialogEx
{
	DECLARE_DYNAMIC(Algorithm_Seting)

public:
	Algorithm_Seting(CWnd* pParent = NULL);   // standard constructor
	virtual ~Algorithm_Seting();

// Dialog Data
	enum { IDD = IDD_ALGORITHM_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	double m_Algorithm_param1;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeEditAlgorithmParam1();
	afx_msg void OnBnClickedOk();
};
