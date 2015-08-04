#include "stdafx.h"
#include "Mobis.h"
#include "LoadManage.h"
#include "afxdialogex.h"


IMPLEMENT_DYNAMIC(LoadManage, CDialogEx)

LoadManage::LoadManage(CWnd* pParent /*=NULL*/)
	: CDialogEx(LoadManage::IDD, pParent)
	, m_add_name(_T(""))
	, m_add_password(_T(""))
{

}

LoadManage::~LoadManage()
{
}

void LoadManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_password);
	DDX_Text(pDX, IDC_EDIT1, m_add_name);
	DDX_Text(pDX, IDC_EDIT2, m_add_password);
}


BEGIN_MESSAGE_MAP(LoadManage, CDialogEx)
	ON_BN_CLICKED(IDC_DELETE_ZHAOHAO, &LoadManage::OnBnClickedDeleteZhaohao)
	ON_BN_CLICKED(IDC_ADD_ZHAOHAO, &LoadManage::OnBnClickedAddZhaohao)
END_MESSAGE_MAP()


BOOL LoadManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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
		dump_com_error(e);
		return FALSE;
	}

	//初始化listctl控件
	m_list_password.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	LONG lStyle;
	lStyle = GetWindowLong(m_list_password.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list_password.m_hWnd, GWL_STYLE, lStyle);//设置style

	m_list_password.DeleteAllItems();//清空
	m_list_password.InsertColumn(0,_T("账号"));//添加列
	m_list_password.InsertColumn(1,_T("密码"));
	m_list_password.SetColumnWidth(0, 100);//设置列宽
	m_list_password.SetColumnWidth(1, 100);
	m_list_password.SetRedraw(FALSE);//防止重绘

	exchangDatabase(false);

	return true;
}

//打印调用ADO控件时产生的详细错误信息
void LoadManage::dump_com_error(_com_error &e)
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

void LoadManage::exchangDatabase(bool direct)
{
	m_list_password.DeleteAllItems();
	openRecordset();
	_variant_t var;
	CString strName,strpassword;
	try
	{		// 读入库中各字段并加入列表框中
		int i=0;
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("name");
			if(var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			var = m_pRecordset->GetCollect("password");
			if(var.vt != VT_NULL)
				strpassword = (LPCSTR)_bstr_t(var);
			//加入列表控件
			m_list_password.InsertItem(i,strName);
			m_list_password.SetItemText(i,1,strpassword);
			i++;
			m_pRecordset->MoveNext();
		}
		m_list_password.SetRedraw(TRUE);
		// 默认列表指向第一项，同时移动记录指针并显示
		//m_AccessList.SetCurSel(0);
	}
	catch(_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}

	closeRecordset();
}

void LoadManage::OnBnClickedDeleteZhaohao()
{
	openRecordset();
	POSITION pos = m_list_password.GetFirstSelectedItemPosition();  
	if (pos != NULL)  
	{
		int nItem = m_list_password.GetNextSelectedItem(pos);  
		try
		{
			// 假设删除第二条记录
			m_pRecordset->MoveFirst();
			m_pRecordset->Move(nItem);        // 从0开始
			m_pRecordset->Delete(adAffectCurrent);  // 参数adAffectCurrent为删除当前记录
			m_pRecordset->Update();
		}
		catch(_com_error *e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
	}
	closeRecordset();
	exchangDatabase(false);
}

void LoadManage::OnBnClickedAddZhaohao()
{
	UpdateData();
	if(m_add_name==_T("")||m_add_password==_T(""))
	{
		MessageBoxA("账号和密码不能为空");
		return;
	}
	openRecordset();
	m_pRecordset->AddNew();
	m_pRecordset->PutCollect("name",_variant_t(m_add_name));
	m_pRecordset->PutCollect("password",_variant_t(m_add_password));
	m_pRecordset->Update();
	closeRecordset();
	exchangDatabase(false);

	
}

void LoadManage::openRecordset()
{
	// 使用ADO创建数据库记录集
	m_pRecordset.CreateInstance(__uuidof(Recordset));
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
	}
}

void LoadManage::closeRecordset()
{
	m_pRecordset->Close();
	m_pRecordset = NULL;
}

void LoadManage::OnDestroy()  
{
	// 关闭ADO连接状态
	if(m_pConnection->State)
		m_pConnection->Close();
	m_pConnection= NULL;
	CDialogEx::OnDestroy();
}