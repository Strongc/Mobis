#include "stdafx.h"
#include"Model.h"


//void writeModel2File(string filename,Model &model)
//{
//	FileStorage fs(filename, FileStorage::WRITE);
//	fs<<"describe"<<model.getDescribe();
//	fs<<"region"<<model.getRegion();
//	int positive_num= model.m_positiveModel.size();
//	int Nagetive_num= model.m_nagetiveModel.size();
//	fs<<"positive_num"<<positive_num;
//	fs<<"Nagetive_num"<<Nagetive_num;
//
//	for(int i=0;i<positive_num;i++)
//	{
//		char name[30];
//		sprintf(name,"positive_Image_%02d",i);	
//		fs<<name<<model.m_positiveModel[i];
//	}
//
//	for(int i=0;i<Nagetive_num;i++)
//	{
//		char name[30];
//		sprintf(name,"Nagetive_Image_%02d",i);	
//		fs<<name<<model.m_positiveModel[i];
//	}
//
//	fs.release(); 
//}
//
//
//void readModel2File(string filename,Model &model)
//{
//	FileStorage fs;
//	fs.open(filename, FileStorage::READ);
//	string describe = (string)fs["describe"];
//	model.setDescribe(describe);   
//
//	Rect r;
//	fs["region"]>>r;
//	model.setRegion(r);
//
//	int positive_num = (int) fs["positive_num"];
//	int Nagetive_num = (int) fs["Nagetive_num"];
//
//	for (int i = 0; i < positive_num; i++)
//	{
//		char name[30];
//		sprintf(name,"positive_Image_%02d",i);
//		Mat p ;
//		fs[name]>>p;
//		model.addPosModel(p);
//	}
//
//	for (int i = 0; i < Nagetive_num; i++)
//	{
//		char name[30];
//		sprintf(name,"Nagetive_Image_%02d",i);
//		Mat p ;
//		fs[name]>>p;
//		model.addPosModel(p);
//	}
//
//
//	fs.release(); 
//}

