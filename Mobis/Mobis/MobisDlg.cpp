#include "stdafx.h"
#include <vld.h>
#include "Mobis.h"
#include "MobisDlg.h"
#include "types.h"
#include "selectDialog.h"
#include"sheet_Seting.h"
#include<fstream> 
#include "afxdialogex.h"
#include"Algorithm_Seting.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMobisDlg dialog
CMobisDlg::CMobisDlg(CWnd* pParent /*=NULL*/): CDialogEx(CMobisDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_CHECK);


	int ctrNum=2;
	m_zoomPics.resize(ctrNum);
	workPool_imgs.resize(ctrNum);

}

void CMobisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_list, m_list_all);
	//for (int i = 0; i < m_zoomPics.size(); i++)
	//{
	//	DDX_Control(pDX, IDC_IMG+i,m_zoomPics[i]);  //这种做法限制比较大  所以图像显都示控件的ID如IDC_IMG，必须连续增加。
	//}
	DDX_Control(pDX, IDC_IMG,m_zoomPics[0]);
	DDX_Control(pDX, IDC_IMG2,m_zoomPics[1]);


	DDX_Control(pDX, IDC_PIC1, m_pics[0]);
	DDX_Control(pDX, IDC_PIC2, m_pics[1]);
	DDX_Control(pDX, IDC_PIC3, m_pics[2]);
	DDX_Control(pDX, IDC_PIC4, m_pics[3]);
	DDX_Control(pDX, IDC_PIC5, m_pics[4]);
	DDX_Control(pDX, IDC_PIC6, m_pics[5]);
	DDX_Control(pDX, IDC_PIC7, m_pics[6]);
	DDX_Control(pDX, IDC_PIC8, m_pics[7]);
	DDX_Control(pDX, IDC_PIC9, m_pics[8]);
	DDX_Control(pDX, IDC_PIC10, m_pics[9]);
	DDX_Control(pDX, IDC_PIC11, m_pics[10]);
	DDX_Control(pDX, IDC_PIC12, m_pics[11]);
	DDX_Control(pDX, IDC_PIC13, m_pics[12]);
	DDX_Control(pDX, IDC_PIC14, m_pics[13]);
	DDX_Control(pDX, IDC_PIC15, m_pics[14]);
	DDX_Control(pDX, IDC_PIC16, m_pics[15]);
	DDX_Control(pDX, IDC_PIC17, m_pics[16]);
	DDX_Control(pDX, IDC_PIC18, m_pics[17]);
	DDX_Control(pDX, IDC_PIC19, m_pics[18]);
	DDX_Control(pDX, IDC_PIC20, m_pics[19]);


	DDX_Control(pDX, IDC_status1, m_status[0]);
	DDX_Control(pDX, IDC_status2, m_status[1]);
	DDX_Control(pDX, IDC_status3, m_status[2]);
	DDX_Control(pDX, IDC_status4, m_status[3]);
	DDX_Control(pDX, IDC_status5, m_status[4]);
	DDX_Control(pDX, IDC_status6, m_status[5]);
	DDX_Control(pDX, IDC_status7, m_status[6]);
	DDX_Control(pDX, IDC_status8, m_status[7]);
	DDX_Control(pDX, IDC_status9, m_status[8]);
	DDX_Control(pDX, IDC_status10, m_status[9]);
	DDX_Control(pDX, IDC_status11, m_status[10]);
	DDX_Control(pDX, IDC_status12, m_status[11]);
	DDX_Control(pDX, IDC_status13, m_status[12]);
	DDX_Control(pDX, IDC_status14, m_status[13]);
	DDX_Control(pDX, IDC_status15, m_status[14]);
	DDX_Control(pDX, IDC_status16, m_status[15]);
	DDX_Control(pDX, IDC_status17, m_status[16]);
	DDX_Control(pDX, IDC_status18, m_status[17]);
	DDX_Control(pDX, IDC_status19, m_status[18]);
	DDX_Control(pDX, IDC_status20, m_status[19]);

}

BEGIN_MESSAGE_MAP(CMobisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUILDMODEL, &CMobisDlg::OnBnClickedBuildmodel)
	ON_BN_CLICKED(IDC_BT_ZHAOHAO, &CMobisDlg::OnBnClickedBtZhaohao)
	ON_BN_CLICKED(IDC_CAMERA_SETTING, &CMobisDlg::OnBnClickedCameraSetting)
	ON_BN_CLICKED(IDC_BeginCheck, &CMobisDlg::OnBnClickedBegincheck)
	ON_CBN_SELCHANGE(IDC_list, &CMobisDlg::OnSelchangeList)
	ON_MESSAGE(WM_DATA_READY,camera_buf_ready) 
	ON_BN_CLICKED(IDC_BUTTON1, &CMobisDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMobisDlg::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON3, &CMobisDlg::OnBnClickedButton3)
	//ON_BN_CLICKED(IDC_BUTTON4, &CMobisDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_starttest, &CMobisDlg::OnBnClickedstarttest)
	ON_BN_CLICKED(IDC_stoptest, &CMobisDlg::OnBnClickedstoptest)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_Algorithm_SETTING, &CMobisDlg::OnBnClickedAlgorithmSetting)
