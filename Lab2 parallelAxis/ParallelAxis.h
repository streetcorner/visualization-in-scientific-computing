
// ParallelAxis.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CParallelAxisApp:
// �йش����ʵ�֣������ ParallelAxis.cpp
//

class CParallelAxisApp : public CWinApp
{
public:
	CParallelAxisApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CParallelAxisApp theApp;