// ModelView.cpp : ʵ���ļ�
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


// CModelView ��ͼ

void CModelView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
	int m;
	m = 2;
}


// CModelView ���

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


// CModelView ��Ϣ�������
