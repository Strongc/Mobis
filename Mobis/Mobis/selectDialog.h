#pragma once
#include "afxwin.h"
#include "opencv.hpp"
#include "CvvImage.h"
#include "LeoPicture_For_SelectDlg.h"
#include "Model.h"
#include "afxcmn.h"



class selectDialog : public CDialogEx
{
	DECLARE_DYNAMIC(selectDialog)

public:
	selectDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~selectDialog();

	// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	//picture�ؼ�������
	vector<LeoPicture_For_SelectDlg>m_zoomPics;
	vector<Mat> workPool_imgs;


	//��Ͽ�ؼ�
	CComboBox m_list_xinghao;
	vector<ModelManage>*xinghaos; 
	int m_pos;
	//ĳ�ͺ���������
	CString m_curren_name;
	int m_current_num;
	CListCtrl m_listctr;
	ModelManage current_xh;

	BOOL m_isCameraLock;



public:
	afx_msg void OnSelchangeCombo1();		//ѡ��ĳ	�ͺ�					
	afx_msg void OnBnClickedAddnew();		//����һ�����ͺ�	
	afx_msg void OnBnClickedDeletecurrent();//ɾ����ǰ�ͺ�


	afx_msg void OnBnClickedBtAddPosition();					//���Ӽ��λ��
	afx_msg void OnBnClickedBtDeletePosition();					//ɾ��ĳ���λ��
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);//�༭���λ�� �ļ�����򣬼����ģ��
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);	//�鿴���λ��	

	afx_msg void OnChangeEditXhName();		//�༭�ͺ�����
	afx_msg void OnBnClickedSave();			//���浱ǰ�ͺ�  
	afx_msg void OnBnClickedOk();			//�˳��༭

	afx_msg void OnClickedCheckLock();		//ͼ�����������������
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	void myUpdata(bool direct=true); //�����ͺ��б�򡢸����ͺ����Ƽ��ݶ������༭�򡢸���ģ���б��
	LRESULT camera_buf_ready(WPARAM wParam, LPARAM lParam);

};
