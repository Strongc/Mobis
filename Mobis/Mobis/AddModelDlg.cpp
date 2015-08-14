#include "stdafx.h"
#include "Mobis.h"
#include "AddModelDlg.h"
#include "afxdialogex.h"
#include "types.h"
Rect amplifyRrect(Rect rect,double m_factor,double f_x=0,double f_y=0);
bool keepRectSafty(Rect rect,Size imgsize);

// addModel2 dialog

IMPLEMENT_DYNAMIC(addModel2, CDialogEx)

addModel2::addModel2(CWnd* pParent /*=NULL*/)
	: CDialogEx(addModel2::IDD, pParent)
	, m_slider_value(_T(""))
	, m_checkID(0)
{

}

addModel2::~addModel2()
{
}

void addModel2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_addm_pic, m_zoomCtrl);
	DDX_Control(pDX, IDC_DIRECT_PIC1, m_directPic);
	DDX_Control(pDX, IDC_DIRECT_PIC2, m_directPic2);
	DDX_Control(pDX, IDC_SHOWDIRECT, m_showDirectPic);
	DDX_Control(pDX, IDC_Search_Rect, m_Search_Rect);

	DDX_Control(pDX, IDC_ZHENG_PIC1, m_zhengPic[0]);
	DDX_Control(pDX, IDC_ZHENG_PIC2, m_zhengPic[1]);
	DDX_Control(pDX, IDC_ZHENG_PIC3, m_zhengPic[2]);
	DDX_Control(pDX, IDC_FU_PIC1, m_fuPic[0]);
	DDX_Control(pDX, IDC_FU_PIC2, m_fuPic[1]);
	DDX_Control(pDX, IDC_FU_PIC3, m_fuPic[2]);

	DDX_Text(pDX, IDC_PRect1, m_zhengRect[0]);
	DDX_Text(pDX, IDC_PRect2, m_zhengRect[1]);
	DDX_Text(pDX, IDC_PRect3, m_zhengRect[2]);
	DDX_Text(pDX, IDC_PSearchRect1, m_zhengSearchRect[0]);
	DDX_Text(pDX, IDC_PSearchRect2, m_zhengSearchRect[1]);
	DDX_Text(pDX, IDC_PSearchRect3, m_zhengSearchRect[2]);
	DDX_Control(pDX, IDC_ZHENG_SearchRect, m_zhengPicSearchRect);


	DDX_Text(pDX, IDC_NRect1, m_fuRect[0]);
	DDX_Text(pDX, IDC_NRect2, m_fuRect[1]);
	DDX_Text(pDX, IDC_NRect3, m_fuRect[2]);
	DDX_Text(pDX, IDC_NSearchRect1, m_fuSearchRect[0]);
	DDX_Text(pDX, IDC_NSearchRect2, m_fuSearchRect[1]);
	DDX_Text(pDX, IDC_NSearchRect3, m_fuSearchRect[2]);
	DDX_Control(pDX, IDC_fu_SearchRect, m_fuPicSearchRect);

	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Text(pDX, IDC_EDIT1, m_slider_value);
	DDX_Control(pDX, IDC_CameraID, m_combo_CameraID);
	DDX_Text(pDX, IDC_EDIT2, m_checkID);
	DDV_MinMaxInt(pDX, m_checkID, 0, 1);
}

