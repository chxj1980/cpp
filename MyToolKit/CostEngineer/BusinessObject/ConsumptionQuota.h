#pragma once


/* �����£������ţ����������� */

class CConsumptionQuotaObj
{
public:
	CConsumptionQuotaObj();

	~CConsumptionQuotaObj();

	void Serialize(CArchive& ar, double version);
	bool CreateOrUpdate(string menuCode);
	
	static bool Draw(CGridCtrl* pGridCtrl, vector<CConsumptionQuotaObj>& cols);
	static bool Update(string menuCode, int nRow, vector<CConsumptionQuotaObj>& cols);
	static bool Delete(string menuCode, int nRow, vector<CConsumptionQuotaObj>& cols);

	
	CString m_name;				//  �˹� ���Ĳ�����
	double	m_quantity;			//	��������
	double	m_unit_price;		//	��λ�۸�
	CString m_unit;				//	������λ
};


class CConsumptionQuota
{
public:
	CConsumptionQuota();
	~CConsumptionQuota();

	void Serialize(CArchive& ar, double version);
	bool CreateOrUpdate(string strMenuCode);
	void GetQuotaFee(double& people, double& material, double& machine);
	
	static bool Draw(string menuCode, CGridCtrl* pGridCtrl, vector<CConsumptionQuota>& cols);
	static bool Update(string menuCode, int nRow, vector<CConsumptionQuota>& cols);
	static bool Delete(string menuCode, int nRow, vector<CConsumptionQuota>& cols);
	static unsigned int PopupMenuId(string menuCode);
	static void Calculate(string menuCode, vector<CConsumptionQuota>& cols);
	static CConsumptionQuota * FindQuota(CString quotaId, vector<CConsumptionQuota>& quotas);

	static string m_ObjectCode;
	static double m_ObjectVersion;


	CString m_identifier;	//	���� ���
	CString m_name;			//	���� ����
	int		m_unit;			//	���� ��λ
	
	vector<CConsumptionQuotaObj>	m_materials;	//	���ֺĲ�,�˹�������������
};

