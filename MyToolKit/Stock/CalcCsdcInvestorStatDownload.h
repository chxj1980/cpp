#pragma once

class CCalcCsdcInvestorStatDownload : public CCalculateTask
{
public:
	CCalcCsdcInvestorStatDownload(HWND hwnd, int logType);
	~CCalcCsdcInvestorStatDownload(void);

	string ClassName(){ return "CCalcCsdcInvestorStatDownload"; }

	void NeedDownload();
	static void NeedDownload1(void* firstArg);
public:
	vector<int>		m_vec_code			;	//	"ÿ�ܵĿ�ʼ����",
};