END_MESSAGE_MAP()

// CMobisDlg message handlers
BOOL CMobisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	GetClientRect(&m_rect);  //获取对话框的大小
	int id[]={IDC_STATIC_admin,IDC_IMG,IDC_IMG2,IDC_BT_ZHAOHAO,IDC_BUILDMODEL,IDC_CAMERA_SETTING,IDC_Algorithm_SETTING,IDC_STATIC_checkNum,IDC_list,
		IDC_STATIC_1,IDC_STATIC_2,IDC_STATIC_3,IDC_STATIC_4,IDC_STATIC_5,IDC_STATIC_6,IDC_STATIC_7,IDC_STATIC_8,IDC_STATIC_9,IDC_STATIC_10,
		IDC_STATIC_11,IDC_STATIC_12,IDC_STATIC_13,IDC_STATIC_14,IDC_STATIC_15,IDC_STATIC_16,IDC_STATIC_17,IDC_STATIC_18,IDC_STATIC_19,IDC_STATIC_20,
		IDC_status1,IDC_status2,IDC_status3,IDC_status4,IDC_status5,IDC_status6,IDC_status7,IDC_status8,IDC_status9,IDC_status10,
		IDC_status11,	IDC_status12,IDC_status13,IDC_status14,IDC_status15,IDC_status16,IDC_status17,IDC_status18,IDC_status19,IDC_status20,
		IDC_PIC1,IDC_PIC2,IDC_PIC3,IDC_PIC4,IDC_PIC5,IDC_PIC6,IDC_PIC7,IDC_PIC8,IDC_PIC9,IDC_PIC10,
		IDC_PIC11,IDC_PIC12,IDC_PIC13,IDC_PIC14,IDC_PIC15,IDC_PIC16,IDC_PIC17,IDC_PIC18,IDC_PIC19,IDC_PIC20,
		IDC_BeginCheck,IDC_STATIC_cam1,IDC_STATIC_cam2
	};
	ctl_IDs.assign(id,id+sizeof(id)/sizeof(int));
	getCtlRect(ctl_IDs,ctl_Rects);



	//初始化PictureControl控件///////////////////////
	for (int i = 0; i < m_zoomPics.size(); i++)
	{
		m_zoomPics[i].ID = i;
		m_zoomPics[i].UpdateImage(workPool_imgs[i]);  
	}


	//从文件读型号信息，并赋予PictureControl控件///////////
	readFlie();
	if(AllXingHaos.size()>0)
	{
		m_pos= 0;
		CurrentXinghao = AllXingHaos[m_pos];
		for (int i = 0; i < m_zoomPics.size(); i++)
		{
			m_zoomPics[i].p_ModelManage = &CurrentXinghao;
		}
	}
	else 
	{
		m_pos= -1;
	}
	//初始化所需图片////////////////////////////////
	m_pass = imread("pass.bmp");
	m_ng = imread("ng.bmp");
	m_no = imread("no.bmp");

	//初始化型号列表控件////////////////////////////
	myUpdata(false);

	//初始化相机///////////////////////////////////
	//m_cameraManage.findCamera();
	if(m_cameraManage.m_cameraIDList.size()<1)
	{
		m_hFindCamThread = (HANDLE)_beginthreadex(NULL,0,FindCameraThread,this,0,NULL);
	}
	else
		m_cameraManage.allocationCameraConnect();




	//初始化全局变量///////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < g_CamNum; i++)
	{
		InitializeCriticalSection(&g_CamBufs[i]); 
		g_CamAcqs[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
	}
	//初始化全局变量 ---按下check按钮，得到最新图像所需同步的变量///////////////////////////////////////
	for (int i = 0; i < g_CamNum; i++)
	{
		g_ReadyChecks[i] = CreateEvent( NULL, TRUE, FALSE, NULL );
	}

	//初始化采集线程////////////////////////////////////////////////////////////////////////////////////
	point_and_camIDs.resize(g_CamNum);
	for (int i = 0; i < g_CamNum; i++)
	{
		point_and_camIDs[i].camID=i;
		point_and_camIDs[i].Point=this;
		m_hAcqThread = (HANDLE)_beginthreadex(NULL,0,AcqAndShowThread,&point_and_camIDs[i],0,NULL);
	}
	//初始化检测线程////////////////////////////////////////////////////////////////////////////////////
	m_hCheckEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	m_hCheckThread = (HANDLE)_beginthreadex(NULL,0,CheckThread,this,0,NULL);
	//////////////////////////////////////////////////////////////////////////////////////////////////
	return TRUE; 
}

void CMobisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CMobisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMobisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMobisDlg::OnBnClickedBuildmodel()
{
	LoadDlg  Logon;
	if(Logon.DoModal()== IDOK)
	{
		selectDialog dlg;
		dlg.xinghaos = &AllXingHaos;
		for (int i = 0; i < workPool_imgs.size(); i++)
		{
			dlg.workPool_imgs[i] = workPool_imgs[i];
		}
		dlg.m_pos = m_pos;
		dlg.DoModal();



		writeFlie();
		if(dlg.m_pos>0&&dlg.m_pos<AllXingHaos.size())  //更新选择的灯的型号，当然要保证在合理范围内
			m_pos = dlg.m_pos;
		CurrentXinghao = AllXingHaos[m_pos];
		for (int i = 0; i < m_zoomPics.size(); i++)
		{
			m_zoomPics[i].p_ModelManage = &CurrentXinghao;
		}
		myUpdata(false);
	}
}

void CMobisDlg::OnBnClickedBtZhaohao()
{
	LoadDlg Logon;
	if(Logon.DoModal()== IDOK)
	{
		LoadManage LogonManage;
		LogonManage.DoModal();
	}


}

void CMobisDlg::OnSelchangeList()
{
	// TODO: Add your control notification handler code here	int pos = m_list_xinghao.GetCurSel();
	int pos = m_list_all.GetCurSel();
	m_pos = pos;
	if(m_pos>=0 &&m_pos<AllXingHaos.size())
	{
		CurrentXinghao = AllXingHaos[m_pos];
		for (int i = 0; i < m_zoomPics.size(); i++)
		{
			m_zoomPics[i].p_ModelManage = &CurrentXinghao;
		}
		/*m_zoomPic.p_ModelManage = &CurrentXinghao;
		m_zoomPic.Invalidate();

		m_zoomPic2.p_ModelManage = &CurrentXinghao;
		m_zoomPic2.Invalidate();*/
	}
	myUpdata(false);
}

void CMobisDlg::OnBnClickedCameraSetting()
{

	sheet_Seting  SettingDlg(this);
	SettingDlg.DoModal();

}

void CMobisDlg::OnBnClickedAlgorithmSetting()
{
	Algorithm_Seting  Algorithm_SetingDlg;
	Algorithm_SetingDlg.DoModal();;
}


void CMobisDlg::OnBnClickedBegincheck()
{
	SetEvent(m_hCheckEvent);
	//m_hCheckThread = (HANDLE)_beginthreadex(NULL,0,CheckThread,this,0,NULL);
	return ;
}

