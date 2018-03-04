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
	ON_WM_SIZE()
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


void CGraphView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	GetClientRect(&rect);

}


void CGraphView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if(nType!=SIZE_MINIMIZED )  //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
	{
//		ChangeSize(IDC_MSCHART1,cx,cy);  //对每一个控件依次做调整 
//		ChangeSize(IDC_STATIC,cx,cy);
		GetClientRect(&rect);   //最后要更新对话框的大小，当做下一次变化的旧坐标；
	}
}



void CGraphView::ChangeSize(UINT nID, int x, int y)// nID为控件ID，x,y分别为对话框的当前长和宽
{
	CWnd *pWnd;
	pWnd=GetDlgItem(nID); 
	if(pWnd!=NULL)     //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
	{
		CRect rec; 
		pWnd->GetWindowRect(&rec);  //获取控件变化前的大小
		ScreenToClient(&rec);   //将控件大小装换位在对话框中的区域坐标
		rec.left=rec.left*x/rect.Width();  //按照比例调整空间的新位置
		rec.top=rec.top*y/rect.Height();
		rec.bottom=rec.bottom*y/rect.Height();
		rec.right=rec.right*x/rect.Width();
		pWnd->MoveWindow(rec);   //伸缩控件
	}
}
