#pragma once


// CModelView ��ͼ

class CModelView : public CView
{
	DECLARE_DYNCREATE(CModelView)

protected:
	CModelView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CModelView();

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


