// Control.cpp : ʵ���ļ�
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


// CControl ��ͼ

void CControl::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���

	CClientDC dc(this);
	CString str; 

	int a = 666888; 

	str.Format(_T("a = %d, ����ָ������!"), a); 

	dc.TextOut(10, 20, str);
}


// CControl ���

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


// CControl ��Ϣ�������
