#pragma once

// CStatsGovCnDoc �ĵ�

class CStatsGovCnDoc : public CDocument
{
	DECLARE_DYNCREATE(CStatsGovCnDoc)

public:
	CStatsGovCnDoc();
	virtual ~CStatsGovCnDoc();
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
	string			m_str_db_code;
	vector<string>	m_vec_zb_code;
	vector<string>	m_vec_reg_code;
	vector<string>	m_vec_csrc_gate_code;
	vector<string>	m_vec_csrc_big_code;
	int				m_nOutput;

	COleDateTime	m_StartDate;
	COleDateTime	m_End_Date;


};
