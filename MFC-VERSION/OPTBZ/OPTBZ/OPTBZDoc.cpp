
// OPTBZDoc.cpp : COPTBZDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "OPTBZ.h"
#endif

#include "OPTBZDoc.h"
#include <propkey.h>
#include <iostream>
#include "opt.h"
#include "mclmcr.h"
#include "matrix.h"
#include "mclcppclass.h"
#include "MainFrm.h"

using namespace std;


CWinThread *pWinoptThread;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COPTBZDoc

IMPLEMENT_DYNCREATE(COPTBZDoc, CDocument)

BEGIN_MESSAGE_MAP(COPTBZDoc, CDocument)
END_MESSAGE_MAP()


// COPTBZDoc ����/����


UINT optThread(LPVOID pParam)
{
	

	CMainFrame * pMain=(CMainFrame*)AfxGetApp()->m_pMainWnd;  
	CString m_strOutput = _T("Modeling......");
	pMain->AddStrOutputDebugWnd(m_strOutput);//����CMainFrame�е��Զ��Ժ�����m_strOutput�Ǳ༭��ı���
	
	if(!optInitialize())
	{
		//cout<<"init error"<<endl;
		m_strOutput = _T("dll init error");
		pMain->AddStrOutputDebugWnd(m_strOutput);
	}
	
	
	
	
	// Ϊ���������ڴ�ռ䣬���Բ����mwArray
	mwArray opt(1,1,mxDOUBLE_CLASS);
    mwArray para(1,1,mxDOUBLE_CLASS);
	opt(1,1)=1;
    para(1,1)=30;
	mwArray res(1,1,mxDOUBLE_CLASS);

	optmain(1,res,opt,para);
	
	m_strOutput = _T("Modeled end!");
	pMain->AddStrOutputDebugWnd(m_strOutput);

	double *i=new double;
	res.GetData(i,1);
	//cout<<"x="<<*i<<endl; 
	if (*i==1)
	{
		m_strOutput = _T("Modeled succed!");
	} 
	else
	{
		m_strOutput = _T("Modeled failed!");
	}

	//m_strOutput.Format(_T("x = %f"),*i);
	pMain->AddStrOutputDebugWnd(m_strOutput);  
	 
	opt(1,1)=2; //����opt
	while (TRUE)
	{
		m_strOutput = _T("Optimize begin......");
		pMain->AddStrOutputDebugWnd(m_strOutput);
		optmain(1,res,opt,para);
		
		m_strOutput = _T("Optimization succeed!");
		pMain->AddStrOutputDebugWnd(m_strOutput);
		
		Sleep(1000);
	}
	return 0;
}

COPTBZDoc::COPTBZDoc()
{
	// TODO: �ڴ����һ���Թ������


	 pWinoptThread = AfxBeginThread(optThread,this);



}

COPTBZDoc::~COPTBZDoc()
{
}

BOOL COPTBZDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// COPTBZDoc ���л�

void COPTBZDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void COPTBZDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void COPTBZDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}


void COPTBZDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COPTBZDoc ���

#ifdef _DEBUG
void COPTBZDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COPTBZDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COPTBZDoc ����

