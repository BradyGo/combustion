#pragma once



// CGraphView 窗体视图

class CGraphView : public CFormView
{
	DECLARE_DYNCREATE(CGraphView)

protected:
	CGraphView();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CRect rect;
	// nID为控件ID，x,y分别为对话框的当前长和宽
	void ChangeSize(UINT nID, int x, int y);
};


