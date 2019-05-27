#pragma once

class CCalcFinanceReport : public CCalculateTask
{
public:
	CCalcFinanceReport(HWND hwnd, int logType);
	~CCalcFinanceReport(void);

	string ClassName(){ return "CCalcFinanceReport"; }

	void Execute();
	static void Execute1(void* firstArg);


public :
	string				m_str_db_code;			//	ָ������� ���񱨱�
	vector<string>		m_vec_zb_code;			//	ָ������� ָ�� ��Ӫҵ����/ Ӫҵ�ɱ�/ ����ȣ�

	vector<string>		m_vec_csrc_gate_code;	//	֤�����ҵ����: ����
	vector<string>		m_vec_csrc_big_code;	//	֤�����ҵ����: ����
	vector<string>		m_vec_reg_code;			//	����������

};
