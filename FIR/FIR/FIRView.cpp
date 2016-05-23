// FIRView.cpp : CFIRView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_APP_EXIT, &CFIRView::OnAppExit)
END_MESSAGE_MAP()

// CFIRView 构造/析构

CFIRView::CFIRView()
{
	// TODO: 在此处添加构造代码
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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFIRView 绘制

void CFIRView::OnDraw(CDC* pDC)
{
	CFIRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	DrawMap(pDC, pDoc);
	DrawChese(pDC, pDoc);
	DrawCurPlayer(pDC,pDoc);
}


// CFIRView 打印

BOOL CFIRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFIRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CFIRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


void CFIRView::DrawMap(CDC* pDC,CFIRDoc* pDoc)
{

	//画背景
	pDC->FillRect(BackgroundFrame,BackBrush);

	//画内外框
	int width = (int)(len/5);
	pDC->Rectangle(startx-halflen-width,starty-halflen-width,startx+n*len-halflen+width,starty+n*len-halflen+width);	//外框
	pDC->FillRect(InnerMapFrame,MapBrush);		//内框

	//画竖线
	int start = starty-halflen;
	int end = starty+n*len-halflen;
	for(int i=startx;i<startx+n*len;i += len)
	{
		pDC->MoveTo(i,start);
		pDC->LineTo(i,end);
	}
	//画横线
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
	CString buf("执棋：");
	pDC->TextOutW(startx+(n+1)*len-20,starty+2*len-10,buf);
		
	if(pDoc->curPlayer==1)
		DrawChese1(pDC,2,18);
	else
		DrawChese2(pDC,2,18);
}




// CFIRView 诊断

#ifdef _DEBUG
void CFIRView::AssertValid() const
{
	CView::AssertValid();
}

void CFIRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFIRDoc* CFIRView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFIRDoc)));
	return (CFIRDoc*)m_pDocument;
}
#endif //_DEBUG


// CFIRView 消息处理程序

void CFIRView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
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
	// TODO: 在此添加命令处理程序代码
	AfxGetMainWnd()->SendMessage(WM_CLOSE); 
}
