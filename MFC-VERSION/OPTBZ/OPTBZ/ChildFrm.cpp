
// ChildFrm.cpp : CChildFrame ���ʵ��
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

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{
/*
	return m_wndSplitter.Create(this,
		2, 2,			// TODO: ��������������
		CSize(10, 10),	// TODO: ������С�����С
		pContext);
		*/

	CRect rc;   

	// ��ȡ��ܴ��ڿͻ�����CRect����   
	GetClientRect(&rc);   

	// ������̬�ָ�ڣ�����һ��   
	if (!m_wndSplitter.CreateStatic(this, 2, 2))   
		return FALSE;   

	// �������洰���е���ͼ   
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CModelView),CSize(rc.Width()/2, rc.Height()/2), pContext))   
		return FALSE;   

	// �������洰���е���ͼ   
	if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CControl), CSize(rc.Width()/2, rc.Height()/2), pContext))   
		return FALSE;   
	// �������洰���е���ͼ   
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CGraphView),CSize(rc.Width()/2, rc.Height()/2), pContext))   
		return FALSE;   

	// �������洰���е���ͼ   
	if (!m_wndSplitter.CreateView(1, 1, RUNTIME_CLASS(CEnergySave), CSize(rc.Width()/2, rc.Height()/2), pContext))   
		return FALSE;   

	return TRUE;
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

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

// CChildFrame ��Ϣ�������
