#pragma once

class CStockDataModel
{
public:
	CStockDataModel(void);

	//	��������Ӧ����Ϊ�麯�����Ա���������ͷ� m_vec_xxx �е��ڴ棬����memory leaks
	virtual ~CStockDataModel(void);
	
	virtual string ModelType() = 0;

	// ����ֵ�� CSV_CHECK_NO_ERROR �� �ɹ�   CSV_CHECK_FORMAT_ERROR : ���ص�CSV ��ʽ����   
	// CSV_CHECK_DATA_EXIST_ERROR �����ݿ����Ѵ���CSV�еļ�¼
	virtual int  CheckReport(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData) = 0;
	virtual void ParseCsvFile(vector<string>&  arrayHeader, vector<vector<string>>&  arrayData) = 0;
	virtual bool ParseCsvFileName(string szFileName) = 0;
	virtual void ParseXmlElement(void) = 0;
	virtual void ImportToDatabase(void) = 0;
	virtual void ExportFromDatabase(double startTime = 0.0, double endTime = 0.0) =0;
	virtual CStockDataModel * NewCopy() = 0;

	virtual string GetDownloadUrl() = 0;
	virtual string SaveAsCsv() = 0;
	virtual string GetCsvFileName() = 0;
	virtual string SqlScript() = 0;	//	�������ݿ�Ľű�
	virtual void NotifyDatabaseImportedToWindow();

	long CheckDownloadFileInfo(string middleFileName);
	long GetDownloadFileSize(string middleFileName);
	

public:
	int m_nRowNum;
	int m_nCode;	//	��Ʊ���� �����߽������ڣ�CsiPeDaily, CsiCsrcPeDaily ��
	HWND m_hWnd;	//	����֪ͨ��Ϣ��Ŀ�괰�ھ��
	int	m_nLogType;	//	��־�ļ���
	string m_cninfo_orgid;	
	string m_ConnectString ;

	enum eCheckResult { 
		CSV_CHECK_NO_ERROR,
		CSV_CHECK_FORMAT_ERROR,
		CSV_CHECK_DATA_EXIST_ERROR
	};

};
