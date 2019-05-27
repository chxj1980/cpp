#pragma once

#define  RECORD_NUM_PER_PAGE 500

typedef void CalculateTaskFunc(void* clientData);

//////////////////////////////////////////////////////////////////////////
// ʹ�ù���
// 

class CTipRecord
{
public:
	string	secCode;
	string	id;
	string	title;
	string	url;
	string	report_date;
};

class CCalculateTask
{
public:
	CCalculateTask(HWND hwnd, int logType);
	virtual ~CCalculateTask(void);

	LONG TaskID() { return m_nTaskID; }

	virtual string ClassName() = 0;
	
	void ScheduleTask(CalculateTaskFunc * proc);

	void NotifyTaskFinished();	//	�ڼ���ִ���߳��з���֪ͨ���������𴰿ڡ�,֪ͨ�а��������ʶ

	static CCalculateTask * FetchTask(LONG taskID);

	static void init();

	static void unInit();

	static UINT CalculateThreadFunc(LPVOID param);

	void AddPoint(string strZbCode, string strZbName, string strSjCode, string strUnit, double dbData,double dbData1 = 0,double dbData2 = 0,double dbData3 = 0);
	

	double GetDoubleValue(row & r, string colName)
	{
		double strResult;
		try{
			strResult = r.get<double>(colName);
		}
		catch(...)
		{
			unsigned long nan[2]={0xffffffff, 0x7fffffff};    
			strResult = *( double* )nan;
		}
		return strResult;
	}

public:
	HWND m_hWnd;
	int	m_nLogType;
	vector<string>		m_vec_request_code;		//	�������Ĺ�Ʊ��Χ
	vector<int>		m_vec_request_is_stock;
	string			m_str_request_zb_code;		//	

	COleDateTime		m_StartDate;
	COleDateTime		m_EndDate;

	CalculateTaskFunc * m_proc;
	
protected:
	LONG	m_nTaskID;						//	��������� ��ʶ��ȫ��Ψһ
	
	/* ����Ϊ��׼�������ʽ */
public:
	vector<string>		zb_code;	//	������
	vector<string>		zb_name;
	vector<string>		sj_code;	//	������
	vector<double>		data;
	vector<double>		data1;
	vector<double>		data2;
	vector<double>		data3;
	vector<string>		unit;		//	���ݵ�λ
	map<string,list<CTipRecord>>	tip;		//	������ʾ

	string				title_code;	//	�̶�ά ����
	string				title_name;	//	�̶�ά ����

	int		m_windowInMatlab;				//	matlab �д��ڵı�ʶ
	string	m_strGraphOrTable;				//	matlab ����� ��ͼ�� ���� �����
};
