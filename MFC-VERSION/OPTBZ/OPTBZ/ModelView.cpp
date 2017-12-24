// ModelView.cpp : 实现文件
//

#include "stdafx.h"
#include "OPTBZ.h"
#include "ModelView.h"


// CModelView

IMPLEMENT_DYNCREATE(CModelView, CView)

CModelView::CModelView()
{

}

CModelView::~CModelView()
{
}

BEGIN_MESSAGE_MAP(CModelView, CView)
END_MESSAGE_MAP()


// CModelView 绘图

void CModelView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	int m;
	m = 2;
}


// CModelView 诊断

#ifdef _DEBUG
void CModelView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CModelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CModelView 消息处理程序
