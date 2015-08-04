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
	afx_msg void OnBnClickedBtAddPosition();					//增加检测位置
	afx_msg void OnBnClickedBtDeletePosition();					//删除某检测位置
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);//编辑检测位置 的检测区域，及检测模板
	afx_msg void OnSelchangeCombo1();		//选择某	型号					
	afx_msg void OnBnClickedAddnew();		//增加一个新型号	
	afx_msg void OnBnClickedDeletecurrent();//删除当前型号
	afx_msg void OnChangeEditXhName();		//编辑型号名称
	afx_msg void OnBnClickedSave();			//保存当前型号  
	afx_msg void OnBnClickedOk();
	void myUpdata(bool direct=true); //更新型号列表框、更新型号名称及螺钉数量编辑框、更新模型列表框
	LRESULT camera_buf_ready(WPARAM wParam, LPARAM lParam);
	//picture控件
	LeoPicture_For_SelectDlg m_zoomCtrl;
	Mat workPool_img;

	LeoPicture_For_SelectDlg m_zoomCtrl2;
	Mat workPool_img2;
	//组合框控件
	CComboBox m_list_xinghao;
	vector<ModelManage>*xinghaos; 
	int m_pos;
	//某型号所需数据
	CListCtrl m_listctr;
	CString m_curren_name;
	int m_current_num;
	ModelManage current_xh;
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);



};
