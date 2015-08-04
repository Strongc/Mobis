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
		dump_com_error(e);
		return FALSE;
	}

	//��ʼ��listctl�ؼ�
	m_list_password.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	LONG lStyle;
	lStyle = GetWindowLong(m_list_password.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_list_password.m_hWnd, GWL_STYLE, lStyle);//����style

	m_list_password.DeleteAllItems();//���
	m_list_password.InsertColumn(0,_T("�˺�"));//�����
	m_list_password.InsertColumn(1,_T("����"));
	m_list_password.SetColumnWidth(0, 100);//�����п�
	m_list_password.SetColumnWidth(1, 100);
	m_list_password.SetRedraw(FALSE);//��ֹ�ػ�

	exchangDatabase(false);

	return true;
}

//��ӡ����ADO�ؼ�ʱ��������ϸ������Ϣ
void LoadManage::dump_com_error(_com_error &e)
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

void LoadManage::exchangDatabase(bool direct)
{
	m_list_password.DeleteAllItems();
	openRecordset();
	_variant_t var;
	CString strName,strpassword;
	try
	{		// ������и��ֶβ������б����
		int i=0;
		while(!m_pRecordset->adoEOF)
		{
			var = m_pRecordset->GetCollect("name");
			if(var.vt != VT_NULL)
				strName = (LPCSTR)_bstr_t(var);
			var = m_pRecordset->GetCollect("password");
			if(var.vt != VT_NULL)
				strpassword = (LPCSTR)_bstr_t(var);
			//�����б�ؼ�
			m_list_password.InsertItem(i,strName);
			m_list_password.SetItemText(i,1,strpassword);
			i++;
			m_pRecordset->MoveNext();
		}
		m_list_password.SetRedraw(TRUE);
		// Ĭ���б�ָ���һ�ͬʱ�ƶ���¼ָ�벢��ʾ
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
			// ����ɾ���ڶ�����¼
			m_pRecordset->MoveFirst();
			m_pRecordset->Move(nItem);        // ��0��ʼ
			m_pRecordset->Delete(adAffectCurrent);  // ����adAffectCurrentΪɾ����ǰ��¼
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
		MessageBoxA("�˺ź����벻��Ϊ��");
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
	// ʹ��ADO�������ݿ��¼��
	m_pRecordset.CreateInstance(__uuidof(Recordset));
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
	}
}

void LoadManage::closeRecordset()
{
	m_pRecordset->Close();
	m_pRecordset = NULL;
}

void LoadManage::OnDestroy()  
{
	// �ر�ADO����״̬
	if(m_pConnection->State)
		m_pConnection->Close();
	m_pConnection= NULL;
	CDialogEx::OnDestroy();
}