unsigned CMobisDlg:: CheckThread(void*params)
{
	CMobisDlg* pCMobisDlg = (CMobisDlg*)params;

	while (WaitForSingleObject(pCMobisDlg->m_hCheckEvent,INFINITE)==WAIT_OBJECT_0)
	{
		//获取图像///////////////////////////////////////////////////////////////////////////////
		vector<Mat>images; 
		pCMobisDlg->getImages(images);
		//int num = pCMobisDlg->m_cameraManage.m_cameraList.size();
		//if (num>0 )  //有相机
		//{
		//	if(pCMobisDlg->m_cameraManage.m_cameraList[0].m_TrigSetting==SoftWareTrig)
		//	{
		//		for (int i = 0; i < num; i++)
		//		{
		//			pCMobisDlg->m_cameraManage.m_cameraList[i].OnBnClickedSwtriggerbutton();
		//			ResetEvent(g_ReadyChecks[i]);     //同步
		//		}
		//	}
		//	else
		//	{
		//		for (int i = 0; i < num; i++)
		//		{
		//			ResetEvent(g_ReadyChecks[i]);     //同步
		//		}
		//	}


		//	for (int i = 0; i < num; i++)
		//	{
		//		if(WaitForSingleObject(g_ReadyChecks[i],INFINITE)==WAIT_OBJECT_0)
		//		{
		//			images.push_back(pCMobisDlg->workPool_imgs[i].clone());

		//		}
		//	}
		//}
		//else if(num==0)//无相机，检测指定图片
		//{
		//	for (int i = 0; i <pCMobisDlg->workPool_imgs.size(); i++)
		//	{
		//		images.push_back(pCMobisDlg->workPool_imgs[i].clone());
		//	}
		//}







		/////////////////////////////////////////////////////////////////////////////////////////
		//擦除检测区域图像
		for (int i = 0; i < 20; i++)
		{
			CDC *pdc = pCMobisDlg->m_pics[i].GetDC();
			pdc->SetStretchBltMode(STRETCH_HALFTONE);
			CRect myrect;
			pCMobisDlg->m_pics[i].GetClientRect(&myrect);
			HDC hDC=pdc->GetSafeHdc();	

			Mat roi = pCMobisDlg->m_no;
			//IplImage *img = &roi.operator IplImage();
			//IplImage tem = (IplImage)roi;
			IplImage *img = &(IplImage)roi;
			CvvImage iimg;			//创建一个CvvImage对象
			iimg.CopyOf(img);
			iimg.DrawToHDC(hDC,&myrect);
			pCMobisDlg->m_pics[i].ReleaseDC( pdc );
		}

		//显示检测区域图像
		int modelNum = pCMobisDlg->CurrentXinghao.m_Models.size();
		for (int i = 0; i < modelNum; i++)
		{
			//检测是否有图像存在////////////////////////////////
			Model c_model =pCMobisDlg->CurrentXinghao.m_Models[i];
			Mat image; 
			if(c_model.m_cameraID>pCMobisDlg->workPool_imgs.size())  //防止型号所需的CamId，在软件中不存在。防止下面数组越界
				continue;
			if(!pCMobisDlg->workPool_imgs[c_model.m_cameraID].empty()) //如果没有图像就不处理
				image = pCMobisDlg->workPool_imgs[c_model.m_cameraID];
			else 
				continue;
			//if(c_model.m_cameraID==0)
			//{
			//	if(!pCMobisDlg->workPool_img.empty())
			//		image = pCMobisDlg->workPool_img;
			//	else 
			//		continue;
			//}
			//else if(c_model.m_cameraID==1)
			//{
			//	if(!pCMobisDlg->workPool_img2.empty())
			//		image = pCMobisDlg->workPool_img2;
			//	else 
			//		continue;
			//}



			///////////////////////////////////////////////////

			CDC *pdc = pCMobisDlg->m_pics[i].GetDC();
			pdc->SetStretchBltMode(STRETCH_HALFTONE);
			CRect myrect;
			pCMobisDlg->m_pics[i].GetClientRect(&myrect);
			HDC hDC=pdc->GetSafeHdc();	


			Mat roi(image,pCMobisDlg->CurrentXinghao.m_Models[i].Search_rect);
			IplImage *img = &(IplImage)roi;

			CvvImage iimg;			//创建一个CvvImage对象
			iimg.CopyOf(img);
			iimg.DrawToHDC(hDC,&myrect);
			pCMobisDlg->m_pics[i].ReleaseDC( pdc );
		}




		////擦除显示结果
		for (int i = 0; i < 20; i++)
		{
			CDC *pdc = pCMobisDlg->m_status[i].GetDC();
			pdc->SetStretchBltMode(STRETCH_HALFTONE);
			CRect myrect;
			pCMobisDlg->m_status[i].GetClientRect(&myrect);
			HDC hDC=pdc->GetSafeHdc();	

			Mat roi = pCMobisDlg->m_no;
			IplImage *img = &(IplImage)roi;

			CvvImage iimg;			//创建一个CvvImage对象
			iimg.CopyOf(img);
			iimg.DrawToHDC(hDC,&myrect);
			pCMobisDlg->m_pics[i].ReleaseDC( pdc );
		}

		myAlgorithm_ncc cat(&pCMobisDlg->CurrentXinghao);
		if(!cat.templateMatching(images))
			AfxMessageBox("检测失败，检查模板是否建立完好");
		else
		{
			vector<int> result = cat.getValueResult();
			//输出检测结果
			for (int i = 0; i < result.size(); i++)
			{
				CDC *pdc = pCMobisDlg->m_status[i].GetDC();
				pdc->SetStretchBltMode(STRETCH_HALFTONE);
				CRect myrect;
				pCMobisDlg->m_status[i].GetClientRect(&myrect);
				HDC hDC=pdc->GetSafeHdc();	

				IplImage *img;
				if(result[i]==1)
				{
					Mat roi = pCMobisDlg->m_pass;
					img = &(IplImage)roi;
				}
				else
				{
					Mat roi = pCMobisDlg->m_ng;
					img = &(IplImage)roi;
				}


				CvvImage iimg;			//创建一个CvvImage对象
				iimg.CopyOf(img);
				iimg.DrawToHDC(hDC,&myrect);
				pCMobisDlg->m_pics[i].ReleaseDC( pdc );
			}

			//更新图像主窗口		
			for (int i = 0; i < pCMobisDlg->m_zoomPics.size(); i++)
			{
				pCMobisDlg->m_zoomPics[i].states = result;
				pCMobisDlg->m_zoomPics[i].Invalidate();
			}
			//pCMobisDlg->m_zoomPic.states = result;
			//pCMobisDlg->m_zoomPic.Invalidate();
			//pCMobisDlg->m_zoomPic2.states = result;
			//pCMobisDlg->m_zoomPic2.Invalidate();
		}

		//保存图像数据
		pCMobisDlg->savePic(images);


		vector<myAlgorithm_ncc::myresult> result = cat.getAllResult();

		//CString messages("正负模板相似度，与前面图的距离偏差 \n");
		//for (int i = 0; i < result.size(); i++)
		//{
		//	//Point offshit;
		//	//if(pCMobisDlg->m_result.size()>0)
		//	//{
		//	//	Point prePt = pCMobisDlg->m_result[i].result?pCMobisDlg->m_result[i].p_max_pt:pCMobisDlg->m_result[i].n_max_pt;
		//	//	Point afterPt = result[i].result?result[i].p_max_pt:result[i].n_max_pt;
		//	//	offshit =  afterPt-prePt;
		//	//}
		//	CString m;
		//	/*m.Format("%d: %.3f,%.3f   match_value=%.3f   x=%d,y=%d \n",i+1,result[i].p_max,result[i].n_max,result[i].directValue,offshit.x,offshit.y);*/
		//	m.Format("%d: %.3f,%.3f  match_value=%.3f \n",i+1,result[i].p_max,result[i].n_max,result[i].directValue);
		//	messages+=m;
		//}
		//::MessageBox(pCMobisDlg->m_hWnd,messages,"详细结果",0);

		//ofstream fout;
		//fout.open("output.txt",ios_base::app);
		//fout << messages << "\n";
		//fout.close();

		/*CString messages2;
		if(pCMobisDlg->m_result.size()>0)
		{
		for (int i = 0; i < result.size(); i++)
		{

		CString str;
		str.Format("%d: x=%d,y=%d \n",i+1,offshit.x,offshit.y);
		messages2+=str;
		}
		::MessageBox(pCMobisDlg->m_hWnd,messages2,"距离偏差",0);
		}*/
		pCMobisDlg->m_result = result;
	}

	return true;
}

