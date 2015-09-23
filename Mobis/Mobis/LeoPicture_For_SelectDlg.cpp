#include "stdafx.h"
#include "LeoPicture_For_SelectDlg.h"

LeoPicture_For_SelectDlg::LeoPicture_For_SelectDlg()
{
	ID=0;
}

LeoPicture_For_SelectDlg::~LeoPicture_For_SelectDlg()
{

}

void LeoPicture_For_SelectDlg::Draw(CDC *pDC)
{
	if (m_img.empty())
		return;

	cv::Mat showMat=m_img.clone();
	for (int i = 0; i < models.size(); i++)
	{
		if(ID == models[i].getCameraID())
		{
			int a = (models)[i].getSearchrect().width;
			int b = RectRoi.width;
			if(a==0) a=1;
			int w = b/a *3/23;
			if(w>4)
				w=4;
			else if(w<1)
				w=1;


			cv::putText(showMat,(models)[i].getDescribe(),
				cv::Point((models)[i].getSearchrect().x,(models)[i].getSearchrect().y),FONT_HERSHEY_DUPLEX,1.5,Scalar(0,255,255));
			cv::rectangle(showMat,(models)[i].getSearchrect(),cv::Scalar(0,255,0),w);
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
	

	if(m_RectTracker!=NULL)
		m_RectTracker->Draw(pDC);
	//ReleaseDC( pDC );
}

void LeoPicture_For_SelectDlg::AddRelatedModel(Model mod)
{
	models.push_back(mod);
	OnPaint();
}

