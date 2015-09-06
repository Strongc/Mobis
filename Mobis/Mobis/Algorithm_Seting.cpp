// Algorithm_Seting.cpp : implementation file
//

#include "stdafx.h"
#include "Mobis.h"
#include "Algorithm_Seting.h"
#include "afxdialogex.h"


// Algorithm_Seting dialog

IMPLEMENT_DYNAMIC(Algorithm_Seting, CDialogEx)

	Algorithm_Seting::Algorithm_Seting(CWnd* pParent /*=NULL*/)
	: CDialogEx(Algorithm_Seting::IDD, pParent)
	, m_Algorithm_param1(0)
{

}

Algorithm_Seting::~Algorithm_Seting()
{
}

void Algorithm_Seting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Algorithm_param1, m_Algorithm_param1);
}

BOOL Algorithm_Seting::OnInitDialog()
{
	//m_Algorithm_param1=::GetPrivateProfileInt("数据保存设置","图像格式",0,".//setting.ini");
	CString str;
	::GetPrivateProfileStringA("算法参数设置","算法参数1",".//data",str.GetBuffer(MAX_PATH),MAX_PATH,".//setting.ini");
	m_Algorithm_param1 = _ttof(str);

	UpdateData(false);
	return 1;
}

BEGIN_MESSAGE_MAP(Algorithm_Seting, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &Algorithm_Seting::OnDeltaposSpin1)
	ON_EN_CHANGE(IDC_EDIT_Algorithm_param1, &Algorithm_Seting::OnChangeEditAlgorithmParam1)
	ON_BN_CLICKED(IDOK, &Algorithm_Seting::OnBnClickedOk)
END_MESSAGE_MAP()


// Algorithm_Seting message handlers


void Algorithm_Seting::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	//@TN
	//	*pResult = 0;
	//// TODO: Add your control notification handler code here
	//*pResult = 0;


	UpdateData(true);
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(pNMUpDown-> iDelta == 1) // 如果此值为1 , 说明点击了Spin的往下箭头 
	{  
		//增加编辑框中的数字值 
		m_Algorithm_param1-=0.01;
	} 
	else if(pNMUpDown-> iDelta == -1) // 如果此值为-1 , 说明点击了Spin的往上箭头 
	{ 
		//减少编辑框中的数字值 
		m_Algorithm_param1+=0.01;
	}

	UpdateData(false);
	*pResult = 0;
}


void Algorithm_Seting::OnChangeEditAlgorithmParam1()
{
	UpdateData(true);
}


void Algorithm_Seting::OnBnClickedOk()
{
	CString str;
	str.Format("%f",m_Algorithm_param1);
	::WritePrivateProfileString("算法参数设置","算法参数1",str,".//setting.ini");
	CDialogEx::OnOK();
}
