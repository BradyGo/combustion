#pragma once



// CGuide 窗体视图

class CGuide : public CFormView
{
	DECLARE_DYNCREATE(CGuide)

protected:
	CGuide();           // 动态创建所使用的受保护的构造函数
	virtual ~CGuide();

public:
	enum { IDD = IDD_GUIDE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
//	afx_msg void OnLbnSelchangeList1();
	CListCtrl m_List;
	virtual void OnInitialUpdate();
};


