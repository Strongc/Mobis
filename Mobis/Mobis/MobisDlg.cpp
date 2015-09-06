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
	//	DDX_Control(pDX, IDC_IMG+i,m_zoomPics[i]);  //�����������ƱȽϴ�  ����ͼ���Զ�ʾ�ؼ���ID��IDC_IMG�������������ӡ�
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
	GetClientRect(&m_rect);  //��ȡ�Ի���Ĵ�С
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



	//��ʼ��PictureControl�ؼ�///////////////////////
	for (int i = 0; i < m_zoomPics.size(); i++)
	{
		m_zoomPics[i].ID = i;
		m_zoomPics[i].UpdateImage(workPool_imgs[i]);  
	}


	//���ļ����ͺ���Ϣ��������PictureControl�ؼ�///////////
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
	//��ʼ������ͼƬ////////////////////////////////
	m_pass = imread("pass.bmp");
	m_ng = imread("ng.bmp");
	m_no = imread("no.bmp");

	//��ʼ���ͺ��б�ؼ�////////////////////////////
	myUpdata(false);

	//��ʼ�����///////////////////////////////////
	//m_cameraManage.findCamera();
	if(m_cameraManage.m_cameraIDList.size()<1)
	{
		m_hFindCamThread = (HANDLE)_beginthreadex(NULL,0,FindCameraThread,this,0,NULL);
	}
	else
		m_cameraManage.allocationCameraConnect();




	//��ʼ��ȫ�ֱ���///////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < g_CamNum; i++)
	{
		InitializeCriticalSection(&g_CamBufs[i]); 
		g_CamAcqs[i] = CreateEvent( NULL, FALSE, FALSE, NULL );
	}
	//��ʼ��ȫ�ֱ��� ---����check��ť���õ�����ͼ������ͬ���ı���///////////////////////////////////////
	for (int i = 0; i < g_CamNum; i++)
	{
		g_ReadyChecks[i] = CreateEvent( NULL, TRUE, FALSE, NULL );
	}

	//��ʼ���ɼ��߳�////////////////////////////////////////////////////////////////////////////////////
	point_and_camIDs.resize(g_CamNum);
	for (int i = 0; i < g_CamNum; i++)
	{
		point_and_camIDs[i].camID=i;
		point_and_camIDs[i].Point=this;
		m_hAcqThread = (HANDLE)_beginthreadex(NULL,0,AcqAndShowThread,&point_and_camIDs[i],0,NULL);
	}
	//��ʼ������߳�////////////////////////////////////////////////////////////////////////////////////
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
		if(dlg.m_pos>0&&dlg.m_pos<AllXingHaos.size())  //����ѡ��ĵƵ��ͺţ���ȻҪ��֤�ں���Χ��
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
		//��ȡͼ��///////////////////////////////////////////////////////////////////////////////
		vector<Mat>images; 
		pCMobisDlg->getImages(images);
		//int num = pCMobisDlg->m_cameraManage.m_cameraList.size();
		//if (num>0 )  //�����
		//{
		//	if(pCMobisDlg->m_cameraManage.m_cameraList[0].m_TrigSetting==SoftWareTrig)
		//	{
		//		for (int i = 0; i < num; i++)
		//		{
		//			pCMobisDlg->m_cameraManage.m_cameraList[i].OnBnClickedSwtriggerbutton();
		//			ResetEvent(g_ReadyChecks[i]);     //ͬ��
		//		}
		//	}
		//	else
		//	{
		//		for (int i = 0; i < num; i++)
		//		{
		//			ResetEvent(g_ReadyChecks[i]);     //ͬ��
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
		//else if(num==0)//����������ָ��ͼƬ
		//{
		//	for (int i = 0; i <pCMobisDlg->workPool_imgs.size(); i++)
		//	{
		//		images.push_back(pCMobisDlg->workPool_imgs[i].clone());
		//	}
		//}







		/////////////////////////////////////////////////////////////////////////////////////////
		//�����������ͼ��
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
			CvvImage iimg;			//����һ��CvvImage����
			iimg.CopyOf(img);
			iimg.DrawToHDC(hDC,&myrect);
			pCMobisDlg->m_pics[i].ReleaseDC( pdc );
		}

		//��ʾ�������ͼ��
		int modelNum = pCMobisDlg->CurrentXinghao.m_Models.size();
		for (int i = 0; i < modelNum; i++)
		{
			//����Ƿ���ͼ�����////////////////////////////////
			Model c_model =pCMobisDlg->CurrentXinghao.m_Models[i];
			Mat image; 
			if(c_model.m_cameraID>pCMobisDlg->workPool_imgs.size())  //��ֹ�ͺ������CamId��������в����ڡ���ֹ��������Խ��
				continue;
			if(!pCMobisDlg->workPool_imgs[c_model.m_cameraID].empty()) //���û��ͼ��Ͳ�����
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

			CvvImage iimg;			//����һ��CvvImage����
			iimg.CopyOf(img);
			iimg.DrawToHDC(hDC,&myrect);
			pCMobisDlg->m_pics[i].ReleaseDC( pdc );
		}




		////������ʾ���
		for (int i = 0; i < 20; i++)
		{
			CDC *pdc = pCMobisDlg->m_status[i].GetDC();
			pdc->SetStretchBltMode(STRETCH_HALFTONE);
			CRect myrect;
			pCMobisDlg->m_status[i].GetClientRect(&myrect);
			HDC hDC=pdc->GetSafeHdc();	

			Mat roi = pCMobisDlg->m_no;
			IplImage *img = &(IplImage)roi;

			CvvImage iimg;			//����һ��CvvImage����
			iimg.CopyOf(img);
			iimg.DrawToHDC(hDC,&myrect);
			pCMobisDlg->m_pics[i].ReleaseDC( pdc );
		}

		myAlgorithm_ncc cat(&pCMobisDlg->CurrentXinghao);
		if(!cat.templateMatching(images))
			AfxMessageBox("���ʧ�ܣ����ģ���Ƿ������");
		else
		{
			vector<int> result = cat.getValueResult();
			//��������
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


				CvvImage iimg;			//����һ��CvvImage����
				iimg.CopyOf(img);
				iimg.DrawToHDC(hDC,&myrect);
				pCMobisDlg->m_pics[i].ReleaseDC( pdc );
			}

			//����ͼ��������		
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

		//����ͼ������
		pCMobisDlg->savePic(images);


		vector<myAlgorithm_ncc::myresult> result = cat.getAllResult();

		//CString messages("����ģ�����ƶȣ���ǰ��ͼ�ľ���ƫ�� \n");
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
		//::MessageBox(pCMobisDlg->m_hWnd,messages,"��ϸ���",0);

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
		::MessageBox(pCMobisDlg->m_hWnd,messages2,"����ƫ��",0);
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
				Mat rgb_img=pCMobisDlg->workPool_imgs[camID].clone();//�����ͼ�����ݿ������� ������ʾ
				LeaveCriticalSection(&g_CamBufs[camID]); 
				SetEvent(g_ReadyChecks[camID]);			//֪ͨ��⺯����ͼ���Ѿ�׼����


				if(rgb_img.channels()==1)
					cvtColor(rgb_img,rgb_img,CV_GRAY2RGB);
				pCMobisDlg->m_zoomPics[camID].UpdateImage(rgb_img);

				Sleep(100);  //������ʾ�ٶȣ�̫��UI�̻߳Ῠ
			}
		}
	}

	return true;
}