BOOL addModel2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ctl=0;

	m_Search_Rect.m_ID = 1;
	m_directPic.m_ID = 100;
	m_directPic2.m_ID = 101;

	m_zhengPic[0].m_ID =1001;
	m_zhengPic[1].m_ID =1002;
	m_zhengPic[2].m_ID =1003;
	m_fuPic[0].m_ID =2001;
	m_fuPic[1].m_ID =2002;
	m_fuPic[2].m_ID =2003;

	//更新组合框相机ID ，及数据源
	picSources.push_back(-1);
	if(!workPool_img.empty())
	{
		m_combo_CameraID.AddString("Camera 0");
		picSources.push_back(0);
	}

	if(!workPool_img2.empty())
	{
		m_combo_CameraID.AddString("Camera 1");
		picSources.push_back(1);
	}


	//选择数据源
	if(picSources.size()>=2)	
	{
		m_combo_CameraID.SetCurSel(0); 
		choosePicSource(picSources[1]);
	}
	else 
	{
		m_combo_CameraID.SetCurSel(-1);
		choosePicSource(picSources[0]);
	}
	m_zoomCtrl.AddRelatedModel(*p_Model);



	//跟新检测目标
	m_checkID = p_Model->m_cameraID;

	m_slider.SetRange(1,50);
	if(p_Model->m_pModels.size()>0)
	{
		Rect rect = p_Model->getPModelRects(0);
		Rect SearchRect = p_Model->getPModelSearchRects(0);
		m_slider.SetPos(SearchRect.width-rect.width);
	}
	else if(p_Model->m_nModels.size()>0)
	{
		Rect rect = p_Model->getNModelRects(0);
		Rect SearchRect = p_Model->getNModelSearchRects(0);
		m_slider.SetPos(SearchRect.width-rect.width);
	}
	else
		m_slider.SetPos(15);

	int nPos = m_slider.GetPos(); 
	CString str;
	str.Format("%d",nPos);
	m_slider_value=str;
	UpdateData(false);




	UpdateControl();
	return true;
}

BEGIN_MESSAGE_MAP(addModel2, CDialogEx)
	ON_MESSAGE(WM_EXTPICMENU_ADD,OnMessage_ExtPicture_Add) 
	ON_MESSAGE(WM_EXTPICMENU_DELETE,OnMessage_ExtPicture_Delete) 
	ON_MESSAGE(WM_ZOOMCTRL_LDCLICK,OnMessage_ZoomPicture_add) 
	ON_MESSAGE(WM_ZOOMCTRL_RCLICK,OnMessage_ZoomPicture_cancel) 
	ON_BN_CLICKED(IDC_CHOOSE_PIC, &addModel2::OnBnClickedChoosePic)
	ON_BN_CLICKED(IDC_CHECK2, &addModel2::OnBnClickedCheck2)
	ON_STN_CLICKED(IDC_RADIO2, &addModel2::OnStnClickedRadio2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &addModel2::OnCustomdrawSlider1)
	ON_CBN_SELCHANGE(IDC_CameraID, &addModel2::OnSelchangeCameraid)

	ON_MESSAGE(WM_DATA_READY,camera_buf_ready) 
	ON_EN_CHANGE(IDC_EDIT2, &addModel2::OnChangeEdit2)
END_MESSAGE_MAP()


