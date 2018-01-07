// GraphView.cpp : 实现文件
//

#include "stdafx.h"
#include "OPTBZ.h"
#include "GraphView.h"


// CGraphView

IMPLEMENT_DYNCREATE(CGraphView, CFormView)

CGraphView::CGraphView()
	: CFormView(CGraphView::IDD)
{

}

CGraphView::~CGraphView()
{
}

void CGraphView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGraphView, CFormView)
END_MESSAGE_MAP()


// CGraphView 诊断

#ifdef _DEBUG
void CGraphView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGraphView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGraphView 消息处理程序