unsigned CMobisDlg:: FindCameraThread(void*params)
{
	CMobisDlg* pCMobisDlg = (CMobisDlg*)params;

	while(pCMobisDlg->m_cameraManage.m_cameraIDList.size()<4)
	{
		pCMobisDlg->m_cameraManage.findCamera();
		Sleep(800);
	}
	pCMobisDlg->m_cameraManage.allocationCameraConnect();
	return true;
}

unsigned CMobisDlg:: AcqAndShowThread(void*params)
{

	point_and_camID* p = (point_and_camID*)params;
	CMobisDlg* pCMobisDlg = (CMobisDlg*)(p->Point);
	int camID = p->camID;
	while(1)
	{
		if(WaitForSingleObject(g_CamAcqs[camID],INFINITE)==WAIT_OBJECT_0)
		{
			if(!pCMobisDlg->m_cameraManage.m_cameraList.empty())
			{
				EnterCriticalSection(&g_CamBufs[camID]); 
				pCMobisDlg->workPool_imgs[camID] = pCMobisDlg->m_cameraManage.m_cameraList[camID].img;
				Mat rgb_img=pCMobisDlg->workPool_imgs[camID].clone();//将相机图像数据拷贝出来 用于显示
				LeaveCriticalSection(&g_CamBufs[camID]); 
				SetEvent(g_ReadyChecks[camID]);			//通知检测函数，图像已经准备好


				if(rgb_img.channels()==1)
					cvtColor(rgb_img,rgb_img,CV_GRAY2RGB);
				pCMobisDlg->m_zoomPics[camID].UpdateImage(rgb_img);

				Sleep(100);  //控制显示速度，太快UI线程会卡
			}
		}
	}

	return true;
}