void CMobisDlg::readFlie()
{
	AllXingHaos.clear();
	//���ļ�
	CFileFind fileFinder;
	CString filePath = _T("*.yml");
	BOOL bFinished = fileFinder.FindFile(filePath);
	while(bFinished)  //ÿ��ѭ����Ӧһ�����Ŀ¼
	{
		bFinished = fileFinder.FindNextFile();
		//if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //����Ŀ¼��ݹ���ô˷���
		//{
		//	BayesCategoryTest(bt, fileFinder.GetFilePath());
		//}
		//else  //���ж��Ƿ�Ϊtxt�ļ�
		{
			//��ȡ�ļ�����
			CString fileName = fileFinder.GetFileName();
			int dotPos=fileName.ReverseFind('.');
			CString fileExt=fileName.Right(fileName.GetLength()-dotPos);
			if(fileExt == _T(".yml"))  //����txt�ļ���ʼ�������
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
	//���ļ�
	CFileFind fileFinder;
	CString filePath = _T("*.*");
	BOOL bFinished = fileFinder.FindFile(filePath);
	while(bFinished)  //ÿ��ѭ����Ӧһ�����Ŀ¼
	{
		bFinished = fileFinder.FindNextFile();
		//if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //����Ŀ¼��ݹ���ô˷���
		//{
		//	BayesCategoryTest(bt, fileFinder.GetFilePath());
		//}
		//else  //���ж��Ƿ�Ϊtxt�ļ�
		{
			//��ȡ�ļ�����
			CString fileName = fileFinder.GetFileName();
			int dotPos=fileName.ReverseFind('.');
			CString fileExt=fileName.Right(fileName.GetLength()-dotPos);
			if(fileExt == _T(".yml"))  //����txt�ļ���ʼ�������
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
* ����ԭ�ͣ�void showimage(cv::Mat& image,int IDC)�� 
* 
* ��    ����cv::Mat &image -- Ҫ��ʾ��ͼ��
*			 int IDC	    -- ��ʾͼ���ͼ��ؼ���ID
* 
* ��������: ��ͼ����ʾ�ڶ�Ӧ��ͼ��ؼ���
*	
* 
* �� �� ֵ����
* 
* �׳��쳣����
* 

================================================================*/  
void CMobisDlg::LeoShowImage(cv::Mat& image,int IDC)
{
	CDC* pDC=GetDlgItem(IDC)->GetDC();			//����ID��ô���ָ���ٻ�ȡ��ô��ڹ�����������ָ��
	pDC->SetStretchBltMode(STRETCH_HALFTONE);		//����ͼƬ��ʧ��
	HDC hDC=pDC->GetSafeHdc();					// ��ȡ�豸�����ľ��
	CRect rect;
	GetDlgItem(IDC)->GetClientRect(&rect);		//��ȡ��ʾ��


	IplImage* img=&(IplImage)image;		//��ͼ��ת��ΪIplImage��ʽ������ͬһ���ڴ棨ǳ������
	CvvImage iimg;								//����һ��CvvImage����
	iimg.CopyOf(img);
	iimg.DrawToHDC(hDC,&rect);
	ReleaseDC( pDC );

}

void CMobisDlg::myUpdata(bool direct)
{
	if(direct==false)
	{
		//�����ͺ��б��
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

//��������
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






void CMobisDlg::ChangeSize(UINT nID, int x, int y)  //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{
	for (int i = 0; i < ctl_IDs.size(); i++)
	{
		CWnd *pWnd=GetDlgItem(ctl_IDs[i]); 
		if(pWnd!=NULL)     //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
		{
			CRect rec; 
			//pWnd->GetWindowRect(&rec);  //��ȡ�ؼ��仯ǰ�Ĵ�С
			//ScreenToClient(&rec);   //���ؼ���Сװ��λ�ڶԻ����е���������
			rec.left  =ctl_Rects[i].left*x/m_rect.Width();  //���ձ��������ռ����λ��
			rec.top   =ctl_Rects[i].top*y/m_rect.Height();
			rec.bottom=ctl_Rects[i].bottom*y/m_rect.Height();
			rec.right =ctl_Rects[i].right*x/m_rect.Width();
			pWnd->MoveWindow(rec);   //�����ؼ�
		}
	}
}

void CMobisDlg::OnSize(UINT nType, int cx, int cy)  //cx,cy���ǵ�ǰ�Ի���ĳ��Ϳ�
{
	CDialog::OnSize(nType, cx, cy);

	if(nType!=SIZE_MINIMIZED )  //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
	{
		ChangeSize(IDC_IMG,cx,cy);  //��ÿһ���ؼ�����������
		//ChangeSize(IDC_IMG2,cx,cy);  //��ÿһ���ؼ�����������
		//ChangeSize(IDC_BT_ZHAOHAO,cx,cy);
		//ChangeSize(IDC_BUILDMODEL,cx,cy);
		//ChangeSize(IDC_CAMERA_SETTING,cx,cy);
		//ChangeSize(IDC_BUILDMODEL,cx,cy);

		//GetClientRect(&m_rect);   //���Ҫ���¶Ի���Ĵ�С��������һ�α仯�ľ����ꣻ
	}
	Invalidate();
}

void CMobisDlg::getCtlRect(vector<int> &ctl_IDs,vector<CRect> &ctl_Rects)
{
	for (int i = 0; i < ctl_IDs.size(); i++)
	{
		CWnd *pWnd=GetDlgItem(ctl_IDs[i]); 
		if(pWnd!=NULL)     //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
		{

			CRect rec; 
			pWnd->GetWindowRect(&rec);  //��ȡ�ؼ��仯ǰ�Ĵ�С
			ScreenToClient(&rec);   //���ؼ���Сװ��λ�ڶԻ����е���������
			ctl_Rects.push_back(rec);


		}
	}

}


void CMobisDlg::OnBnClickedstarttest()
{
	SetTimer(1,2000,NULL);//������ʱ��1,��ʱʱ����1��
}

void CMobisDlg::OnBnClickedstoptest()
{
	KillTimer(1);        //�رն�ʱ��1��
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
	// ���ù�����   
	TCHAR szFilter[] = _T("�����ļ�(*.*)|*.*||");   
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
	CString strFilePath;   

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())   
	{   
		// ���������ļ��Ի����ϵġ��򿪡���ť������ͼ����ʾ����
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
	// ���ù�����   
	TCHAR szFilter[] = _T("�����ļ�(*.*)|*.*||");   
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);   
	CString strFilePath;   

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())   
	{   
		// ���������ļ��Ի����ϵġ��򿪡���ť������ͼ����ʾ����
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
//	// ���ù�����   
//	TCHAR szFilter[] = _T("�����ļ�(*.*)|*.*||");   
//	// ������ļ��Ի���   
//	CFileDialog fileDlg(false, NULL, NULL, 0, szFilter, this);   
//	CString strFilePath;   
//
//	// ��ʾ���ļ��Ի���   
//	if (IDOK == fileDlg.DoModal())   
//	{   
//		// ���������ļ��Ի����ϵġ��򿪡���ť������ͼ����ʾ����
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
//		m.Format("λ��%d  :����ģ�����ƶ�=%.3f   \n",i+1,values[i]);
//		messages+=m;
//	}
//	MessageBoxA(messages,"��ϸ���",0);
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
	if (num>0 )  //�����
	{
		for (int i = 0; i < tryNum; i++) //����tryNUm��
		{

			if(m_cameraManage.m_cameraList[0].m_TrigSetting==SoftWareTrig)
			{
				for (int i = 0; i < num; i++)
				{
					m_cameraManage.m_cameraList[i].OnBnClickedSwtriggerbutton();
					ResetEvent(g_ReadyChecks[i]);     //ͬ��
				}
			}
			else
			{
				for (int i = 0; i < num; i++)
				{
					ResetEvent(g_ReadyChecks[i]);     //ͬ��
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
				//����try

				timeOutNum++;
			}
		}


	}
	else if(num==0)//����������ָ��ͼƬ
	{
		for (int i = 0; i <workPool_imgs.size(); i++)
		{
			images.push_back(workPool_imgs[i].clone());
		}
	}

}

