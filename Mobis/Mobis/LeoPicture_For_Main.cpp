#include "stdafx.h"
#include "LeoPicture_For_Main.h"


LeoPicture_For_Main::LeoPicture_For_Main(void)
{
}

LeoPicture_For_Main::~LeoPicture_For_Main(void)
{

}


void LeoPicture_For_Main::Draw(CDC *pDC)
{
	if (m_img.empty())
		return;

	cv::Mat showMat=m_img.clone();
	if(p_ModelManage!=NULL)
	{
		for (int i = 0; i < p_ModelManage->m_Models.size(); i++)
		{
			if(ID == p_ModelManage->m_Models[i].m_cameraID)
			{
				int a = (p_ModelManage->m_Models)[i].Search_rect.width;
				int b = RectRoi.width;
				if(a==0) a=1;
				int w = b/a *3/23;
				if(w>3)
					w=3;
				else if(w<1)
					w=1;


				cv::putText(showMat,(p_ModelManage->m_Models)[i].m_Describe,
					cv::Point((p_ModelManage->m_Models)[i].Search_rect.x,(p_ModelManage->m_Models)[i].Search_rect.y),FONT_HERSHEY_DUPLEX,1.5,Scalar(0,255,255));
				if(states.size()==p_ModelManage->m_Models.size())
				{
					if(states[i])
						cv::rectangle(showMat,(p_ModelManage->m_Models)[i].Search_rect,cv::Scalar(0,255,0),w);
					else
						cv::rectangle(showMat,(p_ModelManage->m_Models)[i].Search_rect,cv::Scalar(0,0,255),w);
				}
				else
					cv::rectangle(showMat,(p_ModelManage->m_Models)[i].Search_rect,cv::Scalar(0,255,255),w);
			}

		}
	}
	
	cv::Mat showImage(showMat,RectRoi);

	CRect myrect;
	GetClientRect(&myrect);	//取得客户区尺寸

	IplImage* img=&(IplImage)showImage;		//将图像转换为IplImage格式，共用同一个内存（浅拷贝）
	CvvImage iimg;								//创建一个CvvImage对象
	iimg.CopyOf(img);

	HDC hDC=pDC->GetSafeHdc();	
	iimg.DrawToHDC(hDC,&myrect);
	ReleaseDC( pDC );

	if(m_RectTracker!=NULL)
		m_RectTracker->Draw(pDC);
}

