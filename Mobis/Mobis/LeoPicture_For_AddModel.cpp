
//---------------------------------------------------------------------
#include "stdafx.h"
#include "LeoPicture_For_AddModel.h"
#include "CvvImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//---------------------------------------------------------------------
LeoPicture_For_AddModel::LeoPicture_For_AddModel()
{


}

//---------------------------------------------------------------------
LeoPicture_For_AddModel::~LeoPicture_For_AddModel()
{

}

void LeoPicture_For_AddModel::Draw(CDC *pDC)
{
	if (m_img.empty())
		return;

	cv::Mat showMat=m_img.clone();
	//for (int i = 0; i < ptr_models.size(); i++)
	//{
	//	//int a = ptr_models[i]->m_region.width;
	//	//int b = RectRoi.width;



	//	cv::putText(showMat,ptr_models[i]->m_Describe,cv::Point(ptr_models[i]->m_region.x,ptr_models[i]->m_region.y),CV_FONT_HERSHEY_SIMPLEX,1.5,Scalar(0,0,255));
	//	cv::rectangle(showMat,ptr_models[i]->m_region,cv::Scalar(0,0,255),1);
	//	if(ptr_models[i]->getSmallRegion().area()>0)
	//	{
	//		cv::rectangle(showMat,ptr_models[i]->getSmallRegion(),cv::Scalar(0,255,255),1);
	//	}
	//}


	cv::Mat showImage(showMat,RectRoi);

	CRect myrect;
	GetClientRect(&myrect);	//取得客户区尺寸

	IplImage* img=&(IplImage)showImage;		//将图像转换为IplImage格式，共用同一个内存（浅拷贝）
	CvvImage iimg;								//创建一个CvvImage对象
	iimg.CopyOf(img);

	HDC hDC=pDC->GetSafeHdc();	
	iimg.DrawToHDC(hDC,&myrect);


	if(m_RectTracker!=NULL)
		m_RectTracker->Draw(pDC);


}


void LeoPicture_For_AddModel::AddRelatedModel(Model mod)
{
	models.push_back(mod);
	OnPaint();
}