// addModel2 message handlers
LRESULT addModel2::OnMessage_ExtPicture_Add(WPARAM wParam, LPARAM lParam)
{

	m_ctl = lParam;


	Point shifft;
	if(m_ctl<=1003&&m_ctl>=1001)
	{

		if(!p_Model->getDModel().empty())
		{
			shifft = calDirect();
			Rect rrr = p_Model->getDModelRect()+shifft;
			Mat newMat(work_img,rrr); 
			m_showDirectPic.loadImage(newMat);
		}
		else if(!p_Model->getDModel2().empty())
		{
			shifft = calDirect2();
			/*Rect rrr = p_Model->getDModelRect()+shifft;
			Mat newMat(work_img,rrr); */
			m_showDirectPic.loadImage(Mat());
		}
		else
		{
			shifft=Point(0,0);
			m_showDirectPic.loadImage(Mat());
		}
	}
	else if(m_ctl<=2003&&m_ctl>=2001)
	{

		if(!p_Model->getDModel2().empty())
		{
			shifft = calDirect2();
			Rect rrr = p_Model->getDModelRect2()+shifft;
			Mat newMat(work_img,rrr); 
			m_showDirectPic.loadImage(newMat);
		}
		else if(!p_Model->getDModel().empty())
		{
			shifft = calDirect();
			/*Rect rrr = p_Model->getDModelRect()+shifft;
			Mat newMat(work_img,rrr); */
			m_showDirectPic.loadImage(Mat());
		}
		else
		{
			shifft=Point(0,0);
			m_showDirectPic.loadImage(Mat());
		}
	}
	else if(m_ctl==100)
	{
		if(!p_Model->getDModel().empty())
		{
			shifft = calDirect();
		}
		else 
			shifft = Point(0,0);
	}
	else if(m_ctl==101)
	{
		if(!p_Model->getDModel2().empty())
		{
			shifft = calDirect2();
		}
		else 
			shifft = Point(0,0);
	}
	else 
	{

	}

	Rect r = getModelRectFromID(p_Model,m_ctl);
	Rect newRect = r+shifft;



	if(m_zoomCtrl.m_RectTracker!=NULL)
		delete(m_zoomCtrl.m_RectTracker);
	m_zoomCtrl.m_RectTracker = new LeoRectTracker ;
	if(newRect.area()==0)
		m_zoomCtrl.m_RectTracker->m_rect.SetRect(0,0,40,40); //初始化m_rect的值
	else
	{
		Point tl = m_zoomCtrl.ImageToClient(newRect.tl());
		Point br = m_zoomCtrl.ImageToClient(newRect.br());
		m_zoomCtrl.m_RectTracker->m_rect.SetRect(tl.x,tl.y,br.x,br.y); //初始化m_rect的值
	}

	m_zoomCtrl.Invalidate(); 
	return true;
}
LRESULT addModel2::OnMessage_ExtPicture_Delete(WPARAM wParam, LPARAM lParam)
{
	m_ctl = lParam;

	protect_deleteModel(p_Model,m_ctl);
	UpdateControl();
	return true;
}
LRESULT addModel2::OnMessage_ZoomPicture_add(WPARAM wParam, LPARAM lParam)
{


	CRect r = m_zoomCtrl.m_RectTracker->m_rect;
	cv::Point client_pt1(r.left,r.top);
	cv::Point client_pt2(r.right,r.bottom);
	cv::Point img_pt1 = m_zoomCtrl.ClientToImage(client_pt1);
	cv::Point img_pt2 = m_zoomCtrl.ClientToImage(client_pt2);


	cv::Rect rect = Rect(img_pt1,img_pt2);
	cv::Mat img_roi(m_zoomCtrl.m_img,rect);

	Mat pm,nm;
	if(p_Model->m_pModels.size()>0)
	{
		pm = p_Model->getPModel(0);
	}
	if(p_Model->m_nModels.size()>0)
	{
		nm = p_Model->getNModel(0);
	}
	protect_addModel(p_Model,m_ctl,m_zoomCtrl.m_img,rect);

	Mat pm2,nm2;

	if(p_Model->m_pModels.size()>0)
	{
		pm2 = p_Model->getPModel(0);
	}
	if(p_Model->m_nModels.size()>0)
	{
		nm2 = p_Model->getNModel(0);
	}

	UpdateControl();
	delete(m_zoomCtrl.m_RectTracker);
	m_zoomCtrl.m_RectTracker=NULL;
	m_zoomCtrl.Invalidate(); 

	return true;
}
LRESULT addModel2::OnMessage_ZoomPicture_cancel(WPARAM wParam, LPARAM lParam)
{
	if(m_zoomCtrl.m_RectTracker!=NULL)
		delete(m_zoomCtrl.m_RectTracker);
	m_zoomCtrl.m_RectTracker=NULL;
	m_zoomCtrl.Invalidate(); 
	return true;
}

