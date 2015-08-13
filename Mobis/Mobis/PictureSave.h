#pragma once
#include"opencv.hpp"
#include<vector>
#include"Model.h"
using namespace cv;
using namespace std;




class PictureSave
{
public:
	PictureSave(void);
	~PictureSave(void);

	int UpdateParm();
	int UpdateModel(ModelManage  *p_ModelManage);
	int savePic(vector<cv::Mat> imgs);
	int savePic(cv::Mat img);
	
private:
	int savePic(cv::Mat img,CString strDate,CString strTime,int index);
	void getDateAndTime(CString&date,CString&time);


	bool openDataBase();
	bool closeDataBase();
	bool openConnection();
	bool closeConnection();
	bool openRecordset();
	bool closeRecordset();

	//�������
	int addPicToDbAndDir(Mat img,CString name,CString dir,CString path,CString addin);
	bool addPicToDB(CString name,CString dir,CString path,CString addin);
	int addPicToDir(Mat img ,CString path);

	//��ѯ
	int getPicNum();					  //��ȡ���ݿⱣ��ͼ������
	int getPicDateNum();				  //��ȡ���ݿⱣ��ͼ������
	double GetFreeSpace_MB(CString dir);  //��ȡĳ���̿��ÿռ�
	bool FreeSpaceMoreThan(double mixSpace);//���ʣ��ռ����mixSpace ��λMB

	//ɾ������
	CString getEarliestDate();
	int deleteDbAndDir(CString strDir);
	bool deleteDBdir(CString strDir);
	void deleteDirectory(CString strDir);

	//ȫ�ִ�ͼת�ֲ�Сͼ  ��С�洢����
	int translatePic(Mat &LargeImg,Mat &SmallImg );
	void All2One(vector<Mat> imgs,Mat &outimg);


	_ConnectionPtr	m_pConnection;
	_RecordsetPtr	m_pRecordset;

	ModelManage  *m_ModelManage;
	int m_PicType;
	int m_dateNum;
public:
	CString m_dataPath;
	int warmspace ;  //���̿ռ�С��200M ������
	int errospace ;	//���̿ռ�С��50M ������
};

