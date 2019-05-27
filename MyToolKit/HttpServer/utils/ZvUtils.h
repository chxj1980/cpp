#pragma once

namespace ZvLibs
{
	// �ļ�Ŀ¼����
	tstring	GetFileDirPath(const tstring & szFilePath);
	tstring	GetFileName(const tstring & szFilePath);
	tstring	GetExeName();
	tstring	GetExePath();
	tstring & ToWinPath(tstring & szPath);
	tstring	GetAppPath();
	bool    GetDiskSpaceInfo(char cLetter=NULL, double * pTotal=NULL, double * pUsed=NULL, double * pPercentUsed=NULL, double * pLeft=NULL, double * pPercentLeft=NULL);
	bool	FileExist(const tstring &  szFilePath, LPWIN32_FIND_DATA pFd = NULL);
	tstring	MakeDirectory(const tstring & szPath);
	bool    DelFile(const tstring & szPath);

	// �����
	int		GetRandomInt();
	tstring	GetRandomString(int nLen);
	tstring GetStrFileSize(double fSize);

	// �ַ���
	tstring & StringTrim(tstring & str, const tstring & szTrim = _T(" "));
	void	 StringSplit(const tstring & szStr, const tstring & szSplitter, vector<tstring> & vtStr, const tstring & szEndStr=_T(""));
	tstring & StringReplace(tstring & str, const tstring & old_value, const tstring & new_value);
	tstring & ChangeQuotationMarks(tstring & szSrc);
	tstring & EscapeHtmlCharacter(tstring & szStr);
	tstring & EscapeJsonCharacter(tstring & szStr);

	// �汾
	tstring	GetOsVersion();
	tstring	GetFileVersion();

	// ʱ��
	tstring	GetSysTmOneDaySpan(SYSTEMTIME & tmStart, SYSTEMTIME & tmEnd);
	tstring GetFormatedSysTm(SYSTEMTIME & SysTm, bool bOneDay = false);
	int  	CompareSysTm(SYSTEMTIME & tm1, SYSTEMTIME & tm2);
	tstring GetFormatedTmNow();

	bool    ExeCmd(const tstring & szCmdLine, int nTimeoutMil, tstring & szOutput, DWORD & dwExitCode);
};