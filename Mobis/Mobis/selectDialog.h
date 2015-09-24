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
	//picture控件及变量
	vector<LeoPicture_For_SelectDlg>m_zoomPics;
	vector<Mat> workPool_imgs;


	//组合框控件
	CComboBox m_list_xinghao;
	vector<ModelManage>*xinghaos; 
	int m_pos;
	//某型号所需数据
	CString m_curren_name;
	int m_current_num;
	CListCtrl m_listctr;
	ModelManage current_xh;

	BOOL m_isCameraLock;



public:
	afx_msg void OnSelchangeCombo1();		//选择某	型号					
	afx_msg void OnBnClickedAddnew();		//增加一个新型号	
	afx_msg void OnBnClickedDeletecurrent();//删除当前型号


	afx_msg void OnBnClickedBtAddPosition();					//增加检测位置
	afx_msg void OnBnClickedBtDeletePosition();					//删除某检测位置
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);//编辑检测位置 的检测区域，及检测模板
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);	//查看检测位置	

	afx_msg void OnChangeEditXhName();		//编辑型号名称
	afx_msg void OnBnClickedSave();			//保存当前型号  
	afx_msg void OnBnClickedOk();			//退出编辑

	afx_msg void OnClickedCheckLock();		//图像锁定，相机不更新
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	void myUpdata(bool direct=true); //更新型号列表框、更新型号名称及螺钉数量编辑框、更新模型列表框
	LRESULT camera_buf_ready(WPARAM wParam, LPARAM lParam);

};
