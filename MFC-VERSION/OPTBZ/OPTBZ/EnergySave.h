#pragma once



// CEnergySave 窗体视图

class CEnergySave : public CFormView
{
	DECLARE_DYNCREATE(CEnergySave)

protected:
	CEnergySave();           // 动态创建所使用的受保护的构造函数
	virtual ~CEnergySave();

public:
	enum { IDD = IDD_ENERGYSAVE };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


