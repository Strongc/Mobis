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
			m_Edit_ReciveMessage+=strtemp;
			//���½��ܻ�����
		}

		//UpdateData(FALSE); //���±༭������
	}

	UpdateData(FALSE); //���±༭������
}
BEGIN_MESSAGE_MAP(sheet_LightSetPage, CPropertyPage)
	ON_BN_CLICKED(IDC_btn_SendMessage, &sheet_LightSetPage::OnBnClickedbtnSendmessage)
	ON_BN_CLICKED(IDC_CheckBtn, &sheet_LightSetPage::OnBnClickedOpencom)
END_MESSAGE_MAP()

void sheet_LightSetPage::OnBnClickedbtnSendmessage()
{
	CByteArray HexDataBuf;

	UpdateData(TRUE);
	//��ȡ�༭������
	if(m_Edit_SendMessage.IsEmpty())
	{
		AfxMessageBox(_T("��������Ϊ��!"));
		return;
	}
	HexDataBuf.RemoveAll();               //������� 

	int GetLen = m_Edit_SendMessage.GetLength();

	//���ַ���ת��Ϊ�ֽ�����

	HexDataBuf.SetSize(GetLen);            //���������СΪ֡���� 
	for(int i=0; i<GetLen; i++)
	{
		HexDataBuf.SetAt(i,m_Edit_SendMessage[i]);
	}
	m_MSComm.put_Output(COleVariant(HexDataBuf)); //����ʮ����������


	m_Edit_SendMessage.Empty();
	UpdateData(false); //���±༭������
}

void sheet_LightSetPage::OnBnClickedOpencom()
{
	UpdateData(TRUE);
	if(m_openComm_check)
	{
		m_openComm.SetWindowText("�رմ���");//��ʱ�Ѿ��򿪴���
		
		CString str;
		str.Empty();
		if(m_MSComm.get_PortOpen()) //��������Ǵ򿪵ģ����ȹرմ���
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
			//AfxMessageBox(str);
		}
		else
		{
			m_MSComm.put_OutBufferCount(0);
			str.Format(_T("����%d��ʧ��"), com_number);
			AfxMessageBox(str);
		}
	}
	else 
	{
		m_openComm.SetWindowText("�򿪴���");
		
		m_MSComm.put_PortOpen(FALSE);//�رմ���  
		
	}

}
