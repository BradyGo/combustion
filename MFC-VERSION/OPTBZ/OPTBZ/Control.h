#pragma once


// CControl ��ͼ

class CControl : public CView
{
	DECLARE_DYNCREATE(CControl)

protected:
	CControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CControl();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


