// FIRDoc.cpp : CFIRDoc ���ʵ��
//

#include "stdafx.h"
#include "FIR.h"

#include "FIRDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CFIRDoc

IMPLEMENT_DYNCREATE(CFIRDoc, CDocument)

BEGIN_MESSAGE_MAP(CFIRDoc, CDocument)
	ON_COMMAND(ID_32773, &CFIRDoc::Regret)
	ON_COMMAND(ID_32774, &CFIRDoc::MenuRegret)
	ON_COMMAND(ID_32776, &CFIRDoc::MenuSwitchHand)
	ON_COMMAND(ID_32777, &CFIRDoc::MenuRestart)
	ON_COMMAND(ID_EDIT_UNDO, &CFIRDoc::OnEditUndo)
END_MESSAGE_MAP()


// CFIRDoc ����/����

CFIRDoc::CFIRDoc()
{
	// TODO: �ڴ����һ���Թ������
	firstHand=1;
	curPlayer = firstHand;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			Chese[i][j] = 0;
	stepCnt=0;
}

CFIRDoc::~CFIRDoc()
{
}

BOOL CFIRDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CFIRDoc ���л�

void CFIRDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}
//	����

void CFIRDoc::Move(int i,int j)
{
	if(Chese[i][j]!=0)
		return;	
	
	Chese[i][j] = curPlayer;
	step[stepCnt].i=i;
	step[stepCnt].j=j;
	stepCnt++;
	if(Win(i,j))
	UpdateAllViews(NULL);
	curPlayer = (curPlayer==1?2:1);
	UpdateAllViews(NULL);
}
bool CFIRDoc::Win(int i,int j)
{
	int a,b;
	int cnt=0;
	//��������
	for(a=(i<5?0:i-4);a<i+5&&a<15;a++)
	{
		cnt = (Chese[a][j]==curPlayer?cnt+1:0);
		if(cnt==5)
		{
			MakePlayerWin(a-4,j,0);
			return true;
		}
	}
	//��������
	cnt=0;
	for(b=(j<5?0:j-4);b<j+5&&b<15;b++)
	{
		cnt = (Chese[i][b]==curPlayer?cnt+1:0);
		if(cnt==5)
		{
			MakePlayerWin(i,b-4,1);
			return true;
		}
	}
	//������������
	a=i;b=j;
	cnt=0;
	for(int k=0;k<4;k++)
	{
		if(a==0||b==0)
			break;
		a--;
		b--;
	}
	for(int k=0;k<9 && a<15 && b<15 && i+5>a;k++,a++,b++)
	{
		cnt = (Chese[a][b]==curPlayer?cnt+1:0);
		if(cnt==5)
		{
			MakePlayerWin(a-4,b-4,2);
			return true;
		}
	}
	//������������
	a=i;b=j;
	cnt=0;
	for(int k=0;k<4;k++)
	{
		if(a==14||b==0)
			break;
		a++;
		b--;
	}
	for(int k=0;k<9 && a>=0 && b<15 && a>i-5;k++,a--,b++)
	{
		cnt = (Chese[a][b]==curPlayer?cnt+1:0);
		if(cnt==5)
		{
			MakePlayerWin(a+4,b-4,3);
			return true;
		}
	}
	return false;
}
void CFIRDoc::MakePlayerWin(int i,int j,int direct)
{
	switch(direct)
	{
	case 0:	//��
		{
			for(int k=i;k<i+5;k++)
				Chese[k][j]=curPlayer+2;
			break;
		}
	case 1:	//��
		{
			for(int k=j;k<j+5;k++)
				Chese[i][k]=curPlayer+2;
			break;
		}
	case 2:	//����������
		{
			for(int k=0;k<5;k++)
				Chese[i+k][j+k]=curPlayer+2;
			break;
		}
	case 3:	//����������
		{
			for(int k=0;k<5;k++)
				Chese[i-k][j+k]=curPlayer+2;
		}
	}
	OccupyBlank();
}
void CFIRDoc::OccupyBlank()
{
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
			if(Chese[i][j]==0)
				Chese[i][j]=-1;
}
void CFIRDoc::Restart()
{
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
			Chese[i][j]=0;
	curPlayer=firstHand;
	stepCnt=0;
	UpdateAllViews(NULL);
}
	
void CFIRDoc::Regret()
{
	if(stepCnt==0)
		return;
	Chese[step[stepCnt-1].i][step[stepCnt-1].j]=0;
	stepCnt--;
	curPlayer = (curPlayer==1?2:1);
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
		{
			switch(Chese[i][j])
			{
			case -1:
				Chese[i][j]=0;break;
			case 3:
				Chese[i][j]=1;break;
			case 4:
				Chese[i][j]=2;break;
			}
		}
	UpdateAllViews(NULL);
}
void CFIRDoc::SwitchHand()
{
	Restart();
	firstHand = (firstHand==1?2:1);
	curPlayer = firstHand;
	UpdateAllViews(NULL);
}

// CFIRDoc ���

#ifdef _DEBUG
void CFIRDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFIRDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFIRDoc ����

void CFIRDoc::MenuRegret()
{
	// TODO: �ڴ���������������
	Regret();
}

void CFIRDoc::MenuSwitchHand()
{
	// TODO: �ڴ���������������
	SwitchHand();
}
void CFIRDoc::MenuRestart()
{
	// TODO: �ڴ���������������
	Restart();
}

void CFIRDoc::OnEditUndo()
{
	// TODO: �ڴ���������������
	Regret();
}
