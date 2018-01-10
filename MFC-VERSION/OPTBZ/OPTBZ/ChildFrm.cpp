
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "OPTBZ.h"

#include "ChildFrm.h"

#include "ModelView.h"
#include "Control.h"
#include "GraphView.h"
#include "EnergySave.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
/*
	return m_wndSplitter.Create(this,
		2, 2,			// TODO: 调整行数和列数
		CSize(10, 10),	// TODO: 调整最小窗格大小
		pContext);
		*/

	CRect rc;   

	// 获取框架窗口客户区的CRect对象   
	GetClientRect(&rc);   

	// 创建静态分割窗口，两行一列   
	if (!m_wndSplitter.CreateStatic(this, 2, 2))   
		return FALSE;   

	// 创建上面窗格中的视图   
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CModelView),CSize(rc.Width()/2, rc.Height()/2), pContext))   
		return FALSE;   

	// 创建下面窗格中的视图   
	if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CControl), CSize(rc.Width()/2, rc.Height()/2), pContext))   
		return FALSE;   
	// 创建上面窗格中的视图   
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CGraphView),CSize(rc.Width()/2, rc.Height()/2), pContext))   
		return FALSE;   

	// 创建下面窗格中的视图   
	if (!m_wndSplitter.CreateView(1, 1, RUNTIME_CLASS(CEnergySave), CSize(rc.Width()/2, rc.Height()/2), pContext))   
		return FALSE;   

	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序
