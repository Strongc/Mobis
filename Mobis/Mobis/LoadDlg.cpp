

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

//打印调用ADO控件时产生的详细错误信息
void LoadDlg::dump_com_error(_com_error &e)
{
	CString ErrorStr;
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	ErrorStr.Format( "/n/tADO Error/n/tCode = %08lx/n/tCode meaning = %s/n/tSource = %s/n/tDescription = %s/n/n",
		e.Error(), e.ErrorMessage(), (LPCTSTR)bstrSource, (LPCTSTR)bstrDescription );
	//在调试窗口中打印错误信息,在Release版中可用DBGView查看错误信息
	::OutputDebugString((LPCTSTR)ErrorStr);
#ifdef _DEBUG
	AfxMessageBox(ErrorStr, MB_OK | MB_ICONERROR);
#endif	
}

BOOL LoadDlg::OnInitDialog()
{
	// 初始化COM,创建ADO连接等操作
	//if(AfxOleGetMessageFilter()   !=   NULL)
	//	AfxOleInit();

	m_pConnection.CreateInstance(__uuidof(Connection));
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 因为它有时会经常出现一些想不到的错误。jingzhou xu
	try                 
	{	
		// 打开本地Access库Demo.mdb
		m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Demo.mdb","","",adModeUnknown);
	}
	catch(_com_error& e)
	{
		//调用在CAdoRWAccessDlg中打印错误信息的静态函数
		LoadDlg::dump_com_error(e);
		return FALSE;
	}
	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	// 在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	// 因为它有时会经常出现一些想不到的错误。jingzhou xu
	try
	{
		m_pRecordset->Open("SELECT * FROM  test",                // 查询DemoTable表中所有字段
			m_pConnection.GetInterfacePtr(),						 // 获取库接库的IDispatch指针
			adOpenDynamic,
			adLockOptimistic,
			adCmdText);
	}
	catch(_com_error& e)
	{
		dump_com_error(e);
		return FALSE;
	}
	//打开屏幕键盘
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
		AfxMessageBox("验证失败!");
}

void LoadDlg::OnDestroy()  
{
	// 关闭ADO连接状态
	if(m_pConnection->State)
		m_pConnection->Close();
	m_pConnection= NULL;



	




	//关闭屏幕键盘///////////////////////////////////////////
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
			AfxMessageBox("表内数据为空");
			return false;
		}
		// 读入库中各字段并加入列表框中
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