void CMobisDlg::readFlie()
{
	AllXingHaos.clear();
	//读文件
	CFileFind fileFinder;
	CString filePath = _T("*.yml");
	BOOL bFinished = fileFinder.FindFile(filePath);
	while(bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();
		//if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //若是目录则递归调用此方法
		//{
		//	BayesCategoryTest(bt, fileFinder.GetFilePath());
		//}
		//else  //再判断是否为txt文件
		{
			//获取文件类型
			CString fileName = fileFinder.GetFileName();
			int dotPos=fileName.ReverseFind('.');
			CString fileExt=fileName.Right(fileName.GetLength()-dotPos);
			if(fileExt == _T(".yml"))  //若是txt文件则开始分类测试
			{
				ModelManage m_ModelManage;
				FileStorage fs(fileName.GetBuffer(0), FileStorage::READ);
				fs["MyDataManage"] >> m_ModelManage; 	
				fs.release();
				AllXingHaos.push_back(m_ModelManage);
				//myUpdata(false);
			}
		}
	}

	fileFinder.Close();
}

void CMobisDlg::writeFlie()
{
	//读文件
	CFileFind fileFinder;
	CString filePath = _T("*.*");
	BOOL bFinished = fileFinder.FindFile(filePath);
	while(bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();
		//if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //若是目录则递归调用此方法
		//{
		//	BayesCategoryTest(bt, fileFinder.GetFilePath());
		//}
		//else  //再判断是否为txt文件
		{
			//获取文件类型
			CString fileName = fileFinder.GetFileName();
			int dotPos=fileName.ReverseFind('.');
			CString fileExt=fileName.Right(fileName.GetLength()-dotPos);
			if(fileExt == _T(".yml"))  //若是txt文件则开始分类测试
			{
				DeleteFile(fileName);
			}
		}
	}

	fileFinder.Close();


	ModelManage m_ModelManage;
	for (int i = 0; i < AllXingHaos.size(); i++)
	{

		FileStorage fs(AllXingHaos[i].m_Describe+".yml", FileStorage::WRITE);
		fs << "MyDataManage" << AllXingHaos[i]; 	
		fs.release();
	}

}

/*================================================================ 
* 
* 函数原型：void showimage(cv::Mat& image,int IDC)； 
* 
* 参    数：cv::Mat &image -- 要显示的图像
*			 int IDC	    -- 显示图像的图像控件的ID
* 
* 功能描述: 将图像显示在对应的图像控件上
*	
* 
* 返 回 值：无
* 
* 抛出异常：无
* 

================================================================*/  
void CMobisDlg::LeoShowImage(cv::Mat& image,int IDC)
{
	CDC* pDC=GetDlgItem(IDC)->GetDC();			//根据ID获得窗口指针再获取与该窗口关联的上下文指针
	pDC->SetStretchBltMode(STRETCH_HALFTONE);		//保持图片不失真
	HDC hDC=pDC->GetSafeHdc();					// 获取设备上下文句柄
	CRect rect;
	GetDlgItem(IDC)->GetClientRect(&rect);		//获取显示区


	IplImage* img=&(IplImage)image;		//将图像转换为IplImage格式，共用同一个内存（浅拷贝）
	CvvImage iimg;								//创建一个CvvImage对象
	iimg.CopyOf(img);
	iimg.DrawToHDC(hDC,&rect);
	ReleaseDC( pDC );

}

void CMobisDlg::myUpdata(bool direct)
{
	if(direct==false)
	{
		//更新型号列表框
		m_list_all.ResetContent(); 
		for (int i = 0; i < AllXingHaos.size(); i++)
		{
			LPCTSTR str = (AllXingHaos)[i].m_Describe.c_str(); 
			m_list_all.AddString(str);
		}
		m_list_all.SetCurSel(m_pos);

	}
	else
	{

	}
}

//保存数据
void CMobisDlg::savePic(vector<cv::Mat> imgs)
{	
	m_DataSave.UpdateModel(&CurrentXinghao);
	m_DataSave.savePic(imgs);
}

LRESULT CMobisDlg::camera_buf_ready(WPARAM wParam, LPARAM lParam)
{
	if(wParam==0&&m_cameraManage.m_cameraList.size()>=1)
	{
		EnterCriticalSection(&g_CamBufs[0]); 
		workPool_imgs[0] = m_cameraManage.m_cameraList[0].img;
		Mat rgb_img=workPool_imgs[0];
		LeaveCriticalSection(&g_CamBufs[0]); 

		if(rgb_img.channels()==1)
			cvtColor(rgb_img,rgb_img,CV_GRAY2RGB);
		if(::IsWindowEnabled( m_zoomPics[0].GetSafeHwnd()))
		{
			m_zoomPics[0].UpdateImage(rgb_img);
		}
	}
	else if(wParam==1&&m_cameraManage.m_cameraList.size()>=2)
	{
		EnterCriticalSection(&g_CamBufs[1]); 
		workPool_imgs[1] = m_cameraManage.m_cameraList[1].img;
		Mat rgb_img2 = workPool_imgs[1];
		LeaveCriticalSection(&g_CamBufs[1]); 
		if(rgb_img2.channels()==1)
			cvtColor(rgb_img2,rgb_img2,CV_GRAY2RGB);

		if(::IsWindowEnabled( m_zoomPics[1].GetSafeHwnd()))
		{
			m_zoomPics[1].UpdateImage(rgb_img2);
		}
	}

	//SetEvent(m_hAcqEvent);
	return true;
}