void addModel2::UpdateControl()
{
	//初始化图像控件

	//初始化区域位置信息
	//Mat checkregion(work_img,p_Model->m_region);
	//m_checkRegion.loadImage(checkregion);
	//初始化正负模型图像
	for (int i = 0; i < 3; i++)
	{
		m_zhengPic[i].loadImage(Mat());
		m_zhengRect[i] ="";
		m_zhengSearchRect[i] ="";
	}
	for (int i = 0; i < 3; i++)
	{
		m_fuPic[i].loadImage(Mat());
		m_fuRect[i] ="";
		m_fuSearchRect[i] ="";
	}

	for (int i = 0; i < p_Model->m_pModels.size(); i++)
	{
		m_zhengPic[i].loadImage(p_Model->getPModel(i));


		Rect r = p_Model->getPModelRects(i);
		Rect sr = p_Model->getPModelSearchRects(i);
		CString str;
		str.Format("(%d,%d,%d,%d)",r.x,r.y,r.width,r.height);
		m_zhengRect[i] =str;
		CString str2;
		str2.Format("(%d,%d,%d,%d)",sr.x,sr.y,sr.width,sr.height);
		m_zhengSearchRect[i] =str2;
	}

	for (int i = 0; i < p_Model->m_nModels.size(); i++)
	{
		m_fuPic[i].loadImage(p_Model->getNModel(i));


		Rect r = p_Model->getNModelRects(i);
		Rect sr = p_Model->getNModelSearchRects(i);
		CString str;
		str.Format("(%d,%d,%d,%d)",r.x,r.y,r.width,r.height);
		m_fuRect[i] =str;
		CString str2;
		str2.Format("(%d,%d,%d,%d)",sr.x,sr.y,sr.width,sr.height);
		m_fuSearchRect[i] =str2;
	}

	if(!p_Model->getDModel().empty())
		m_directPic.loadImage(p_Model->getDModel());
	else
	{
		m_directPic.loadImage(Mat());
		m_zhengPicSearchRect.loadImage(Mat());
		//m_fuPicSearchRect.loadImage(Mat());
	}

	if(!p_Model->getDModel2().empty())
		m_directPic2.loadImage(p_Model->getDModel2());
	else
	{
		m_directPic2.loadImage(Mat());
		//m_zhengPicSearchRect.loadImage(Mat());
		m_fuPicSearchRect.loadImage(Mat());
	}


	if(p_Model->Search_rect.area()!=0&&!work_img.empty())
	{
		Mat showSearchregion(work_img,p_Model->Search_rect);
		m_Search_Rect.loadImage(showSearchregion);
	}
	else
		m_Search_Rect.loadImage(Mat());
	UpdateData(false);


	if(!p_Model->getDModel().empty())
	{


		if(p_Model->m_pModels_SearchRects.size()>0&&!work_img.empty())
		{
			Point shifft = calDirect();
			Rect rrr = p_Model->getPModelSearchRects(0)+shifft;
			Mat newMat(work_img,rrr); 
			m_zhengPicSearchRect.loadImage(newMat);
		}
		else
			m_zhengPicSearchRect.loadImage(Mat());


	}

	if(!p_Model->getDModel2().empty())
	{
		if(p_Model->m_nModels_SearchRects.size()>0&&!work_img.empty())
		{
			Point shifft = calDirect2();
			Rect rrr = p_Model->getNModelSearchRects(0)+shifft;
			Mat newMat(work_img,rrr); 
			m_fuPicSearchRect.loadImage(newMat);
		}
		else
			m_fuPicSearchRect.loadImage(Mat());

	}

}

void addModel2::OnBnClickedChoosePic()
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
		Mat im = imread(strFilePath.GetBuffer(0));
		work_img =im;
		m_zoomCtrl.UpdateImage(work_img);
		//m_zoomCtrl.UpdateImage(im);

	}   

	UpdateControl();
	choosePicSource(-1);
}




