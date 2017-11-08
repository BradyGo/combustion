
// OPTBZView.cpp : COPTBZView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COPTBZView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// COPTBZView 构造/析构

COPTBZView::COPTBZView()
{
	// TODO: 在此处添加构造代码

}

COPTBZView::~COPTBZView()
{
}

BOOL COPTBZView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// COPTBZView 绘制

void COPTBZView::OnDraw(CDC* /*pDC*/)
{
	COPTBZDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// COPTBZView 打印


void COPTBZView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COPTBZView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COPTBZView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COPTBZView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// COPTBZView 诊断

#ifdef _DEBUG
void COPTBZView::AssertValid() const
{
	CView::AssertValid();
}

void COPTBZView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COPTBZDoc* COPTBZView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COPTBZDoc)));
	return (COPTBZDoc*)m_pDocument;
}
#endif //_DEBUG


// COPTBZView 消息处理程序
