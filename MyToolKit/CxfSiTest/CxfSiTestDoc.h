
// CxfSiTestDoc.h : CCxfSiTestDoc ��Ľӿ�
//


#pragma once


class CCxfSiTestDoc : public CDocument
{
protected: // �������л�����
	CCxfSiTestDoc();
	DECLARE_DYNCREATE(CCxfSiTestDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CCxfSiTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


