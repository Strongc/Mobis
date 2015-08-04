#include "Model.h"
#include "opencv.hpp"


using namespace cv;
using namespace std;


class myAlgorithm_ncc
{
public:
	typedef struct _myresult
	{
		double directValue;
		vector<cv::Mat> p_results;//��ģ��ƥ����
		vector<cv::Mat> n_results;//��ģ��ƥ����
		double p_max;
		double n_max;
		cv::Point p_max_pt;
		cv::Point n_max_pt;
		int result;		//���ֵ�ȽϽ��  1����ģ�壬0:��ģ��
	}myresult;

public:
	myAlgorithm_ncc();
	myAlgorithm_ncc(ModelManage * model);
	~myAlgorithm_ncc();

	void loadModel(ModelManage * model);
	bool templateMatching(cv::Mat &image);
	vector<int> getValueResult();
	vector<myresult> getAllResult();
	bool templateMatching(vector<cv::Mat> images);
private:
	ModelManage *p_model;
	vector< myresult> result;


	void clearResult(vector< myresult> &result);
	void uniformChannelFromModel(Mat &image,Mat &temp);
};

