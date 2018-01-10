#pragma once



// CGraphView ������ͼ

class CGraphView : public CFormView
{
	DECLARE_DYNCREATE(CGraphView)

protected:
	CGraphView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CGraphView();

public:
	enum { IDD = IDD_GRAPHVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CRect rect;
	// nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
	void ChangeSize(UINT nID, int x, int y);
};


