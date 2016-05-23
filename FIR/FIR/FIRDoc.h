// FIRDoc.h : CFIRDoc 类的接口
//


#pragma once


class CFIRDoc : public CDocument
{
protected: // 仅从序列化创建
	CFIRDoc();
	DECLARE_DYNCREATE(CFIRDoc)

// 属性
public:
	int firstHand;
	int curPlayer;
	int Chese[n][n];	//-1:游戏已结束，不能占领;	0:未被占领;	1:已被玩家1占领;	2:已被玩家2占领;	3:玩家1已经连成一线;	4:玩家2已经连成一线
	struct Step	{int i;int j;} step[n*n];
	int stepCnt;

// 操作
public:
	void Move(int i,int j);
	bool Win(int i,int j);
	void MakePlayerWin(int i,int j,int direct);
	void OccupyBlank();
	void Restart();
	void Regret();
	void SwitchHand();

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CFIRDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void MenuRegret();
	afx_msg void MenuSwitchHand();
	afx_msg void MenuRestart();
	afx_msg void OnEditUndo();
};