void addModel2::protect_addModel(Model * model, int PIC_ID,Mat img,Rect rect)
{

	if(PIC_ID<=1003&&PIC_ID>=1001)
	{
		if(model->getDModel().empty())
		{
			if(!add_DModel_fromModel(model,img,rect))
			{
				MessageBoxA("添加导向模板失败，其范围超过图像大小。可以先添加导向模板");
				return;
			}

		}
		add_PModel(model,PIC_ID,img,rect);
	}
	else if(PIC_ID<=2003&&PIC_ID>=2001)
	{
		if(model->getDModel2().empty())
		{
			if(!add_DModel_fromModel2(model,img,rect))
			{
				MessageBoxA("添加导向模板失败，其范围超过图像大小。可以先添加导向模板");
				return;
			}

		}
		add_NModel(model,PIC_ID,img,rect);
	}
	else if(PIC_ID==100)
	{
		if(!add_DModel(model,img,rect))
		{
			MessageBoxA("添加导向1模板失败，其范围超过图像大小。导向模板放入合适区域");
			return;
		}
	}
	else if(PIC_ID==101)
	{
		if(!add_DModel2(model,img,rect))
		{
			MessageBoxA("添加导向2模板失败，其范围超过图像大小。导向模板放入合适区域");
			return;
		}
	}
	else if(PIC_ID==1)
	{
		model->Search_rect = rect;
	}



}
bool addModel2::add_DModel(Model * model, Mat img,Rect rect)
{
	Rect DModel_SearchRect = amplifyRrect(rect,2);
	Rect DModel_rect =rect;
	if(!keepRectSafty(DModel_SearchRect,Size(img.cols,img.rows)))
		return false;
	if(!keepRectSafty(DModel_rect,Size(img.cols,img.rows)))
		return false;


	model->setDModelRect(DModel_rect);
	model->setDModelSearchRect(DModel_SearchRect);


	Mat DModel(img,DModel_rect);
	model->setDModel(DModel);
	return true;
}
bool addModel2::add_DModel_fromModel(Model * model, Mat img,Rect rect)
{

	Rect DModel_SearchRect = amplifyRrect(rect,5);
	Rect DModel_rect = amplifyRrect(rect,3);
	if(!keepRectSafty(DModel_SearchRect,Size(img.cols,img.rows)))
		return false;
	if(!keepRectSafty(DModel_rect,Size(img.cols,img.rows)))
		return false;


	model->setDModelRect(DModel_rect);
	model->setDModelSearchRect(DModel_SearchRect);


	Mat DModel(img,DModel_rect);
	model->setDModel(DModel.clone());
	if(model->Search_rect.area()==0)
		model->Search_rect = DModel_rect;
	return true;
}
bool addModel2::add_DModel2(Model * model, Mat img,Rect rect)
{
	Rect DModel_SearchRect = amplifyRrect(rect,2);
	Rect DModel_rect =rect;
	if(!keepRectSafty(DModel_SearchRect,Size(img.cols,img.rows)))
		return false;
	if(!keepRectSafty(DModel_rect,Size(img.cols,img.rows)))
		return false;


	model->setDModelRect2(DModel_rect);
	model->setDModelSearchRect2(DModel_SearchRect);


	Mat DModel(img,DModel_rect);
	model->setDModel2(DModel);
	return true;
}
bool addModel2::add_DModel_fromModel2(Model * model, Mat img,Rect rect)
{

	Rect DModel_SearchRect = amplifyRrect(rect,5);
	Rect DModel_rect = amplifyRrect(rect,3);
	if(!keepRectSafty(DModel_SearchRect,Size(img.cols,img.rows)))
		return false;
	if(!keepRectSafty(DModel_rect,Size(img.cols,img.rows)))
		return false;


	model->setDModelRect2(DModel_rect);
	model->setDModelSearchRect2(DModel_SearchRect);


	Mat DModel(img,DModel_rect);
	model->setDModel2(DModel.clone());

	if(model->Search_rect.area()==0)
		model->Search_rect = DModel_rect;
	return true;
}

