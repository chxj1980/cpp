#pragma once

 /*���㱻����ָ���ǵ��� ������ĸ�������ֵ*/
class CMatlabShanghaiIndex : public CCalculateTask
{
public:
	CMatlabShanghaiIndex(HWND hwnd, int logType);
	~CMatlabShanghaiIndex(void);

	string ClassName(){ return "CMatlabShanghaiIndex"; }

	void Execute();
	static void Execute1(void* firstArg);

public:
	string  m_strIndexCode;

};
