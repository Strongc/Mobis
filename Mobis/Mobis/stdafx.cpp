
// stdafx.cpp : source file that includes just the standard includes
// Mobis.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"




int g_CamNum =1;
std::vector<CRITICAL_SECTION>  g_CamBufs(g_CamNum);  //´úÂëÁÙ½çÇø 
std::vector<HANDLE> g_CamAcqs(g_CamNum);
