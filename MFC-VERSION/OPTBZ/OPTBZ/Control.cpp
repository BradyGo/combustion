// Control.cpp : 实现文件
//

#include "stdafx.h"
#include "OPTBZ.h"
#include "Control.h"


// CControl

IMPLEMENT_DYNCREATE(CControl, CView)

CControl::CControl()
{

}

CControl::~CControl()
{
}

BEGIN_MESSAGE_MAP(CControl, CView)
END_MESSAGE_MAP()


// CControl 绘图

void CControl::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码

	CClientDC dc(this);
	CString str; 

	int a = 666888; 

	str.Format(_T("a = %d, 运行指导窗口!"), a); 

	dc.TextOut(10, 20, str);
}


// CControl 诊断

#ifdef _DEBUG
void CControl::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CControl::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CControl 消息处理程序
