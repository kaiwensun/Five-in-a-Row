// FIRView.h : CFIRView 类的接口
//


#pragma once


class CFIRView : public CView
{
protected: // 仅从序列化创建
	CFIRView();
	DECLARE_DYNCREATE(CFIRView)

// 属性
public:
	CFIRDoc* GetDocument() const;
	int startx,starty;	//棋盘起始坐标
	int rad;			//棋子半径
	int halflen;		//棋盘小格的一半边长
	int len;			//棋盘小格边长

	//图形
	CRect* InnerMapFrame;
	CRect* BackgroundFrame;
	CRgn* CheseManRgn;


	
	//刷子
	CBrush* BlackManBrush;
	CBrush* BackBrush;
	CBrush* WhiteManBrush;
	CBrush* WinBrush;
	CBrush* MapBrush;

// 操作
public:
	void DrawMap(CDC* pDC,CFIRDoc* pDoc);
	void DrawChese(CDC* pDC,CFIRDoc* pDoc);
	void DrawChese1(CDC* pDC,int i,int j);
	void DrawChese2(CDC* pDC,int i,int j);
	void DrawChese1Win(CDC* pDC,int i,int j);
	void DrawChese2Win(CDC* pDC,int i,int j);
	void DrawCurPlayer(CDC* pDC,CFIRDoc* pDoc);

	bool FindManLocation(CPoint pt,int& i,int& j);
	
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CFIRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAppExit();
};

#ifndef _DEBUG  // FIRView.cpp 中的调试版本
inline CFIRDoc* CFIRView::GetDocument() const
   { return reinterpret_cast<CFIRDoc*>(m_pDocument); }
#endif