void CMobisDlg::ChangeSize(UINT nID, int x, int y)  //nID为控件ID，x,y分别为对话框的当前长和宽
{
	for (int i = 0; i < ctl_IDs.size(); i++)
	{
		CWnd *pWnd=GetDlgItem(ctl_IDs[i]); 
		if(pWnd!=NULL)     //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
		{
			CRect rec; 
			//pWnd->GetWindowRect(&rec);  //获取控件变化前的大小
			//ScreenToClient(&rec);   //将控件大小装换位在对话框中的区域坐标
			rec.left  =ctl_Rects[i].left*x/m_rect.Width();  //按照比例调整空间的新位置
			rec.top   =ctl_Rects[i].top*y/m_rect.Height();
			rec.bottom=ctl_Rects[i].bottom*y/m_rect.Height();
			rec.right =ctl_Rects[i].right*x/m_rect.Width();
			pWnd->MoveWindow(rec);   //伸缩控件
		}
	}
}

void CMobisDlg::OnSize(UINT nType, int cx, int cy)  //cx,cy就是当前对话框的长和宽
{
	CDialog::OnSize(nType, cx, cy);

	if(nType!=SIZE_MINIMIZED )  //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
	{
		ChangeSize(IDC_IMG,cx,cy);  //对每一个控件依次做调整
		//ChangeSize(IDC_IMG2,cx,cy);  //对每一个控件依次做调整
		//ChangeSize(IDC_BT_ZHAOHAO,cx,cy);
		//ChangeSize(IDC_BUILDMODEL,cx,cy);
		//ChangeSize(IDC_CAMERA_SETTING,cx,cy);
		//ChangeSize(IDC_BUILDMODEL,cx,cy);

		//GetClientRect(&m_rect);   //最后要更新对话框的大小，当做下一次变化的旧坐标；
	}
	Invalidate();
}

void CMobisDlg::getCtlRect(vector<int> &ctl_IDs,vector<CRect> &ctl_Rects)
{
	for (int i = 0; i < ctl_IDs.size(); i++)
	{
		CWnd *pWnd=GetDlgItem(ctl_IDs[i]); 
		if(pWnd!=NULL)     //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
		{

			CRect rec; 
			pWnd->GetWindowRect(&rec);  //获取控件变化前的大小
			ScreenToClient(&rec);   //将控件大小装换位在对话框中的区域坐标
			ctl_Rects.push_back(rec);


		}
	}

}


void CMobisDlg::OnBnClickedstarttest()
{
	SetTimer(1,2000,NULL);//启动定时器1,定时时间是1秒
}

void CMobisDlg::OnBnClickedstoptest()
{
	KillTimer(1);        //关闭定时器1。
}

void CMobisDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)      
	{      
	case 1:      
		OnBnClickedBegincheck();      
		break;   
	default:      
		break;      
	}      

	CDialogEx::OnTimer(nIDEvent);
}



void CMobisDlg::OnBnClickedButton1()
{
	// 设置过滤器   
	TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");   
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
	CString strFilePath;   

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())   
	{   
		// 如果点击了文件对话框上的“打开”按钮，则将新图像显示出来
		strFilePath = fileDlg.GetPathName(); 
		if (workPool_imgs.size()<1)
			return ;
		workPool_imgs[0] = imread(strFilePath.GetBuffer(0));

		Mat rgb_img = workPool_imgs[0];
		if(rgb_img.channels()==1)
			cvtColor(rgb_img,rgb_img,CV_GRAY2RGB);
		m_zoomPics[0].UpdateImage(rgb_img);

	}
}   

