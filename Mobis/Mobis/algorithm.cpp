#include "stdafx.h"
#include"algorithm.h"
//#define LEO_DEBUG

void histMatchTemplate( InputArray _img, InputArray _templ, OutputArray _result );

myAlgorithm_ncc::myAlgorithm_ncc()
{
	p_model=NULL;
	param =0.0;
}

myAlgorithm_ncc::myAlgorithm_ncc(ModelManage * model)
{
	param =0.0;
	p_model=NULL;
	loadModel(model);
	loadParam();
}

myAlgorithm_ncc::~myAlgorithm_ncc()
{
}

void myAlgorithm_ncc::loadModel(ModelManage * model)
{
	p_model=model;
	result.clear();
	result.resize(p_model->m_Models.size());
	clearResult(result);
}

void myAlgorithm_ncc::loadParam()
{
	CString str;
	::GetPrivateProfileStringA("算法参数设置","算法参数1",".//data",str.GetBuffer(MAX_PATH),MAX_PATH,".//setting.ini");
	param = _ttof(str);
}

bool myAlgorithm_ncc::templateMatching(cv::Mat &image)
{
	const int num = p_model->m_Models.size();
	for (int i = 0; i < num; i++)
	{

		Model c_model = p_model->m_Models[i];
		//Mat checkRegion( image,p_model->m_Models[i].m_region);
		//if(p_model->m_Models[i].m_positiveModel.size()==0||p_model->m_Models[i].m_nagetiveModel.size()==0||checkRegion.empty()==true)
		//{
		//	return false;
		//}

		//计算导向模板偏移
		/***********************************************************************/
		Point direct_shifft;
		double maxValue;;
		{
			assert(p_model->m_Models[i].getDModel().empty()!=true);
			Mat SearchRegion(image,p_model->m_Models[i].getDModelSearchRect());
			Mat directModel = p_model->m_Models[i].getDModel();
			Mat directResult;
			matchTemplate(SearchRegion,directModel,directResult,CV_TM_CCOEFF_NORMED);

			//double maxValue;
			cv::Point2i maxPt;
			minMaxLoc(directResult,0,&maxValue,0,&maxPt);

			Rect searchRect = p_model->m_Models[i].getDModelSearchRect();
			Rect rect = p_model->m_Models[i].getDModelRect();
			Point direct_oldPt = rect.tl();
			Point direct_newPt =searchRect.tl()+maxPt;
			direct_shifft = direct_newPt-direct_oldPt;
		}

		/***********************************************************************/



		//计算导向模板偏移2
		/***********************************************************************/
		Point direct_shifft2;
		double maxValue2;
		{
			assert(p_model->m_Models[i].getDModel2().empty()!=true);
			Mat SearchRegion(image,p_model->m_Models[i].getDModelSearchRect2());
			Mat directModel = p_model->m_Models[i].getDModel2();
			Mat directResult;
			matchTemplate(SearchRegion,directModel,directResult,CV_TM_CCOEFF_NORMED);

			//double maxValue;
			cv::Point2i maxPt;
			minMaxLoc(directResult,0,&maxValue2,0,&maxPt);

			Rect searchRect = p_model->m_Models[i].getDModelSearchRect2();
			Rect rect = p_model->m_Models[i].getDModelRect2();
			Point direct_oldPt = rect.tl();
			Point direct_newPt =searchRect.tl()+maxPt;
			direct_shifft2 = direct_newPt-direct_oldPt;
		}

		/***********************************************************************/

		result[i].directValue = maxValue>maxValue2?maxValue:maxValue2;


#ifdef LEO_DEBUG
		//imshow("导向模板",directModel);
		//Rect newRect=rect+direct_shifft;
		//Mat newsmodel(image,newRect);  
		//imshow("重定向导向模板",newsmodel);


		imshow("正模板",p_model->m_Models[i].getPModel(0));
		imshow("负模板",p_model->m_Models[i].getNModel(0));


		Rect  posRect= p_model->m_Models[i].getPModelSearchRects(0);
		Rect  posRect_new = posRect+direct_shifft;
		Mat   pSearchRegion(image,posRect_new);
		imshow("正模板检测区域",pSearchRegion);

		Rect  nagRect= p_model->m_Models[i].getNModelSearchRects(0);
		Rect  nagRect_new = nagRect+direct_shifft2;
		Mat   nSearchRegion(image,nagRect_new);
		imshow("负模板检测区域",nSearchRegion);
		waitKey(50);
#endif


		int pnum = p_model->m_Models[i].m_pModels.size(); 
		result[i].p_results.resize(pnum);
		for (int j = 0; j < pnum; j++)
		{
			Rect  posRect= p_model->m_Models[i].getPModelSearchRects(j);
			Rect  posRect_new = posRect+direct_shifft;
			Mat   pSearchRegion(image,posRect_new);

			cv::matchTemplate(pSearchRegion,p_model->m_Models[i].getPModel(j),result[i].p_results[j],CV_TM_CCOEFF_NORMED);
			//histMatchTemplate(checkRegion,p_model->m_Models[i].m_positiveModel[j],result[i].p_results[j]);
		}
		int nnum = p_model->m_Models[i].m_nModels.size();
		result[i].n_results.resize(nnum);
		for (int j = 0; j <nnum; j++)
		{
			Rect  nagRect= p_model->m_Models[i].getNModelSearchRects(j);
			Rect  nagRect_new = nagRect+direct_shifft2;
			Mat   nSearchRegion(image,nagRect_new);

			cv::matchTemplate(nSearchRegion,p_model->m_Models[i].getNModel(j),result[i].n_results[j],CV_TM_CCOEFF_NORMED); 
			//histMatchTemplate(checkRegion,p_model->m_Models[i].m_nagetiveModel[j],result[i].n_results[j]); 
		}

		double pmax = -1;
		cv::Point2i pmax_pt(0,0);
		for (int j = 0; j < p_model->m_Models[i].m_pModels.size(); j++)
		{
			double maxValue;
			cv::Point2i maxPt;
			minMaxLoc(result[i].p_results[j],0,&maxValue,0,&maxPt);
			if(pmax<maxValue)
			{
				pmax = maxValue;
				pmax_pt = maxPt;
			}
		}
		result[i].p_max = pmax;
		result[i].p_max_pt = pmax_pt;



		double nmax = -1;
		cv::Point2i nmax_pt(0,0);
		for (int j = 0; j < p_model->m_Models[i].m_nModels.size(); j++)
		{
			double maxValue;
			cv::Point2i maxPt;
			minMaxLoc(result[i].n_results[j],0,&maxValue,0,&maxPt);

			if(nmax<maxValue)
			{
				nmax = maxValue;
				nmax_pt = maxPt;
			}
		}
		result[i].n_max =nmax;
		result[i].n_max_pt = nmax_pt;

		double minGap=0.85;
		if (result[i].p_max>result[i].n_max&&result[i].p_max-result[i].n_max>minGap)
		{
			result[i].result=1;
		}
		else
			result[i].result=0;
	}

	return true;

}

