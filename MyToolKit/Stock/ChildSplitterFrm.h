
// ChildFrm.h : CChildFrame ��Ľӿ�
//

#pragma once

class CChildSplitterFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildSplitterFrame)
public:
	CChildSplitterFrame();

// ����
public:

// ����
public:

// ��д
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildSplitterFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CMySplitterWndEx m_wndSplitter;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
