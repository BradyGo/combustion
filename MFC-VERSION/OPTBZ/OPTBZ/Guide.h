#pragma once



// CGuide ������ͼ

class CGuide : public CFormView
{
	DECLARE_DYNCREATE(CGuide)

protected:
	CGuide();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
//	afx_msg void OnLbnSelchangeList1();
	CListCtrl m_List;
	virtual void OnInitialUpdate();
};


