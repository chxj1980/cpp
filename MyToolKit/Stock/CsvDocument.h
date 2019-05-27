#pragma once

// CCsvDocument �ĵ�

class CCsvDocument : public CDocument
{
	DECLARE_DYNCREATE(CCsvDocument)

public:
	CCsvDocument();
	virtual ~CCsvDocument();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCsvOpen();

public:
	vector<string>  m_arrayHeader;
	vector<vector<string>>  m_arrayData;

	string	m_strCsvType;		//	���ʲ���ծ�������ֽ�������,

	vector<CStockDataModel *> m_vecStockDataModel; // ����֧�ֵ���� CSV �ļ�����

	int	 m_nCurrStockData;
	
	afx_msg void OnCsvImport();
	bool CheckProfitsReport(void);
};
