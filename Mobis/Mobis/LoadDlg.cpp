

#include "stdafx.h"
#include "Mobis.h"
#include "LoadDlg.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(LoadDlg, CDialogEx)

	LoadDlg::LoadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(LoadDlg::IDD, pParent)
	, m_name(_T(""))
	, m_passsword(_T(""))
{

}

LoadDlg::~LoadDlg()
{

}

void LoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_PASSWORD, m_passsword);
}


BEGIN_MESSAGE_MAP(LoadDlg, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

//��ӡ����ADO�ؼ�ʱ��������ϸ������Ϣ
void LoadDlg::dump_com_error(_com_error &e)
{
	CString ErrorStr;
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	ErrorStr.Format( "/n/tADO Error/n/tCode = %08lx/n/tCode meaning = %s/n/tSource = %s/n/tDescription = %s/n/n",
		e.Error(), e.ErrorMessage(), (LPCTSTR)bstrSource, (LPCTSTR)bstrDescription );
	//�ڵ��Դ����д�ӡ������Ϣ,��Release���п���DBGView�鿴������Ϣ
	::OutputDebugString((LPCTSTR)ErrorStr);
#ifdef _DEBUG
	AfxMessageBox(ErrorStr, MB_OK | MB_ICONERROR);
#endif	
}

BOOL LoadDlg::OnInitDialog()
{
	// ��ʼ��COM,����ADO���ӵȲ���
	//if(AfxOleGetMessageFilter()   !=   NULL)
	//	AfxOleInit();

	m_pConnection.CreateInstance(__uuidof(Connection));
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// ��Ϊ����ʱ�ᾭ������һЩ�벻���Ĵ���jingzhou xu
	try                 
	{	
		// �򿪱���Access��Demo.mdb
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Demo.mdb","","",adModeUnknown);
	}
	catch(_com_error& e)
	{
		//������CAdoRWAccessDlg�д�ӡ������Ϣ�ľ�̬����
		LoadDlg::dump_com_error(e);
		return FALSE;
	}
	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	// ��Ϊ����ʱ�ᾭ������һЩ�벻���Ĵ���jingzhou xu
	try
	{
		m_pRecordset->Open("SELECT * FROM  test",                // ��ѯDemoTable���������ֶ�
			m_pConnection.GetInterfacePtr(),						 // ��ȡ��ӿ��IDispatchָ��
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error& e)
	{
		dump_com_error(e);
		return FALSE;
	}
	//����Ļ����
	//////////////////////////////////////////////////////
	PVOID OldValue;
	BOOL bRet = Wow64DisableWow64FsRedirection (&OldValue);

	memset(&sec, 0, sizeof(SHELLEXECUTEINFO));
	sec.cbSize = sizeof(SHELLEXECUTEINFO);
	sec.lpVerb = _T("open");
	sec.lpFile = _T("osk.exe");
	sec.fMask = SEE_MASK_NOCLOSEPROCESS;
	sec.nShow = SW_SHOW;
	sec.lpDirectory =_T("");
	ShellExecuteEx(&sec);

	if (bRet) 
	{ 
		Wow64RevertWow64FsRedirection(OldValue); 
	}
	/////////////////////////////////////////////////////
	return true;
}

void LoadDlg::OnOK()
{
	if(checkPassword())
	{
		CDialogEx::OnOK();
	}
	else
		AfxMessageBox("��֤ʧ��!");
}

void LoadDlg::OnDestroy()  
{
	// �ر�ADO����״̬
	if(m_pConnection->State)
		m_pConnection->Close();
	m_pConnection= NULL;



	




	//�ر���Ļ����///////////////////////////////////////////
	PVOID OldValue;
	BOOL bRet = Wow64DisableWow64FsRedirection (&OldValue);
	TerminateProcess(sec.hProcess, 1);
	if (bRet) 
	{ 
		Wow64RevertWow64FsRedirection(OldValue); 
	}
	
	////////////////////////////////////////////////////////
	CDialogEx::OnDestroy();
}

bool LoadDlg::checkPassword()
{
	UpdateData();
	_variant_t var;
	CString strName,strpassword;
	try
	{
		if(!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
		else
		{
			AfxMessageBox("��������Ϊ��");
			return false;
		}
		// ������и��ֶβ������б����
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("name");
			if(var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			var = m_pRecordset->GetCollect("password");
			if(var.vt != VT_NULL)
				strpassword = (LPCSTR)_bstr_t(var);
			//m_AccessList.AddString( strName + " --> "+strAge );
			m_pRecordset->MoveNext();

			if(strName==m_name&&strpassword==m_passsword)
				return true;
		}
		return false;

	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
	return true;
}