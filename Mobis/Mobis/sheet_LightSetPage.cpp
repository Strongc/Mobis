// sheet_LightSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "Mobis.h"
#include "sheet_LightSetPage.h"
#include "afxdialogex.h"

#define MAX_BUFFER_SIZE 1024
// sheet_LightSetPage dialog

IMPLEMENT_DYNAMIC(sheet_LightSetPage, CPropertyPage)

	sheet_LightSetPage::sheet_LightSetPage()
	: CPropertyPage(sheet_LightSetPage::IDD)
	, m_Edit_SendMessage(_T(""))
	, m_Edit_ReciveMessage(_T(""))
	, m_openComm_check(FALSE)
{

}

sheet_LightSetPage::~sheet_LightSetPage()
{
}

void sheet_LightSetPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM_LIGHT, m_MSComm);

	DDX_Text(pDX, IDC_EDIT_Send, m_Edit_SendMessage);
	DDX_Text(pDX, IDC_EDIT2, m_Edit_ReciveMessage);
	DDX_Control(pDX, IDC_CheckBtn, m_openComm);
	DDX_Check(pDX, IDC_CheckBtn, m_openComm_check);
}

int sheet_LightSetPage::getData(CMobisDlg*pMaindata)
{

	m_pMaindata  = pMaindata;
	return true;
}

BEGIN_EVENTSINK_MAP(sheet_LightSetPage, CPropertyPage)
	ON_EVENT(sheet_LightSetPage, IDC_MSCOMM_LIGHT, 1, sheet_LightSetPage::OnCommMscommLight, VTS_NONE)
END_EVENTSINK_MAP()


void sheet_LightSetPage::OnCommMscommLight()
{
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	long len,i;
	byte rxdata[MAX_BUFFER_SIZE]={0}; //设置 BYTE 数组
	CString strtemp;
	strtemp.Empty();

	UpdateData(true); //读取编辑框内容

	if(m_MSComm.get_CommEvent()==2) //值为 2 表示接收缓冲区内有字符
	{
		variant_inp=m_MSComm.get_Input(); //读缓冲区消息
		safearray_inp=variant_inp; ///变量转换
		len=safearray_inp.GetOneDimSize(); //得到有效的数据长度
		for(i=0; i<len; i++)
		{
			safearray_inp.GetElement(&i, rxdata+i);
			//获得数据
		}
		for(i=0; i<len; i++) //将数组转换为 CString 型变量
		{
			strtemp.Format(_T("%c"), *(rxdata+i));
			//数据转换
			m_Edit_ReciveMessage+=strtemp;
			//更新接受缓冲区
		}

		//UpdateData(FALSE); //更新编辑框内容
	}

	UpdateData(FALSE); //更新编辑框内容
}
BEGIN_MESSAGE_MAP(sheet_LightSetPage, CPropertyPage)
	ON_BN_CLICKED(IDC_btn_SendMessage, &sheet_LightSetPage::OnBnClickedbtnSendmessage)
	ON_BN_CLICKED(IDC_CheckBtn, &sheet_LightSetPage::OnBnClickedOpencom)
END_MESSAGE_MAP()

void sheet_LightSetPage::OnBnClickedbtnSendmessage()
{
	CByteArray HexDataBuf;

	UpdateData(TRUE);
	//获取编辑框内容
	if(m_Edit_SendMessage.IsEmpty())
	{
		AfxMessageBox(_T("发送数据为空!"));
		return;
	}
	HexDataBuf.RemoveAll();               //清空数组 

	int GetLen = m_Edit_SendMessage.GetLength();

	//将字符串转化为字节数据

	HexDataBuf.SetSize(GetLen);            //设置数组大小为帧长度 
	for(int i=0; i<GetLen; i++)
	{
		HexDataBuf.SetAt(i,m_Edit_SendMessage[i]);
	}
	m_MSComm.put_Output(COleVariant(HexDataBuf)); //发送十六进制数据


	m_Edit_SendMessage.Empty();
	UpdateData(false); //更新编辑框内容
}

void sheet_LightSetPage::OnBnClickedOpencom()
{
	UpdateData(TRUE);
	if(m_openComm_check)
	{
		m_openComm.SetWindowText("关闭串口");//此时已经打开串口
		
		CString str;
		str.Empty();
		if(m_MSComm.get_PortOpen()) //如果串口是打开的，则先关闭串口
		{
			m_MSComm.put_PortOpen(FALSE);
		}
		int com_number=1;
		//com_number = m_ComChoose.GetCurSel()+1;
		m_MSComm.put_CommPort(com_number); //选择COM
		m_MSComm.put_InBufferSize(MAX_BUFFER_SIZE); //接收缓冲区
		m_MSComm.put_OutBufferSize(MAX_BUFFER_SIZE);//发送缓冲区
		m_MSComm.put_InputLen(0);//设置当前接收区数据长度为0,表示全部读取
		m_MSComm.put_InputMode(1);//以二进制方式读写数据
		m_MSComm.put_RThreshold(1);//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm事件
		m_MSComm.put_Settings(_T("9600,n,8,1"));//波特率115200无检验位，8个数据位，1个停止位
		if(!m_MSComm.get_PortOpen())//如果串口没有打开则打开
		{
			m_MSComm.put_PortOpen(TRUE);//打开串口
			str.Format(_T("串口%d打开成功"), com_number);
			//AfxMessageBox(str);
		}
		else
		{
			m_MSComm.put_OutBufferCount(0);
			str.Format(_T("串口%d打开失败"), com_number);
			AfxMessageBox(str);
		}
	}
	else 
	{
		m_openComm.SetWindowText("打开串口");
		
		m_MSComm.put_PortOpen(FALSE);//关闭串口  
		
	}

}
