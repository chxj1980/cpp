#pragma once


// CIndi10jqkaBonusView ��ͼ

class CIndi10jqkaBonusView : public CBaseGridCtlView
{
	DECLARE_DYNCREATE(CIndi10jqkaBonusView)

protected:
public:
	CIndi10jqkaBonusView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CIndi10jqkaBonusView();

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

public:
	virtual void OnInitialUpdate();

	void RedrawGridCtrl(CCalculateTask * cse);
	virtual void ProcessXmlWParam(string msgType,string code,string model, string param1,string param2,string param3);
};


