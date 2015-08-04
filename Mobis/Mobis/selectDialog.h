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
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtAddPosition();					//���Ӽ��λ��
	afx_msg void OnBnClickedBtDeletePosition();					//ɾ��ĳ���λ��
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);//�༭���λ�� �ļ�����򣬼����ģ��
	afx_msg void OnSelchangeCombo1();		//ѡ��ĳ	�ͺ�					
	afx_msg void OnBnClickedAddnew();		//����һ�����ͺ�	
	afx_msg void OnBnClickedDeletecurrent();//ɾ����ǰ�ͺ�
	afx_msg void OnChangeEditXhName();		//�༭�ͺ�����
	afx_msg void OnBnClickedSave();			//���浱ǰ�ͺ�  
	afx_msg void OnBnClickedOk();
	void myUpdata(bool direct=true); //�����ͺ��б�򡢸����ͺ����Ƽ��ݶ������༭�򡢸���ģ���б��
	LRESULT camera_buf_ready(WPARAM wParam, LPARAM lParam);
	//picture�ؼ�
	LeoPicture_For_SelectDlg m_zoomCtrl;
	Mat workPool_img;

	LeoPicture_For_SelectDlg m_zoomCtrl2;
	Mat workPool_img2;
	//��Ͽ�ؼ�
	CComboBox m_list_xinghao;
	vector<ModelManage>*xinghaos; 
	int m_pos;
	//ĳ�ͺ���������
	CListCtrl m_listctr;
	CString m_curren_name;
	int m_current_num;
	ModelManage current_xh;
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);



};