vector<int> myAlgorithm_ncc::getValueResult()
{
	vector<int> r;
	for (int i = 0; i < result.size(); i++)
	{
		int temp = result[i].result;
		r.push_back(temp);
	}
	return r;
}

vector<myAlgorithm_ncc::myresult> myAlgorithm_ncc::getAllResult()
{
	return result;
}

void histMatchTemplate( InputArray _img, InputArray _templ, OutputArray _result )
{


	Mat img = _img.getMat(), templ = _templ.getMat();
	if( img.rows < templ.rows || img.cols < templ.cols )
		std::swap(img, templ);

	if( img.channels()==3)
		cvtColor(img,img,CV_RGB2GRAY);
	if( templ.channels()==3)
		cvtColor(templ,templ,CV_RGB2GRAY);

	CV_Assert( (img.depth() == CV_8U || img.depth() == CV_32F) &&
		img.type() == templ.type() );

	CV_Assert( img.rows >= templ.rows && img.cols >= templ.cols);

	Size corrSize(img.cols - templ.cols + 1, img.rows - templ.rows + 1);
	_result.create(corrSize, CV_32F);
	Mat result = _result.getMat();



	CvHistogram *hist_src;
	{//计算二维直方图
		int dims = 1;
		int size[] = {64}; // 这个地方不要取的太大!
		float range[] = {0,256};
		float *ranges[] = {range};
		hist_src = cvCreateHist(dims,size,CV_HIST_ARRAY,ranges);
		IplImage temp = templ;
		IplImage *ptemp = &temp;
		cvCalcHist(&ptemp,hist_src);
		cvNormalizeHist(hist_src,1);
	}


	CvSize patch_size = cvSize (templ.cols,templ.rows);  
	IplImage  ipl_img = img;
	IplImage *p_ipl_img = &ipl_img;
	IplImage *p_ipl_imgs[] ={p_ipl_img};

	IplImage  ipl_result =  result;
	cvCalcBackProjectPatch (p_ipl_imgs, &ipl_result, patch_size, hist_src, CV_COMP_CORREL, 1);  
}

