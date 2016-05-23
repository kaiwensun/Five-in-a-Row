// FIRView.h : CFIRView ��Ľӿ�
//


#pragma once


class CFIRView : public CView
{
protected: // �������л�����
	CFIRView();
	DECLARE_DYNCREATE(CFIRView)

// ����
public:
	CFIRDoc* GetDocument() const;
	int startx,starty;	//������ʼ����
	int rad;			//���Ӱ뾶
	int halflen;		//����С���һ��߳�
	int len;			//����С��߳�

	//ͼ��
	CRect* InnerMapFrame;
	CRect* BackgroundFrame;
	CRgn* CheseManRgn;


	
	//ˢ��
	CBrush* BlackManBrush;
	CBrush* BackBrush;
	CBrush* WhiteManBrush;
	CBrush* WinBrush;
	CBrush* MapBrush;

// ����
public:
	void DrawMap(CDC* pDC,CFIRDoc* pDoc);
	void DrawChese(CDC* pDC,CFIRDoc* pDoc);
	void DrawChese1(CDC* pDC,int i,int j);
	void DrawChese2(CDC* pDC,int i,int j);
	void DrawChese1Win(CDC* pDC,int i,int j);
	void DrawChese2Win(CDC* pDC,int i,int j);
	void DrawCurPlayer(CDC* pDC,CFIRDoc* pDoc);

	bool FindManLocation(CPoint pt,int& i,int& j);
	
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CFIRView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAppExit();
};

#ifndef _DEBUG  // FIRView.cpp �еĵ��԰汾
inline CFIRDoc* CFIRView::GetDocument() const
   { return reinterpret_cast<CFIRDoc*>(m_pDocument); }
#endif

