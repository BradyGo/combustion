// GraphView.cpp : ʵ���ļ�
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


// CGraphView ���

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


// CGraphView ��Ϣ�������


void CGraphView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	GetClientRect(&rect);

}


void CGraphView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if(nType!=SIZE_MINIMIZED )  //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
	{
//		ChangeSize(IDC_MSCHART1,cx,cy);  //��ÿһ���ؼ����������� 
//		ChangeSize(IDC_STATIC,cx,cy);
		GetClientRect(&rect);   //���Ҫ���¶Ի���Ĵ�С��������һ�α仯�ľ����ꣻ
	}
}



void CGraphView::ChangeSize(UINT nID, int x, int y)// nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{
	CWnd *pWnd;
	pWnd=GetDlgItem(nID); 
	if(pWnd!=NULL)     //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
	{
		CRect rec; 
		pWnd->GetWindowRect(&rec);  //��ȡ�ؼ��仯ǰ�Ĵ�С
		ScreenToClient(&rec);   //���ؼ���Сװ��λ�ڶԻ����е���������
		rec.left=rec.left*x/rect.Width();  //���ձ��������ռ����λ��
		rec.top=rec.top*y/rect.Height();
		rec.bottom=rec.bottom*y/rect.Height();
		rec.right=rec.right*x/rect.Width();
		pWnd->MoveWindow(rec);   //�����ؼ�
	}
}
