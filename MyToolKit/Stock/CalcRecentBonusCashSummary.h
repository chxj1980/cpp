#pragma once

class CCalcRecentBonusCashSummary : public CCalculateTask 
{
public:
	CCalcRecentBonusCashSummary(HWND hwnd, int logType);
	~CCalcRecentBonusCashSummary(void);

	string ClassName(){ return "CCalcRecentBonusCashSummary"; }

	void Execute();
	static void Execute1(void* firstArg);

public:

	vector<int>		m_vec_code			;			//	"��˾����",
	vector<string>	m_vec_abbreviation;
	vector<string>	m_vec_bonus_year;				//	�ֺ����
	vector<double>	m_vec_bonus_cash;				//	�ֽ�ֺ�
	vector<double>	m_vec_bonus_share;				//	�͹�
	vector<double>	m_vec_reserve_to_common_share;	//	ת����
	vector<string>	m_vec_right_record_date;		//	��Ȩ�Ǽ�����
	vector<string>	m_vec_exit_right_date;			//	��Ȩ��Ϣ��
	vector<double>	m_vec_recent_close;				//	������̼�
	vector<double>	m_vec_earning_percent;			//	�������

};
