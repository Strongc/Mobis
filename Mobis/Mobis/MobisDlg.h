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

	//�����ͼ�ؼ�������
	vector<LeoPicture_For_Main>m_zoomPics;
	vector<Mat> workPool_imgs;

	//����ͼ��״̬����Ŀؼ���ͼ�����
	CStatic m_pics[20];
	CStatic m_status[20];
	Mat m_pass;
	Mat m_ng;
	Mat m_no;

	//��Ͽ�ؼ�������Ҫ����ĵƾ��ͺű���
	CComboBox m_list_all;
	int m_pos;
	vector<ModelManage>AllXingHaos; 
	ModelManage CurrentXinghao;

	//�߳�ʹ��	
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

	cameraManage m_cameraManage;//����������
	PictureSave  m_DataSave;//���ݱ���������
	vector<myAlgorithm_ncc::myresult> m_result;//���


	afx_msg void OnBnClickedBuildmodel(); //ģ�����ť
	afx_msg void OnBnClickedBtZhaohao();  //�˺Ź���ť
	afx_msg void OnBnClickedBegincheck(); //����ݶ����޺���
	afx_msg void OnBnClickedCameraSetting(); //��� ��Դ  ���ݱ��������
	afx_msg void OnSelchangeList();		  //ѡ�����ģ��	
	afx_msg void OnBnClickedAlgorithmSetting();  //�����㷨������ť

	afx_msg LRESULT camera_buf_ready(WPARAM wParam, LPARAM lParam);

	void readFlie();  //��files->AllXingHaos    
	void writeFlie(); //��AllXingHaos->files
	void myUpdata(bool direct); //��AllXingHaos���� ���µ� �б��
	void savePic(vector<cv::Mat> imgs);//����ͼ��
	void LeoShowImage(cv::Mat& image,int IDC);//��ͼ����ʾ��ĳID�Ŀؼ���
	
	static unsigned __stdcall FindCameraThread(void*params);
	static unsigned __stdcall AcqAndShowThread(void*params);
	static unsigned __stdcall CheckThread(void*params);




	//ʹ��������Ӧ��Ļ��С////////////////////////////////
	CRect  m_rect;//����Ի����ʼ��С
	vector<int> ctl_IDs;
	vector<CRect> ctl_Rects;
	void getCtlRect(vector<int> &ctl_IDs,vector<CRect> &ctl_Rects);
	void ChangeSize(UINT nID, int x, int y);
	void OnSize(UINT nType, int cx, int cy);
	/////////////////////////////////////////////////////


	//һЩ���԰�ť////////////////////////////////////////////
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
