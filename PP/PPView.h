
// PPView.h : CPPView Ŭ������ �������̽�
//

#pragma once


class CPPView : public CView
{
protected: // serialization������ ��������ϴ�.
	CPPView();
	DECLARE_DYNCREATE(CPPView)

// Ư���Դϴ�.
public:
	CPPDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CPPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_ballx;
	int m_bally;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int dirballx;
	int dirbally;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	int m_lracket;
	int m_rracket;
	bool GameStart;
	int lscore;
	int rscore;
	bool DuringGame;
	int GameSpeed;
	afx_msg void On32771();
};

#ifndef _DEBUG  // PPView.cpp�� ����� ����
inline CPPDoc* CPPView::GetDocument() const
   { return reinterpret_cast<CPPDoc*>(m_pDocument); }
#endif

