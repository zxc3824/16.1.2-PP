
// PPView.cpp : CPPView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "PP.h"
#endif

#include "PPDoc.h"
#include "PPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPPView

IMPLEMENT_DYNCREATE(CPPView, CView)

BEGIN_MESSAGE_MAP(CPPView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_32771, &CPPView::On32771)
END_MESSAGE_MAP()

// CPPView 생성/소멸

CPPView::CPPView()
	: m_ballx(0)
	, m_bally(0)
	, dirballx(5)
	, dirbally(3)
	, m_lracket(0)
	, m_rracket(0)
	, GameStart(false)
	, lscore(0)
	, rscore(0)
	, DuringGame(false)
	, GameSpeed(5)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPPView::~CPPView()
{
}

BOOL CPPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPPView 그리기

void CPPView::OnDraw(CDC* pDC)
{
	CPPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CPPView 인쇄

BOOL CPPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPPView 진단

#ifdef _DEBUG
void CPPView::AssertValid() const
{
	CView::AssertValid();
}

void CPPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPPDoc* CPPView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPPDoc)));
	return (CPPDoc*)m_pDocument;
}
#endif //_DEBUG


// CPPView 메시지 처리기


void CPPView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// 타이머 세팅
	SetTimer(1, 10, NULL);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CPPView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 글꼴 생성
	CFont font1, font2, font3, font4, font5;
	font1.CreateFontW(50, 35, 0, 0, FW_BOLD, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Silkscreen"));
	font2.CreateFontW(30, 20, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Silkscreen"));
	font3.CreateFontW(25, 18, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Silkscreen"));
	font4.CreateFontW(50, 35, 0, 0, FW_DEMIBOLD, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Silkscreen"));
	font5.CreateFontW(80, 80, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Silkscreen"));
	
	// 화면 크기 받아오기
	CRect rect;
	COLORREF col;
	GetClientRect(&rect);

	// 화면 채우기
	CClientDC dc(this);
	dc.FillSolidRect(rect, RGB(0, 0, 0));

	// 텍스트 색, 배경 투명, 텍스트 정렬
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextAlign(TA_CENTER);

	// 승패 판정
	if (lscore >= 11 || rscore >= 11) {
		dc.SelectObject(&font5);
		if (lscore >= 11) dc.TextOutW(rect.Width() / 2 + 10, rect.Height() / 3, L"1P WIN!");
		if (rscore >= 11) dc.TextOutW(rect.Width() / 2 + 10, rect.Height() / 3, L"2P WIN!");
		dc.SelectObject(&font3);
		dc.TextOutW(rect.Width() / 2 + 10, rect.Height() / 3 * 2, L"PRESS ANYKEY TO CONTINUE");
		return;
	}

	if (!GameStart) {
		// 메인 화면 및 설정
		if (!DuringGame) {
			dc.SelectObject(&font1);
			dc.TextOutW(rect.Width() / 2 + 10, rect.Height() / 3, L"PING PONG");
			dc.SelectObject(&font2);
			dc.TextOutW(rect.Width() / 2 + 10, rect.Height() / 3 * 2, L"-PRESS SPACE TO START-");
			CString str;
			str.Format(L"SPEED : %d <L/R>", GameSpeed);
			dc.SelectObject(&font3);
			dc.TextOutW(rect.Width() / 2 + 10, rect.Height() / 4 * 3, str);
			if (GameSpeed > 12) GameSpeed = 12;
			if (GameSpeed < 3) GameSpeed = 3;
			dirballx = GameSpeed;
		}

		// 공 위치 초기화
		m_ballx = rect.Width() / 2 - 7;
		m_bally = rect.Height() / 2 - 7;
	}

	// 점수판
	if (DuringGame) {
		for (int i = 0; i < rect.Height() / 19; i++) dc.FillSolidRect(rect.Width() / 2 - 5, i * 20, 10, 5, RGB(255, 255, 255));
		CString score1, score2;
		score1.Format(L"%d", lscore);
		score2.Format(L"%d", rscore);
		dc.SelectObject(&font4);
		dc.TextOutW(rect.Width() / 10, rect.Height() / 12, score1);
		dc.TextOutW(rect.Width() / 10 * 9, rect.Height() / 12, score2);
	}

	// 라켓, 공 그리기
	dc.FillSolidRect(35, m_lracket, 15, 80, RGB(255, 255, 255));
	dc.FillSolidRect(rect.Width() - 50, m_rracket, 15, 80, RGB(255, 255, 255));
	dc.FillSolidRect(m_ballx, m_bally, 15, 15, RGB(255, 255, 255));

	// 게임 시작('Space'키)
	if (GameStart) {
		DuringGame = true;

		// 라켓 위치 변경(키인식)
		if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState('W') && 0x8001) m_lracket -= GameSpeed + 1;
		if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState('S') && 0x8001) m_lracket += GameSpeed + 1;
		if (m_lracket <= 0) m_lracket = 0;
		if (m_lracket >= rect.Height() - 80) m_lracket = rect.Height() - 80;
		if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_UP) && 0x8001) m_rracket -= GameSpeed + 1;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_DOWN) && 0x8001) m_rracket += GameSpeed + 1;
		if (m_rracket <= 0) m_rracket = 0;
		if (m_rracket >= rect.Height() - 80) m_rracket = rect.Height() - 80;

		// 공 위치, 속도 변경
		m_ballx = m_ballx + dirballx;
		m_bally = m_bally + dirbally;
		if (m_bally <= 0) dirbally = abs(dirbally);
		if (m_bally >= rect.Height() - 15) dirbally = -abs(dirbally);
		if ((m_ballx >= 20 && m_ballx <= 50 && m_bally >= m_lracket - 15 && m_bally <= m_lracket + 80)
			|| (m_ballx >= rect.Width() - 65 && m_ballx <= rect.Width() - 50 && m_bally >= m_rracket - 15 && m_bally <= m_rracket + 80)) {
			if (m_ballx >= 20 && m_ballx <= 50) dirballx = GameSpeed;
			if (m_ballx >= rect.Width() - 65 && m_ballx <= rect.Width() - 50) dirballx = -GameSpeed;
			if ((m_bally >= m_lracket - 15 && m_bally <= m_lracket - 5) || (m_bally >= m_rracket - 15 && m_bally <= m_rracket - 5)) dirbally = -9;
			if ((m_bally >= m_lracket - 5 && m_bally <= m_lracket + 5) || (m_bally >= m_rracket - 5 && m_bally <= m_rracket + 5)) dirbally = -7;
			if ((m_bally >= m_lracket + 5 && m_bally <= m_lracket + 15) || (m_bally >= m_rracket + 5 && m_bally <= m_rracket + 15)) dirbally = -5;
			if ((m_bally >= m_lracket + 15 && m_bally <= m_lracket + 25) || (m_bally >= m_rracket + 15 && m_bally <= m_rracket + 25)) dirbally = -3;
			if ((m_bally >= m_lracket + 25 && m_bally <= m_lracket + 32) || (m_bally >= m_rracket + 25 && m_bally <= m_rracket + 32)) dirbally = -2;
			if ((m_bally >= m_lracket + 33 && m_bally <= m_lracket + 40) || (m_bally >= m_rracket + 33 && m_bally <= m_rracket + 40)) dirbally = 2;
			if ((m_bally >= m_lracket + 40 && m_bally <= m_lracket + 50) || (m_bally >= m_rracket + 40 && m_bally <= m_rracket + 50)) dirbally = 3;
			if ((m_bally >= m_lracket + 50 && m_bally <= m_lracket + 60) || (m_bally >= m_rracket + 50 && m_bally <= m_rracket + 60)) dirbally = 5;
			if ((m_bally >= m_lracket + 60 && m_bally <= m_lracket + 70) || (m_bally >= m_rracket + 60 && m_bally <= m_rracket + 70)) dirbally = 7;
			if ((m_bally >= m_lracket + 70 && m_bally <= m_lracket + 80) || (m_bally >= m_rracket + 70 && m_bally <= m_rracket + 80)) dirbally = 9;
		}

		// 점수 판정
		if (m_ballx <= 0 || m_ballx >= rect.Width() - 15) {
			if (m_ballx <= 0) {
				dirballx = -dirballx;
				rscore++;
			}
			if (m_ballx >= rect.Width() - 15) {
				dirballx = -dirballx;
				lscore++;
			}
			dirbally = 3;
			GameStart = false;
		}
	}

	CView::OnTimer(nIDEvent);
}


BOOL CPPView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// 스페이스키를 통해 시작
	if (!GameStart && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) GameStart = true;

	// 게임 속도 조절(공, 라켓)
	if (!GameStart && !DuringGame) {
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_LEFT) GameSpeed--;
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RIGHT) GameSpeed++;
	}

	// 게임 끝난 뒤 초기화 작업
	if ((lscore >= 11 || rscore >= 11) && (pMsg->message == WM_KEYDOWN)) {
		DuringGame = false;
		lscore = 0;
		rscore = 0;
		dirballx = GameSpeed;
	}

	// 도움말(F1)
	if (!GameStart && pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F1) MessageBox(L"LEFT PLAYER - W and S key\nRIGHT PLAYER - UP and DOWN key\nSPEED - LEFT and RIGHT\n11 POINT - WIN!");
	return CView::PreTranslateMessage(pMsg);
}


BOOL CPPView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CPPView::On32771()
{
	// 도움말(메뉴)
	MessageBox(L"LEFT PLAYER - W and S key\nRIGHT PLAYER - UP and DOWN key\nSPEED - LEFT and RIGHT\n11 POINT - WIN!");
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