void addModel2::add_PModel(Model * model,int PIC_ID, Mat img,Rect rect)
{

	Point shifft;
	if(!p_Model->getDModel().empty())
	{
		shifft = calDirect();
	}

	int ID = PIC_ID-1000;
	Mat roi(img,rect); 
	if((model->m_pModels).size()>=ID)
	{
		model->m_pModels[ID-1] = roi.clone();
		model->m_pModels_Rects[ID-1] = rect-shifft;
		model->m_pModels_SearchRects[ID-1] = amplifyRrect(rect-shifft,0,m_slider.GetPos(),m_slider.GetPos());
	}
	else
	{
		model->m_pModels.push_back(roi.clone());
		model->m_pModels_Rects.push_back(rect-shifft);
		model->m_pModels_SearchRects.push_back(amplifyRrect(rect-shifft,0,m_slider.GetPos(),m_slider.GetPos()));

	}

}
void addModel2::add_NModel(Model * model,int PIC_ID, Mat img,Rect rect)
{
	Point shifft;
	if(!p_Model->getDModel2().empty())
	{
		shifft = calDirect2();
	}


	int ID = PIC_ID-2000;
	Mat roi(img,rect); 
	if((model->m_nModels).size()>= ID)
	{
		model->m_nModels[ID-1] = roi.clone();
		model->m_nModels_Rects[ID-1] = rect-shifft;
		model->m_nModels_SearchRects[ID-1] = amplifyRrect(rect-shifft,0,m_slider.GetPos(),m_slider.GetPos());
	}
	else
	{
		model->m_nModels.push_back(roi.clone());
		model->m_nModels_Rects.push_back(rect-shifft);
		model->m_nModels_SearchRects.push_back(amplifyRrect(rect-shifft,0,m_slider.GetPos(),m_slider.GetPos()));
	}
}

void addModel2::protect_deleteModel(Model * model, int PIC_ID)
{

	if(PIC_ID<=1003&&PIC_ID>=1001)
		delete_PModel(model,PIC_ID);
	else if(PIC_ID<=2003&&PIC_ID>=2001)
		delete_NModel(model,PIC_ID);



	if(model->m_pModels.size()==0&&!p_Model->getDModel().empty())
		delete_DModel_fromModel(model);
	if(model->m_nModels.size()==0&&!p_Model->getDModel2().empty())
		delete_DModel_fromModel2(model);
	if(model->m_pModels.size()==0&&model->m_nModels.size()==0)
		model->Search_rect = Rect(0,0,0,0);

}
void addModel2::delete_DModel_fromModel(Model * model)
{

	model->setDModel(Mat());
	model->setDModelRect(Rect());
	model->setDModelSearchRect(Rect());

}
void addModel2::delete_DModel_fromModel2(Model * model)
{

	model->setDModel2(Mat());
	model->setDModelRect2(Rect());
	model->setDModelSearchRect2(Rect());

}
void addModel2::delete_PModel(Model * model,int PIC_ID)
{
	int ID = PIC_ID-1000;
	if((model->m_pModels).size()>=ID)
	{
		vector<Mat>::iterator iter=p_Model->m_pModels.begin()+ID-1;
		p_Model->m_pModels.erase(iter);

		vector<Rect>::iterator it2=p_Model->m_pModels_Rects.begin()+ID-1;
		p_Model->m_pModels_Rects.erase(it2);

		vector<Rect>::iterator it=p_Model->m_pModels_SearchRects.begin()+ID-1;
		p_Model->m_pModels_SearchRects.erase(it);
	}
	else
	{
		return;

	}

}
void addModel2::delete_NModel(Model * model,int PIC_ID)
{
	int ID = PIC_ID-2000;

	if((model->m_nModels).size()>=ID)
	{
		vector<Mat>::iterator iter=p_Model->m_nModels.begin()+ID-1;
		p_Model->m_nModels.erase(iter);

		vector<Rect>::iterator it2=p_Model->m_nModels_Rects.begin()+ID-1;
		p_Model->m_nModels_Rects.erase(it2);

		vector<Rect>::iterator it=p_Model->m_nModels_SearchRects.begin()+ID-1;
		p_Model->m_nModels_SearchRects.erase(it);
	}
	else
	{
		return;

	}
}


Point addModel2::calDirect()
{
	//计算导向模板偏移
	/***********************************************************************/
	Mat SearchRegion(m_zoomCtrl.m_img,p_Model->getDModelSearchRect());
	Mat directModel = p_Model->getDModel();
	Mat directResult;
	if(SearchRegion.empty()||directModel.empty())
		return Point(0,0);
	else
		matchTemplate(SearchRegion,directModel,directResult,CV_TM_CCOEFF_NORMED);

	double maxValue;
	cv::Point2i maxPt;
	minMaxLoc(directResult,0,&maxValue,0,&maxPt);

	Rect searchRect = p_Model->getDModelSearchRect();
	Rect rect = p_Model->getDModelRect();
	Point direct_oldPt = rect.tl();
	Point direct_newPt =searchRect.tl()+maxPt;
	Point direct_shifft = direct_newPt-direct_oldPt;
	/***********************************************************************/
	return direct_shifft;
}

