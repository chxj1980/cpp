#pragma once
#include "cninfoannouncepdf.h"

class CPDFShareHolding :
	public CCninfoAnnouncePDF
{
public:
	CPDFShareHolding(void);
	~CPDFShareHolding(void);

	virtual string SaveAsCsv();

	string SqlScript();
	string ParseYearQuarter(string title);
	void UpdateQuarter();

	virtual void ImportToDatabase(string csv);
	virtual list<CCninfoAnnouncePDF *> CreatePDF();

public:
	

	string	m_ShareHolder[20];		//	�ɶ�����
	long	m_NumberOfHolding[20];	//	��ĩ�ֹ�����
	double	m_SharePercent[20];
	long	m_NumberOfRestrict[20];	//	���۹�����
	string	m_Character[20];		//	�ɶ�����
	
	int		m_nShareHolder;
};
