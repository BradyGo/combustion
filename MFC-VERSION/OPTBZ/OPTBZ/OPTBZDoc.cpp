
// OPTBZDoc.cpp : COPTBZDoc 类的实现
//

#include "stdafx.h"
#include "CApplication.h"
#include "CWorkbooks.h"
#include "CWorkbook.h"
#include "CWorksheets.h"
#include "CWorksheet.h"
#include "CRectangle.h"
#include "CRectangles.h"
#include "CRange.h"

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

int OptFlag;
int ComuFlag;//

UINT optThread(LPVOID pParam)
{
	

	CMainFrame * pMain=(CMainFrame*)AfxGetApp()->m_pMainWnd;  
	CString m_strOutput = _T("Modeling......");
	pMain->AddStrOutputDebugWnd(m_strOutput);//调用CMainFrame中的自动以函数，m_strOutput是编辑框的变量
	
	if(!optInitialize())
	{
		//cout<<"init error"<<endl;
		m_strOutput = _T("dll init error");
		pMain->AddStrOutputDebugWnd(m_strOutput);
	}
	
	
	
	
	// 为变量分配内存空间，可以查帮助mwArray
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
		ComuFlag = 1;
	} 
	else
	{
		m_strOutput = _T("Modeled failed!");
	}

	//m_strOutput.Format(_T("x = %f"),*i);
	pMain->AddStrOutputDebugWnd(m_strOutput);  
	 
	opt(1,1)=2; //调用opt
	while(TRUE)
	{
		while (OptFlag ==1 )
		{
			ComuFlag = 0;
			m_strOutput = _T("Optimize begin......");
			pMain->AddStrOutputDebugWnd(m_strOutput);
			optmain(1,res,opt,para);

			m_strOutput = _T("Optimization succeed!");
			pMain->AddStrOutputDebugWnd(m_strOutput);

			ComuFlag = 1;
			Sleep(10000);

		}
		Sleep(5000);
	}


	return 0;
}

