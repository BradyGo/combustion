
// OPTBZDoc.cpp : COPTBZDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// COPTBZDoc 构造/析构


UINT optThread(LPVOID pParam)
{

	if(!optInitialize())
	{
		cout<<"init error"<<endl;
	}
	

	
	
	// 为变量分配内存空间，可以查帮助mwArray
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
	pMain->AddStrOutputDebugWnd(m_strOutput);//调用CMainFrame中的自动以函数，m_strOutput是编辑框的变量  
	 
	a(1,1)=2;
	while (TRUE)
	{
		optmain(1,x,a,b);
		Sleep(1000);
		m_strOutput = _T("Optimization succeed!");
		pMain->AddStrOutputDebugWnd(m_strOutput);//调用CMainFrame中的自动以函数，m_strOutput是编辑框的变量
	}
	return 0;
}

COPTBZDoc::COPTBZDoc()
{
	// TODO: 在此添加一次性构造代码


	 pWinoptThread = AfxBeginThread(optThread,this);



}

COPTBZDoc::~COPTBZDoc()
{
}

BOOL COPTBZDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// COPTBZDoc 序列化

void COPTBZDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void COPTBZDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void COPTBZDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// COPTBZDoc 诊断

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


// COPTBZDoc 命令

