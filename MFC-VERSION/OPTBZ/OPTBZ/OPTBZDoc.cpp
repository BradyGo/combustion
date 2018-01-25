
// OPTBZDoc.cpp : COPTBZDoc ���ʵ��
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

int OptFlag;
int ComuFlag;//

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
		ComuFlag = 1;
	} 
	else
	{
		m_strOutput = _T("Modeled failed!");
	}

	//m_strOutput.Format(_T("x = %f"),*i);
	pMain->AddStrOutputDebugWnd(m_strOutput);  
	 
	opt(1,1)=2; //����opt
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
	pMain->AddStrOutputDebugWnd(m_strOutput);//����CMainFrame�е��Զ��Ժ�����m_strOutput�Ǳ༭��ı���

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

	//����Excel ������(����Excel)
	if(!ExcelApp.CreateDispatch(_T("Excel.Application"),NULL))
	{
		AfxMessageBox(_T("����Excel������ʧ��!"));
		return -1;
	}

	/*�жϵ�ǰExcel�İ汾*/
	CString strExcelVersion = ExcelApp.get_Version();
	int iStart = 0;
	strExcelVersion = strExcelVersion.Tokenize(_T("."), iStart);
	if (_T("11") == strExcelVersion)
	{
		AfxMessageBox(_T("��ǰExcel�İ汾��2003��"));
	}
	else if (_T("15") == strExcelVersion)
	{
		AfxMessageBox(_T("��ǰExcel�İ汾��2013��"));
	}
	else
	{
		AfxMessageBox(_T("��ǰExcel�İ汾�������汾��"));
	}

	ExcelApp.put_Visible(TRUE);
	ExcelApp.put_UserControl(FALSE);

	/*�õ�����������*/
	books.AttachDispatch(ExcelApp.get_Workbooks());

	/*��һ�����������粻���ڣ�������һ��������*/
	CString strBookPath = _T("C:\\tmp.xls");
	try
	{
		/*��һ��������*/
		lpDisp = books.Open(strBookPath, 
			vtMissing, vtMissing, vtMissing, vtMissing, vtMissing,
			vtMissing, vtMissing, vtMissing, vtMissing, vtMissing, 
			vtMissing, vtMissing, vtMissing, vtMissing);
		book.AttachDispatch(lpDisp);
	}
	catch(...)
	{
		/*����һ���µĹ�����*/
		lpDisp = books.Add(vtMissing);
		book.AttachDispatch(lpDisp);
	}
	

	/*�õ��������е�Sheet������*/
	sheets.AttachDispatch(book.get_Sheets());

	/*��һ��Sheet���粻���ڣ�������һ��Sheet*/
	CString strSheetName = _T("NewSheet");
	try
	{
		/*��һ�����е�Sheet*/
		lpDisp = sheets.get_Item(_variant_t(strSheetName));
		sheet.AttachDispatch(lpDisp);
	}
	catch(...)
	{
		/*����һ���µ�Sheet*/
		lpDisp = sheets.Add(vtMissing, vtMissing, _variant_t((long)1), vtMissing);
		sheet.AttachDispatch(lpDisp);
		sheet.put_Name(strSheetName);
	}

//	system("pause");

	/*��Sheet��д������Ԫ��,��ģΪ10*10 */
	lpDisp = sheet.get_Range(_variant_t("A1"), _variant_t("J10"));
	range.AttachDispatch(lpDisp);

	VARTYPE vt = VT_I4; /*����Ԫ�ص����ͣ�long*/
	SAFEARRAYBOUND sabWrite[2]; /*���ڶ��������ά�����±����ʼֵ*/
	sabWrite[0].cElements = 10;
	sabWrite[0].lLbound = 0;
	sabWrite[1].cElements = 10;
	sabWrite[1].lLbound = 0;

	COleSafeArray olesaWrite;
	olesaWrite.Create(vt, sizeof(sabWrite)/sizeof(SAFEARRAYBOUND), sabWrite);

	/*ͨ��ָ�������ָ�����Զ�ά�����Ԫ�ؽ��м�Ӹ�ֵ*/
	long (*pArray)[2] = NULL;
	olesaWrite.AccessData((void **)&pArray);
	memset(pArray, 0, sabWrite[0].cElements * sabWrite[1].cElements * sizeof(long));

	/*�ͷ�ָ�������ָ��*/
	olesaWrite.UnaccessData();
	pArray = NULL;

	/*�Զ�ά�����Ԫ�ؽ��������ֵ*/
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

	/*��ColesaWritefeArray����ת��ΪVARIANT,��д�뵽Excel�����*/
	VARIANT varWrite = (VARIANT)olesaWrite;
	range.put_Value2(varWrite);

//	system("pause");

	/*�����ļ��ĺ�׺��ѡ�񱣴��ļ��ĸ�ʽ*/


	/*�ͷ���Դ*/
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
	// TODO: �ڴ����һ���Թ������

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

