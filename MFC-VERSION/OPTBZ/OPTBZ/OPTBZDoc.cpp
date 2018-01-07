
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

	if(!optInitialize())
	{
		cout<<"init error"<<endl;
	}
	

	
	
	// Ϊ���������ڴ�ռ䣬���Բ����mwArray
	mwArray a(1,1,mxDOUBLE_CLASS);
    mwArray b(1,1,mxDOUBLE_CLASS);
	a(1,1)=1;
    b(1,1)=30;
	mwArray x(1,1,mxDOUBLE_CLASS);

	optmain(1,x,a,b);

	double *i=new double;
	x.GetData(i,1);
	cout<<"x="<<*i<<endl; 

	CString m_strOutput = _T("Modeled succeed!");
	CMainFrame * pMain=(CMainFrame*)AfxGetApp()->m_pMainWnd;  
	pMain->AddStrOutputDebugWnd(m_strOutput);//����CMainFrame�е��Զ��Ժ�����m_strOutput�Ǳ༭��ı���  
	 
	a(1,1)=2;
	while (TRUE)
	{
		optmain(1,x,a,b);
		Sleep(1000);
		m_strOutput = _T("Optimization succeed!");
		pMain->AddStrOutputDebugWnd(m_strOutput);//����CMainFrame�е��Զ��Ժ�����m_strOutput�Ǳ༭��ı���
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

