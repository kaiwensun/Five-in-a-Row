// FIRDoc.h : CFIRDoc ��Ľӿ�
//


#pragma once


class CFIRDoc : public CDocument
{
protected: // �������л�����
	CFIRDoc();
	DECLARE_DYNCREATE(CFIRDoc)

// ����
public:
	int firstHand;
	int curPlayer;
	int Chese[n][n];	//-1:��Ϸ�ѽ���������ռ��;	0:δ��ռ��;	1:�ѱ����1ռ��;	2:�ѱ����2ռ��;	3:���1�Ѿ�����һ��;	4:���2�Ѿ�����һ��
	struct Step	{int i;int j;} step[n*n];
	int stepCnt;

// ����
public:
	void Move(int i,int j);
	bool Win(int i,int j);
	void MakePlayerWin(int i,int j,int direct);
	void OccupyBlank();
	void Restart();
	void Regret();
	void SwitchHand();

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CFIRDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void MenuRegret();
	afx_msg void MenuSwitchHand();
	afx_msg void MenuRestart();
	afx_msg void OnEditUndo();
};


