// Guide.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OPTBZ.h"
#include "Guide.h"


// CGuide

IMPLEMENT_DYNCREATE(CGuide, CFormView)

CGuide::CGuide()
	: CFormView(CGuide::IDD)
{

}

CGuide::~CGuide()
{
}

void CGuide::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}





#ifdef _DEBUG
void CGuide::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGuide::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG



void CGuide::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_List.SetExtendedStyle(dwStyle);


	m_List.InsertColumn(0, _T("����"),LVCFMT_LEFT,80);
	m_List.InsertColumn(1, _T("������"),LVCFMT_LEFT,100);
	m_List.InsertColumn(2, _T("��ǰֵ"),LVCFMT_LEFT,80);
	m_List.InsertColumn(3, _T("ָ��ֵ"),LVCFMT_LEFT,80);
}