bool myAlgorithm_ncc::templateMatching(vector<cv::Mat> images)
{
	int modelNum = p_model->m_Models.size();
	int maxCamID=-1;
	for (int i = 0; i < modelNum; i++)
	{
		if(maxCamID<p_model->m_Models[i].m_cameraID)
			maxCamID = 	p_model->m_Models[i].m_cameraID;
	}
	//assert((maxCamID+1)<=images.size());







	for (int i = 0; i < modelNum; i++)
	{

		Model c_model = p_model->m_Models[i];
		Mat image;
		if((maxCamID+1)<=images.size())
		{
			image =images[c_model.m_cameraID];;
			if(image.empty())
			{
				//MessageBoxA("不存在图像供模型 检测");
				continue;
			}
		}
		else
		{
			continue;
		}




		//Mat checkRegion( image,p_model->m_Models[i].m_region);
		//if(p_model->m_Models[i].m_positiveModel.size()==0||p_model->m_Models[i].m_nagetiveModel.size()==0||checkRegion.empty()==true)
		//{
		//	return false;
		//}

		//计算导向模板偏移
		/***********************************************************************/
		Point direct_shifft;
		double maxValue;;
		{
			assert(p_model->m_Models[i].getDModel().empty()!=true);
			Mat SearchRegion(image,p_model->m_Models[i].getDModelSearchRect());
			Mat directModel = p_model->m_Models[i].getDModel();
			Mat directResult;
			uniformChannelFromModel(SearchRegion,directModel);
			matchTemplate(SearchRegion,directModel,directResult,CV_TM_CCOEFF_NORMED);

			//double maxValue;
			cv::Point2i maxPt;
			minMaxLoc(directResult,0,&maxValue,0,&maxPt);

			Rect searchRect = p_model->m_Models[i].getDModelSearchRect();
			Rect rect = p_model->m_Models[i].getDModelRect();
			Point direct_oldPt = rect.tl();
			Point direct_newPt =searchRect.tl()+maxPt;
			direct_shifft = direct_newPt-direct_oldPt;
		}

		/***********************************************************************/



		//计算导向模板偏移2
		/***********************************************************************/
		Point direct_shifft2;
		double maxValue2;
		{
			assert(p_model->m_Models[i].getDModel2().empty()!=true);
			Mat SearchRegion(image,p_model->m_Models[i].getDModelSearchRect2());
			Mat directModel = p_model->m_Models[i].getDModel2();
			Mat directResult;
			uniformChannelFromModel(SearchRegion,directModel);
			matchTemplate(SearchRegion,directModel,directResult,CV_TM_CCOEFF_NORMED);

			//double maxValue;
			cv::Point2i maxPt;
			minMaxLoc(directResult,0,&maxValue2,0,&maxPt);

			Rect searchRect = p_model->m_Models[i].getDModelSearchRect2();
			Rect rect = p_model->m_Models[i].getDModelRect2();
			Point direct_oldPt = rect.tl();
			Point direct_newPt =searchRect.tl()+maxPt;
			direct_shifft2 = direct_newPt-direct_oldPt;
		}

		/***********************************************************************/

		result[i].directValue = maxValue>maxValue2?maxValue:maxValue2;


#ifdef LEO_DEBUG
		//imshow("导向模板",directModel);
		//Rect newRect=rect+direct_shifft;
		//Mat newsmodel(image,newRect);  
		//imshow("重定向导向模板",newsmodel);


		imshow("正模板",p_model->m_Models[i].getPModel(0));
		imshow("负模板",p_model->m_Models[i].getNModel(0));


		Rect  posRect= p_model->m_Models[i].getPModelSearchRects(0);
		Rect  posRect_new = posRect+direct_shifft;
		Mat   pSearchRegion(image,posRect_new);
		imshow("正模板检测区域",pSearchRegion);

		Rect  nagRect= p_model->m_Models[i].getNModelSearchRects(0);
		Rect  nagRect_new = nagRect+direct_shifft2;
		Mat   nSearchRegion(image,nagRect_new);
		imshow("负模板检测区域",nSearchRegion);
		waitKey(50);
#endif


		int pnum = p_model->m_Models[i].m_pModels.size(); 
		result[i].p_results.resize(pnum);
		for (int j = 0; j < pnum; j++)
		{
			Rect  posRect= p_model->m_Models[i].getPModelSearchRects(j);
			Rect  posRect_new = posRect+direct_shifft;
			Mat   pSearchRegion(image,posRect_new);

			uniformChannelFromModel(pSearchRegion,p_model->m_Models[i].getPModel(j));
			cv::matchTemplate(pSearchRegion,p_model->m_Models[i].getPModel(j),result[i].p_results[j],CV_TM_CCOEFF_NORMED);
			//histMatchTemplate(pSearchRegion,p_model->m_Models[i].getPModel(j),result[i].p_results[j]);
		}
		int nnum = p_model->m_Models[i].m_nModels.size();
		result[i].n_results.resize(nnum);
		for (int j = 0; j <nnum; j++)
		{
			Rect  nagRect= p_model->m_Models[i].getNModelSearchRects(j);
			Rect  nagRect_new = nagRect+direct_shifft2;
			Mat   nSearchRegion(image,nagRect_new);

			uniformChannelFromModel(nSearchRegion,p_model->m_Models[i].getNModel(j));
			cv::matchTemplate(nSearchRegion,p_model->m_Models[i].getNModel(j),result[i].n_results[j],CV_TM_CCOEFF_NORMED); 
			//histMatchTemplate(nSearchRegion,p_model->m_Models[i].getNModel(j),result[i].n_results[j]); 
		}

		double pmax = -1;
		cv::Point2i pmax_pt(0,0);
		for (int j = 0; j < p_model->m_Models[i].m_pModels.size(); j++)
		{
			double maxValue;
			cv::Point2i maxPt;
			minMaxLoc(result[i].p_results[j],0,&maxValue,0,&maxPt);
			if(pmax<maxValue)
			{
				pmax = maxValue;
				pmax_pt = maxPt;
			}
		}
		result[i].p_max = pmax;
		result[i].p_max_pt = pmax_pt;



		double nmax = -1;
		cv::Point2i nmax_pt(0,0);
		for (int j = 0; j < p_model->m_Models[i].m_nModels.size(); j++)
		{
			double maxValue;
			cv::Point2i maxPt;
			minMaxLoc(result[i].n_results[j],0,&maxValue,0,&maxPt);

			if(nmax<maxValue)
			{
				nmax = maxValue;
				nmax_pt = maxPt;
			}
		}
		result[i].n_max =nmax;
		result[i].n_max_pt = nmax_pt;


		double minGap=param;
		if (result[i].p_max>result[i].n_max&&result[i].p_max-result[i].n_max>minGap)
		{
			result[i].result=1;
		}
		else
			result[i].result=0;
	}

	return true;

}

void myAlgorithm_ncc::clearResult(vector< myresult> &result)
{
	int resultNum = result.size();
	for (int i = 0; i < resultNum; i++)
	{
		result[i].directValue =0;
		result[i].p_max =0;
		result[i].n_max=0;
		result[i].p_max_pt=Point(-1,-1);
		result[i].n_max_pt=Point(-1,-1);
		result[i].result=-1;
	}
}

void myAlgorithm_ncc::uniformChannelFromModel(Mat &image,Mat &temp)
{
	int channels_temp = temp.channels();
	int channels_image = image.channels();
	if(channels_temp!=channels_image)
	{
		if(channels_temp==1)
			cvtColor(image,image,CV_BGR2GRAY);
		else if(channels_temp==3)
			cvtColor(image,image,CV_GRAY2RGB);
	}
}