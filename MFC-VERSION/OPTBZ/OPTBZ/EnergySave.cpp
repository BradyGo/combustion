// EnergySave.cpp : 实现文件
//

#include "stdafx.h"
#include "OPTBZ.h"
#include "EnergySave.h"


// CEnergySave

IMPLEMENT_DYNCREATE(CEnergySave, CFormView)

CEnergySave::CEnergySave()
	: CFormView(CEnergySave::IDD)
{

}

CEnergySave::~CEnergySave()
{
}

void CEnergySave::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEnergySave, CFormView)
END_MESSAGE_MAP()


// CEnergySave 诊断

#ifdef _DEBUG
void CEnergySave::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CEnergySave::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CEnergySave 消息处理程序
