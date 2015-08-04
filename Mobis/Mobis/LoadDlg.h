#pragma once



class LoadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoadDlg)

public:
	LoadDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~LoadDlg();

	// Dialog Data
	enum { IDD = IDD_LOAD_Dlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();
public:
	void dump_com_error(_com_error &e);
	void OnOK();
	void OnDestroy();
	bool checkPassword();

public:
	 
	_ConnectionPtr	m_pConnection;
	_RecordsetPtr	m_pRecordset;

	CString m_name;
	CString m_passsword;

	SHELLEXECUTEINFO sec;
};
