#pragma once



// CEnergySave ������ͼ

class CEnergySave : public CFormView
{
	DECLARE_DYNCREATE(CEnergySave)

protected:
	CEnergySave();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


