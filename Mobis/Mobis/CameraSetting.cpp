// CameraSetting.cpp : implementation file
//

#include "stdafx.h"
#include "Mobis.h"
#include "CameraSetting.h"
#include "afxdialogex.h"


// CameraSetting dialog

IMPLEMENT_DYNAMIC(CameraSetting, CDialogEx)

	CameraSetting::CameraSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CameraSetting::IDD, pParent)
	, m_Edit(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CameraSetting::~CameraSetting()
{
}

void CameraSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_MSComm);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
}


BEGIN_MESSAGE_MAP(CameraSetting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CameraSetting::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_BUTTON2, &CameraSetting::OnBnClickedButton2)
END_MESSAGE_MAP()


// CameraSetting message handlers
BEGIN_EVENTSINK_MAP(CameraSetting, CDialogEx)
	ON_EVENT(CameraSetting, IDC_MSCOMM1, 1, CameraSetting::OnCommMscomm, VTS_NONE)

END_EVENTSINK_MAP()


void CameraSetting::OnCommMscomm()
{
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	long len,i;
	byte rxdata[MAX_BUFFER_SIZE]={0}; //���� BYTE ����
	CString strtemp;
	strtemp.Empty();

	UpdateData(true); //��ȡ�༭������

	if(m_MSComm.get_CommEvent()==2) //ֵΪ 2 ��ʾ���ջ����������ַ�
	{
		variant_inp=m_MSComm.get_Input(); //����������Ϣ
		safearray_inp=variant_inp; ///����ת��
		len=safearray_inp.GetOneDimSize(); //�õ���Ч�����ݳ���
		for(i=0; i<len; i++)
		{
			safearray_inp.GetElement(&i, rxdata+i);
			//�������
		}
		for(i=0; i<len; i++) //������ת��Ϊ CString �ͱ���
		{
			strtemp.Format(_T("%c"), *(rxdata+i));
			//����ת��
			m_Edit2+=strtemp;
			//���½��ܻ�����
		}

		//UpdateData(FALSE); //���±༭������
	}

	UpdateData(FALSE); //���±༭������

}

void CameraSetting::OnBnClickedOpen()
{

	CString str;
	str.Empty();

	if(m_MSComm.get_PortOpen()) //��������Ǵ򿪵ģ����йرմ���
	{
		m_MSComm.put_PortOpen(FALSE);
	}
	int com_number=1;
	//com_number = m_ComChoose.GetCurSel()+1;
	m_MSComm.put_CommPort(com_number); //ѡ��COM
	m_MSComm.put_InBufferSize(MAX_BUFFER_SIZE); //���ջ�����
	m_MSComm.put_OutBufferSize(MAX_BUFFER_SIZE);//���ͻ�����
	m_MSComm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ
	m_MSComm.put_InputMode(1);//�Զ����Ʒ�ʽ��д����
	m_MSComm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm�¼�
	m_MSComm.put_Settings(_T("9600,n,8,1"));//������115200�޼���λ��8������λ��1��ֹͣλ
	if(!m_MSComm.get_PortOpen())//�������û�д����
	{
		m_MSComm.put_PortOpen(TRUE);//�򿪴���
		str.Format(_T("����%d�򿪳ɹ�"), com_number);
		AfxMessageBox(str);
	}
	else
	{
		m_MSComm.put_OutBufferCount(0);
		str.Format(_T("����%d��ʧ��"), com_number);
		AfxMessageBox(str);
	}
}

void CameraSetting::OnBnClickedButton2()
{
	CByteArray HexDataBuf;

	UpdateData(TRUE);
	//��ȡ�༭������
	if(m_Edit.IsEmpty())
	{
		AfxMessageBox(_T("��������Ϊ��!"));
		return;
	}
	HexDataBuf.RemoveAll();               //������� 

	int GetLen = m_Edit.GetLength();

	//���ַ���ת��Ϊ�ֽ�����

	HexDataBuf.SetSize(GetLen);            //���������СΪ֡���� 
	for(int i=0; i<GetLen; i++)
	{
		HexDataBuf.SetAt(i,m_Edit[i]);
	}
	m_MSComm.put_Output(COleVariant(HexDataBuf)); //����ʮ����������

	UpdateData(false); //���±༭������
}
