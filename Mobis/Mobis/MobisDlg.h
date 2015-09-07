#pragma once
#include "opencv.hpp"
#include "CvvImage.h"
#include "selectDialog.h"
#include "Model.h"
#include "LoadDlg.h"
#include "LoadManage.h"
#include "afxwin.h"
#include "algorithm.h"
#include"LeoPicture_For_Main.h"
#include"cameraManage.h"
#include"PictureSave.h"
using namespace cv;

class CMobisDlg : public CDialogEx
{
	// Construction
public:
	CMobisDlg(CWnd* pParent = NULL);	// standard constructor
	~CMobisDlg();
	// Dialog Data
	enum { IDD = IDD_MOBIS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	//整体大图控件及变量
	vector<LeoPicture_For_Main>m_zoomPics;
	vector<Mat> workPool_imgs;

	//区域图，状态结果的控件及图像变量
	CStatic m_pics[20];
	CStatic m_status[20];
	Mat m_pass;
	Mat m_ng;
	Mat m_no;

	//组合框控件及其需要处理的灯具型号变量
	CComboBox m_list_all;
	int m_pos;
	vector<ModelManage>AllXingHaos; 
	ModelManage CurrentXinghao;

	//线程使用	
	typedef struct point_and_camID_  
	{  
		void* Point;
		int camID;  
	}point_and_camID;
	vector<point_and_camID> point_and_camIDs;

	HANDLE m_hFindCamEvent;
	HANDLE m_hFindCamThread;

	HANDLE m_hAcqEvent;
	vector<HANDLE> m_hAcqThreads;

	HANDLE m_hCheckEvent;
	HANDLE m_hCheckThread;

	HANDLE m_hAppExit; 

	cameraManage m_cameraManage;//相机管理对象
	PictureSave  m_DataSave;//数据保存管理对象
	vector<myAlgorithm_ncc::myresult> m_result;//结果


	afx_msg void OnBnClickedBuildmodel(); //模板管理按钮
	afx_msg void OnBnClickedBtZhaohao();  //账号管理按钮
	afx_msg void OnBnClickedBegincheck(); //检测螺钉有无函数
	afx_msg void OnBnClickedCameraSetting(); //相机 光源  数据保存的配置
	afx_msg void OnSelchangeList();		  //选择检测的模板	
	afx_msg void OnBnClickedAlgorithmSetting();  //设置算法参数按钮

	afx_msg LRESULT camera_buf_ready(WPARAM wParam, LPARAM lParam);

	void readFlie();  //从files->AllXingHaos    
	void writeFlie(); //从AllXingHaos->files
	void myUpdata(bool direct); //将AllXingHaos变量 更新到 列表框
	void savePic(vector<cv::Mat> imgs);//保存图像
	void LeoShowImage(cv::Mat& image,int IDC);//将图像显示到某ID的控件上
	
	static unsigned __stdcall FindCameraThread(void*params);
	static unsigned __stdcall AcqAndShowThread(void*params);
	static unsigned __stdcall CheckThread(void*params);




	//使主窗口适应屏幕大小////////////////////////////////
	CRect  m_rect;//保存对话框初始大小
	vector<int> ctl_IDs;
	vector<CRect> ctl_Rects;
	void getCtlRect(vector<int> &ctl_IDs,vector<CRect> &ctl_Rects);
	void ChangeSize(UINT nID, int x, int y);
	void OnSize(UINT nType, int cx, int cy);
	/////////////////////////////////////////////////////


	//一些测试按钮////////////////////////////////////////////
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();    
	//afx_msg void OnBnClickedButton3();
	//afx_msg void OnBnClickedButton4();


	afx_msg void OnBnClickedstarttest();
	afx_msg void OnBnClickedstoptest();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	/////////////////////////////////////////////////////


	int getImages(vector<Mat> &images,DWORD timeOut=2000,int tryNum=3);

};