void CMobisDlg::OnBnClickedButton2()
{
	// 设置过滤器   
	TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");   
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
	CString strFilePath;   

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())   
	{   
		// 如果点击了文件对话框上的“打开”按钮，则将新图像显示出来
		strFilePath = fileDlg.GetPathName(); 
		if (workPool_imgs.size()<2)
			return ;
		workPool_imgs[1]= imread(strFilePath.GetBuffer(0));

		Mat rgb_img = workPool_imgs[1];
		if(rgb_img.channels()==1)
			cvtColor(rgb_img,rgb_img,CV_GRAY2RGB);
		m_zoomPics[1].UpdateImage(rgb_img);


	}   
}
//
//void CMobisDlg::OnBnClickedButton3()
//{
//	// 设置过滤器   
//	TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");   
//	// 构造打开文件对话框   
//	CFileDialog fileDlg(false, NULL, NULL, 0, szFilter, this);   
//	CString strFilePath;   
//
//	// 显示打开文件对话框   
//	if (IDOK == fileDlg.DoModal())   
//	{   
//		// 如果点击了文件对话框上的“打开”按钮，则将新图像显示出来
//		strFilePath = fileDlg.GetPathName(); 
//
//		string src  = strFilePath.GetBuffer(0);
//
//		for (int i = 0; i < CurrentXinghao.m_Models.size(); i++)
//		{
//			Mat pmodel = CurrentXinghao.m_Models[i].m_pModels[0];
//			Mat nmodel = CurrentXinghao.m_Models[i].m_nModels[0];
//			Mat testimage(workPool_imgs[0],CurrentXinghao.m_Models[i].Search_rect);
//
//			CString pstr;
//			pstr.Format(strFilePath+"_PModel_"+"%d"+".bmp",i);
//			imwrite(pstr.GetBuffer(),pmodel);
//
//			CString nstr;
//			nstr.Format(strFilePath+"_NModel_"+"%d"+".bmp",i);
//			imwrite(nstr.GetBuffer(),nmodel);
//
//			CString reginstr;
//			reginstr.Format(strFilePath+"_region_"+"%d"+".bmp",i);
//			imwrite(reginstr.GetBuffer(),testimage);
//
//
//		}
//		/*workPool_img2 = imread(strFilePath.GetBuffer(0));
//
//		Mat rgb_img = workPool_img2;
//		if(rgb_img.channels()==1)
//		cvtColor(rgb_img,rgb_img,CV_GRAY2RGB);
//		m_zoomPic2.UpdateImage(rgb_img);*/
//
//
//	}   
//}
//
//void CMobisDlg::OnBnClickedButton4()
//{
//	vector<double> values;
//	int num = CurrentXinghao.m_Models.size();
//	for (int i = 0; i <num; i++)
//	{
//
//		Mat pmodel = CurrentXinghao.m_Models[i].m_pModels[0];
//		Mat nmodel = CurrentXinghao.m_Models[i].m_nModels[0];
//		Mat result;
//		matchTemplate(pmodel,nmodel,result,CV_TM_CCOEFF_NORMED);
//		double maxValue;
//		minMaxLoc(result,0,&maxValue,0,0);
//		values.push_back(maxValue);
//	}
//	CString messages;
//	for (int i = 0; i < values.size(); i++)
//	{
//		CString m;
//		m.Format("位置%d  :正负模板相似度=%.3f   \n",i+1,values[i]);
//		messages+=m;
//	}
//	MessageBoxA(messages,"详细结果",0);
//
//
//
//	ofstream fout;
//	fout.open("output.txt");
//	fout << messages << "\n";
//
//
//
//}



int CMobisDlg::timeOutNum = 0;
void CMobisDlg::getImages(vector<Mat> &images,DWORD timeOut,int tryNum )
{
	int num = m_cameraManage.m_cameraList.size();
	if (num>0 )  //有相机
	{
		for (int i = 0; i < tryNum; i++) //尝试tryNUm次
		{

			if(m_cameraManage.m_cameraList[0].m_TrigSetting==SoftWareTrig)
			{
				for (int i = 0; i < num; i++)
				{
					m_cameraManage.m_cameraList[i].OnBnClickedSwtriggerbutton();
					ResetEvent(g_ReadyChecks[i]);     //同步
				}
			}
			else
			{
				for (int i = 0; i < num; i++)
				{
					ResetEvent(g_ReadyChecks[i]);     //同步
				}

			}



			DWORD  ret = WaitForMultipleObjects(num,&g_ReadyChecks[0],true,timeOut);
			if(ret==WAIT_OBJECT_0)
			{
				for (int i = 0; i < num; i++)
				{
					images.push_back(workPool_imgs[i].clone());
				}

				break;

			}
			else if (ret==WAIT_TIMEOUT)
			{
				//继续try

				timeOutNum++;
			}
		}


	}
	else if(num==0)//无相机，检测指定图片
	{
		for (int i = 0; i <workPool_imgs.size(); i++)
		{
			images.push_back(workPool_imgs[i].clone());
		}
	}

}