Point addModel2::calDirect2()
{
	//计算导向模板偏移
	/***********************************************************************/
	Mat SearchRegion(m_zoomCtrl.m_img,p_Model->getDModelSearchRect2());
	Mat directModel = p_Model->getDModel2();
	Mat directResult;
	if(SearchRegion.empty()||directModel.empty())
		return Point(0,0);
	else
		matchTemplate(SearchRegion,directModel,directResult,CV_TM_CCOEFF_NORMED);

	double maxValue;
	cv::Point2i maxPt;
	minMaxLoc(directResult,0,&maxValue,0,&maxPt);

	Rect searchRect = p_Model->getDModelSearchRect2();
	Rect rect = p_Model->getDModelRect2();
	Point direct_oldPt = rect.tl();
	Point direct_newPt =searchRect.tl()+maxPt;
	Point direct_shifft = direct_newPt-direct_oldPt;
	/***********************************************************************/
	return direct_shifft;
}

Mat addModel2::getModelFromID(Model * model,int ID)
{
	if(ID>1000&&ID<2000) //正模板
	{
		ID=ID-1000;
		if((model->m_pModels).size()>=ID)
			return model->m_pModels[ID];
		else 
			return Mat();
	}

	else if(ID>2000&&ID<3000)//负模板
	{
		ID=ID-2000;
		if((model->m_pModels).size()>=ID)
			return model->m_nModels[ID];
		else 
			return Mat();
	}
	else 
		return Mat();


}

Rect addModel2::getModelRectFromID(Model * model,int ID)
{
	if(ID>1000&&ID<2000) //正模板
	{
		ID=ID-1000;
		if((model->m_pModels_Rects).size()>=ID)
			return model->m_pModels_Rects[ID-1];
		else if(model->m_pModels_Rects.size()>0)
			return model->m_pModels_Rects[0];
		else if(model->m_nModels_Rects.size()>0)
			return model->m_nModels_Rects[0];
		else
			return Rect(0,0,0,0);
	}

	else if(ID>2000&&ID<3000)//负模板
	{
		ID=ID-2000;
		if((model->m_nModels_Rects).size()>=ID)
			return model->m_nModels_Rects[ID-1];
		else if(model->m_nModels_Rects.size()>0)
			return model->m_nModels_Rects[0];
		else if(model->m_pModels_Rects.size()>0)
			return model->m_pModels_Rects[0];
		else
			return Rect(0,0,0,0);
	}
	else if(ID==1)
	{
		return model->Search_rect;
	}
	else if(ID==100)
	{
		return model->getDModelRect();
	}
	else if(ID==101)
	{
		return model->getDModelRect2();
	}

	else
		return Rect(0,0,0,0);
}

void addModel2::OnBnClickedCheck2()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK2);
	int state = pBtn->GetCheck();


}