UINT ComuThread(LPVOID pParam)
{
	CMainFrame * pMain=(CMainFrame*)AfxGetApp()->m_pMainWnd;  
	CString m_strOutput = _T("Write Exl begin......");
	pMain->AddStrOutputDebugWnd(m_strOutput);//调用CMainFrame中的自动以函数，m_strOutput是编辑框的变量

	HRESULT hr;   
	hr = CoInitialize(NULL);     
	if(FAILED(hr))
	{    
		AfxMessageBox(_T("Failed to call Coinitialize()" ));
	}
	
	
	
	CApplication ExcelApp;
	CWorkbooks books;
	CWorkbook book;
	CWorksheets sheets;
	CWorksheet sheet;
	CRange range;
	LPDISPATCH lpDisp = NULL;

	//创建Excel 服务器(启动Excel)
	if(!ExcelApp.CreateDispatch(_T("Excel.Application"),NULL))
	{
		AfxMessageBox(_T("启动Excel服务器失败!"));
		return -1;
	}

	/*判断当前Excel的版本*/
	CString strExcelVersion = ExcelApp.get_Version();
	int iStart = 0;
	strExcelVersion = strExcelVersion.Tokenize(_T("."), iStart);
	if (_T("11") == strExcelVersion)
	{
		AfxMessageBox(_T("当前Excel的版本是2003。"));
	}
	else if (_T("15") == strExcelVersion)
	{
		AfxMessageBox(_T("当前Excel的版本是2013。"));
	}
	else
	{
		AfxMessageBox(_T("当前Excel的版本是其他版本。"));
	}

	ExcelApp.put_Visible(TRUE);
	ExcelApp.put_UserControl(FALSE);

	/*得到工作簿容器*/
	books.AttachDispatch(ExcelApp.get_Workbooks());

	/*打开一个工作簿，如不存在，则新增一个工作簿*/
	CString strBookPath = _T("C:\\tmp.xls");
	try
	{
		/*打开一个工作簿*/
		lpDisp = books.Open(strBookPath, 
			vtMissing, vtMissing, vtMissing, vtMissing, vtMissing,
			vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, 
			vtMissing, vtMissing, vtMissing, vtMissing);
		book.AttachDispatch(lpDisp);
	}
	catch(...)
	{
		/*增加一个新的工作簿*/
		lpDisp = books.Add(vtMissing);
		book.AttachDispatch(lpDisp);
	}
	

	/*得到工作簿中的Sheet的容器*/
	sheets.AttachDispatch(book.get_Sheets());

	/*打开一个Sheet，如不存在，就新增一个Sheet*/
	CString strSheetName = _T("NewSheet");
	try
	{
		/*打开一个已有的Sheet*/
		lpDisp = sheets.get_Item(_variant_t(strSheetName));
		sheet.AttachDispatch(lpDisp);
	}
	catch(...)
	{
		/*创建一个新的Sheet*/
		lpDisp = sheets.Add(vtMissing, vtMissing, _variant_t((long)1), vtMissing);
		sheet.AttachDispatch(lpDisp);
		sheet.put_Name(strSheetName);
	}

//	system("pause");

	/*向Sheet中写入多个单元格,规模为10*10 */
	lpDisp = sheet.get_Range(_variant_t("A1"), _variant_t("J10"));
	range.AttachDispatch(lpDisp);

	VARTYPE vt = VT_I4; /*数组元素的类型，long*/
	SAFEARRAYBOUND sabWrite[2]; /*用于定义数组的维数和下标的起始值*/
	sabWrite[0].cElements = 10;
	sabWrite[0].lLbound = 0;
	sabWrite[1].cElements = 10;
	sabWrite[1].lLbound = 0;

	COleSafeArray olesaWrite;
	olesaWrite.Create(vt, sizeof(sabWrite)/sizeof(SAFEARRAYBOUND), sabWrite);

	/*通过指向数组的指针来对二维数组的元素进行间接赋值*/
	long (*pArray)[2] = NULL;
	olesaWrite.AccessData((void **)&pArray);
	memset(pArray, 0, sabWrite[0].cElements * sabWrite[1].cElements * sizeof(long));

	/*释放指向数组的指针*/
	olesaWrite.UnaccessData();
	pArray = NULL;

	/*对二维数组的元素进行逐个赋值*/
	long index[2] = {0, 0};
	long lFirstLBound = 0;
	long lFirstUBound = 0;
	long lSecondLBound = 0;
	long lSecondUBound = 0;
	olesaWrite.GetLBound(1, &lFirstLBound);
	olesaWrite.GetUBound(1, &lFirstUBound);
	olesaWrite.GetLBound(2, &lSecondLBound);
	olesaWrite.GetUBound(2, &lSecondUBound);
	for (long i = lFirstLBound; i <= lFirstUBound; i++)
	{
		index[0] = i;
		for (long j = lSecondLBound; j <= lSecondUBound; j++)
		{
			index[1] = j;
			long lElement = i * sabWrite[1].cElements + j; 
			olesaWrite.PutElement(index, &lElement);
		}
	}

	/*把ColesaWritefeArray变量转换为VARIANT,并写入到Excel表格中*/
	VARIANT varWrite = (VARIANT)olesaWrite;
	range.put_Value2(varWrite);

//	system("pause");

	/*根据文件的后缀名选择保存文件的格式*/


	/*释放资源*/
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	ExcelApp.Quit();
	ExcelApp.ReleaseDispatch();


	while(TRUE)
	{
		while(ComuFlag == 1)
		{
			OptFlag = 0;
			m_strOutput = _T("Write success!");
			pMain->AddStrOutputDebugWnd(m_strOutput);
			OptFlag = 1;
			Sleep(5000);
		}
		Sleep(5000);
	}
	


	return 0;
}

COPTBZDoc::COPTBZDoc()
{
	// TODO: 在此添加一次性构造代码

	 OptFlag = 0;
	 ComuFlag = 0;

	 pWinoptThread = AfxBeginThread(optThread,this);
	 pWinoptThread = AfxBeginThread(ComuThread,this);



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

