#pragma once



// CDatabaseView ������ͼ

class CDatabaseView : public CFormView
{
	DECLARE_DYNCREATE(CDatabaseView)

protected:
	CDatabaseView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDatabaseView();

public:
	enum { IDD = IDD_DATABASEVIEW };
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