Rect amplifyRrect(Rect rect,double m_factor,double f_x,double f_y)
{
	if(f_x==0&&f_y==0)
	{
		int height =m_factor*rect.height;
		int width = m_factor*rect.width;
		assert(height>=0&&width>=0);
		Point pt_mid((rect.x+rect.width/2),(rect.y+rect.height/2));

		int pt_x = pt_mid.x-width/2;
		int pt_y = pt_mid.y-height/2;
		//if(pt_x<0) pt_x=0;
		//if(pt_y<0) pt_y=0;

		int pt_x2 = pt_mid.x+width/2;
		int pt_y2 = pt_mid.y+height/2;
		/*if(pt_x2>m_zoomCtrl.m_img.cols) pt_x2=m_zoomCtrl.m_img.cols;
		if(pt_y2>m_zoomCtrl.m_img.rows) pt_y2=m_zoomCtrl.m_img.rows;*/

		Rect newRect(Point(pt_x,pt_y),Point(pt_x2,pt_y2));
		return newRect;
	}
	else
	{
		int height =rect.height+f_y;
		int width = rect.width+f_x;
		assert(height>=0&&width>=0);
		Point pt_mid((rect.x+rect.width/2),(rect.y+rect.height/2));

		int pt_x = pt_mid.x-width/2;
		int pt_y = pt_mid.y-height/2;
		if(pt_x<0) pt_x=0;
		if(pt_y<0) pt_y=0;

		int pt_x2 = pt_mid.x+width/2;
		int pt_y2 = pt_mid.y+height/2;
		/*if(pt_x2>m_zoomCtrl.m_img.cols) pt_x2=m_zoomCtrl.m_img.cols;
		if(pt_y2>m_zoomCtrl.m_img.rows) pt_y2=m_zoomCtrl.m_img.rows;*/

		Rect newRect(Point(pt_x,pt_y),Point(pt_x2,pt_y2));
		return newRect;
	}

}

void addModel2::OnStnClickedRadio2()
{
	// TODO: Add your control notification handler code here
}

void addModel2::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nPos = m_slider.GetPos(); 
	CString str;
	str.Format("%d",nPos);
	m_slider_value=str;
	UpdateData(false);

	for (int i = 0; i < p_Model->m_pModels.size(); i++)
	{
		Rect rect = p_Model->getPModelRects(i);
		p_Model->m_pModels_SearchRects[i] = amplifyRrect(rect,0,nPos,nPos);

	}

	for (int i = 0; i < p_Model->m_nModels.size(); i++)
	{
		Rect rect = p_Model->getNModelRects(i);
		p_Model->m_nModels_SearchRects[i] = amplifyRrect(rect,0,nPos,nPos);
	}

	UpdateControl();
}

bool keepRectSafty(Rect rect,Size imgsize)
{
	if(rect.x<0||rect.y<0||rect.x+rect.width>imgsize.width||rect.y+rect.height>imgsize.height)
		return false;
	else
		return true;
}

void addModel2::OnSelchangeCameraid()
{
	int nSel = m_combo_CameraID.GetCurSel();  
	choosePicSource(nSel);
}

LRESULT addModel2::camera_buf_ready(WPARAM wParam, LPARAM lParam)
{
	if(ChoosedSource==-1)
	{

	}
	else if(ChoosedSource==0)
	{
		if(workPool_img.channels()==1)
			cvtColor(workPool_img,work_img,CV_GRAY2RGB);
		m_zoomCtrl.UpdateImage(work_img);


	}
	else if(ChoosedSource==1)
	{
		if(workPool_img2.channels()==1)
			cvtColor(workPool_img2,work_img,CV_GRAY2RGB);
		m_zoomCtrl.UpdateImage(work_img);

	}
	return true;
}

void  addModel2::choosePicSource(int ChoosedSource)
{
	if(ChoosedSource==-1)
	{
		int d= m_combo_CameraID.SetCurSel(-1); 
	}
	else if(ChoosedSource==0)
	{
		m_checkID =0;
		UpdateData(false);
		int d= m_combo_CameraID.SetCurSel(0); 

		work_img = workPool_img;
		if(work_img.channels()==1)
			cvtColor(work_img,work_img,CV_GRAY2RGB);
		m_zoomCtrl.UpdateImage(work_img);
	}
	else if(ChoosedSource==1)
	{

		m_checkID =1;
		UpdateData(false);

		int d= m_combo_CameraID.SetCurSel(1); 

		work_img = workPool_img2;
		if(work_img.channels()==1)
			cvtColor(work_img,work_img,CV_GRAY2RGB);
		m_zoomCtrl.UpdateImage(work_img);
	}

	this->ChoosedSource = ChoosedSource;

	OnChangeEdit2();
}

void addModel2::OnChangeEdit2()
{
	UpdateData(true);
	p_Model->m_cameraID = m_checkID;
}   
