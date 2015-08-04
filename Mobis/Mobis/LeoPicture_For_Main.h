#pragma once
#include "LeoPicture.h"
#include"opencv.hpp"
#include "LeoRectTracker.h"
#include"vector"
#include"Model.h"
#include "CvvImage.h"
class LeoPicture_For_Main :	public LeoPicture
{
public:
	LeoPicture_For_Main(void);
	~LeoPicture_For_Main(void);

public:
	virtual void Draw(CDC *pDC);

	ModelManage* p_ModelManage;
	vector<int> states;
	int ID;
};

