
// GB28181ClientMDIDoc.h : CGB28181ClientMDIDoc ��Ľӿ�
//


#pragma once


class CGB28181ClientMDIDoc : public CDocument
{
protected: // �������л�����
public:
	CGB28181ClientMDIDoc();

	CGB28181ClientMDIDoc(string strDeviceId);

	DECLARE_DYNCREATE(CGB28181ClientMDIDoc)

// ����
public:
	string m_strDeviceId;

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CGB28181ClientMDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


