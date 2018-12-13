
// PPView.h : CPPView 클래스의 인터페이스
//

#pragma once


class CPPView : public CView
{
protected: // serialization에서만 만들어집니다.
	CPPView();
	DECLARE_DYNCREATE(CPPView)

// 특성입니다.
public:
	CPPDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CPPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // PPView.cpp의 디버그 버전
inline CPPDoc* CPPView::GetDocument() const
   { return reinterpret_cast<CPPDoc*>(m_pDocument); }
#endif

