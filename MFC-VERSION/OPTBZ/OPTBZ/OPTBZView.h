
// OPTBZView.h : COPTBZView ��Ľӿ�
//

#pragma once


class COPTBZView : public CView
{
protected: // �������л�����
	COPTBZView();
	DECLARE_DYNCREATE(COPTBZView)

// ����
public:
	COPTBZDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~COPTBZView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // OPTBZView.cpp �еĵ��԰汾
inline COPTBZDoc* COPTBZView::GetDocument() const
   { return reinterpret_cast<COPTBZDoc*>(m_pDocument); }
#endif

