// FIRView.cpp : CFIRView ���ʵ��
//

#include "stdafx.h"
#include "FIR.h"

#include "FIRDoc.h"
#include "FIRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFIRView

IMPLEMENT_DYNCREATE(CFIRView, CView)

BEGIN_MESSAGE_MAP(CFIRView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_APP_EXIT, &CFIRView::OnAppExit)
END_MESSAGE_MAP()

// CFIRView ����/����

CFIRView::CFIRView()
{
	// TODO: �ڴ˴���ӹ������
	startx=400;
	starty=150;
	rad=12;
	halflen=15;
	len=halflen*2;

	InnerMapFrame = new CRect(startx-halflen,starty-halflen,startx+n*len-halflen,starty+n*len-halflen);
	BackgroundFrame = new CRect(0,0,60*len,30*len);
	CheseManRgn = new CRgn();

					
	BackBrush = new CBrush(7,RGB(10,0,191));
	BlackManBrush = new CBrush(RGB(0,0,0));	
	WhiteManBrush = new CBrush(RGB(255,255,255));
	WinBrush = new CBrush(RGB(238,250,22));
	MapBrush = new CBrush(7,RGB(87,77,0));
}

CFIRView::~CFIRView()
{
	delete InnerMapFrame;
	delete BackgroundFrame;
	delete CheseManRgn;

	delete BackBrush;
	delete BlackManBrush;
	delete WhiteManBrush;
	delete WinBrush;
	delete MapBrush;
}

BOOL CFIRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFIRView ����

void CFIRView::OnDraw(CDC* pDC)
{
	CFIRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	DrawMap(pDC, pDoc);
	DrawChese(pDC, pDoc);
	DrawCurPlayer(pDC,pDoc);
}


// CFIRView ��ӡ

BOOL CFIRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFIRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFIRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


void CFIRView::DrawMap(CDC* pDC,CFIRDoc* pDoc)
{

	//������
	pDC->FillRect(BackgroundFrame,BackBrush);

	//�������
	int width = (int)(len/5);
	pDC->Rectangle(startx-halflen-width,starty-halflen-width,startx+n*len-halflen+width,starty+n*len-halflen+width);	//���
	pDC->FillRect(InnerMapFrame,MapBrush);		//�ڿ�

	//������
	int start = starty-halflen;
	int end = starty+n*len-halflen;
	for(int i=startx;i<startx+n*len;i += len)
	{
		pDC->MoveTo(i,start);
		pDC->LineTo(i,end);
	}
	//������
	start = startx-halflen;
	end = startx+n*len-halflen;
	for(int i=starty;i<starty+n*len;i += len)
	{
		pDC->MoveTo(start,i);
		pDC->LineTo(end,i);
	}
}
void CFIRView::DrawChese(CDC* pDC,CFIRDoc* pDoc)
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			switch(pDoc->Chese[i][j])
			{
			case 1:
				DrawChese1(pDC,i,j);break;
			case 2:
				DrawChese2(pDC,i,j);break;
			case 3:
				DrawChese1Win(pDC,i,j);break;
			case 4:
				DrawChese2Win(pDC,i,j);break;
			}
		}
}
void CFIRView::DrawChese1(CDC* pDC,int i,int j)
{
	int x = startx+j*len;
	int y = starty+i*len;
	
	CheseManRgn->Detach();
	CheseManRgn->CreateEllipticRgn(x-rad,y-rad,x+rad,y+rad);
	pDC->FillRgn(CheseManRgn,BlackManBrush);
}
void CFIRView::DrawChese2(CDC* pDC,int i,int j)
{
	int x = startx+j*len;
	int y = starty+i*len;
	
	CheseManRgn->Detach();
	CheseManRgn->CreateEllipticRgn(x-rad,y-rad,x+rad,y+rad);
	pDC->FillRgn(CheseManRgn,WhiteManBrush);
}
void CFIRView::DrawChese1Win(CDC* pDC,int i,int j)
{
	int x = startx+j*len;
	int y = starty+i*len;

	int width = 4;
	CheseManRgn->Detach();
	CheseManRgn->CreateEllipticRgn(x-rad-width,y-rad-width,x+rad+width,y+rad+width);
	pDC->FillRgn(CheseManRgn,WinBrush);	
	DrawChese1(pDC,i,j);
}
void CFIRView::DrawChese2Win(CDC* pDC,int i,int j)
{
	int x = startx+j*len;
	int y = starty+i*len;

	int width = 4;
	CheseManRgn->Detach();
	CheseManRgn->CreateEllipticRgn(x-rad-width,y-rad-width,x+rad+width,y+rad+width);
	pDC->FillRgn(CheseManRgn,WinBrush);	
	DrawChese2(pDC,i,j);
}
bool CFIRView::FindManLocation(CPoint pt,int& i,int& j)
{
	if(pt.x<startx-halflen||pt.x>startx+n*len-halflen||pt.y<starty-halflen||pt.y>starty+n*len-halflen)
		return false;
	i = (pt.y-starty+halflen)/len;
	j = (pt.x-startx+halflen)/len;	
	return true;
}
void CFIRView::DrawCurPlayer(CDC* pDC,CFIRDoc* pDoc)
{
	CString buf("ִ�壺");
	pDC->TextOutW(startx+(n+1)*len-20,starty+2*len-10,buf);
		
	if(pDoc->curPlayer==1)
		DrawChese1(pDC,2,18);
	else
		DrawChese2(pDC,2,18);
}




// CFIRView ���

#ifdef _DEBUG
void CFIRView::AssertValid() const
{
	CView::AssertValid();
}

void CFIRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFIRDoc* CFIRView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFIRDoc)));
	return (CFIRDoc*)m_pDocument;
}
#endif //_DEBUG


// CFIRView ��Ϣ�������

void CFIRView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CFIRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	int i,j;
	if(FindManLocation(point,i,j))
		pDoc->Move(i,j);

	CView::OnLButtonUp(nFlags, point);
}

void CFIRView::OnAppExit()
{
	// TODO: �ڴ���������������
	AfxGetMainWnd()->SendMessage(WM_CLOSE); 
}
