// FIR.h : FIR Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

//�����峣�ò���
const int n = 15;		//���̸���

// CFIRApp:
// �йش����ʵ�֣������ FIR.cpp
//

class CFIRApp : public CWinApp
{
public:
	CFIRApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFIRApp theApp;