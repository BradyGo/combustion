
// OPTBZView.cpp : COPTBZView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "OPTBZ.h"
#endif

#include "OPTBZDoc.h"
#include "OPTBZView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COPTBZView

IMPLEMENT_DYNCREATE(COPTBZView, CView)

BEGIN_MESSAGE_MAP(COPTBZView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COPTBZView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// COPTBZView ����/����

COPTBZView::COPTBZView()
{
	// TODO: �ڴ˴���ӹ������

}

COPTBZView::~COPTBZView()
{
}

BOOL COPTBZView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// COPTBZView ����

void COPTBZView::OnDraw(CDC* /*pDC*/)
{
	COPTBZDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// COPTBZView ��ӡ


void COPTBZView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COPTBZView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void COPTBZView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void COPTBZView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void COPTBZView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COPTBZView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COPTBZView ���

#ifdef _DEBUG
void COPTBZView::AssertValid() const
{
	CView::AssertValid();
}

void COPTBZView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COPTBZDoc* COPTBZView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COPTBZDoc)));
	return (COPTBZDoc*)m_pDocument;
}
#endif //_DEBUG


// COPTBZView ��Ϣ�������
