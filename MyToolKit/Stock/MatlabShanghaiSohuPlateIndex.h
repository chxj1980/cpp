#pragma once

 /*���㱻����ָ���ǵ��� ������ĸ�������ֵ*/
class CMatlabShanghaiSohuPlateIndex : public CCalculateTask
{
public:
	CMatlabShanghaiSohuPlateIndex(HWND hwnd, int logType);
	~CMatlabShanghaiSohuPlateIndex(void);

	string ClassName(){ return "CMatlabShanghaiSohuPlateIndex"; }

	void Execute();
	static void Execute1(void* firstArg);

public:
	

};
