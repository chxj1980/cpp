
// StockDoc.h : CStockDoc ��Ľӿ�
//


#pragma once


class CStockDoc : public CDocument
{
protected: // �������л�����
public:
	CStockDoc();
	DECLARE_DYNCREATE(CStockDoc)

// ����
public:
public:
	//	TradingDaily
	map<int, double>	m_vecTradeDate;
	map<int, double>	m_vecOpen;
	int		m_nRowNum;

	//	Shareholding
	map<int, double>	m_vecReportDateOfShareholding;
	map<int, double>	m_vecTotalShare;
	int		m_nRowNumOfShareholding;

	//	FinanceReport
	map<int, double>	m_vecReportDateOfFinanceReport;
	map<int, double>	m_vecNetProfit;
	int		m_nRowNumOfFinanceReport;

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CStockDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()



};


