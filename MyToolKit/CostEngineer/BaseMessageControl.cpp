#include "StdAfx.h"
#include "CostEngineer.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "BaseMessageElementsParser.h"
#include "BaseMessageView.h"
#include "BaseMessageControl.h"

CBaseMessageControl::CBaseMessageControl(void)
{
}

CBaseMessageControl::~CBaseMessageControl(void)
{
}




void CBaseMessageControl::FocusStockOnLeftPane(string strCode)
{
	 

}

LRESULT CBaseMessageControl::OnUserXmlWParam(WPARAM wParam, LPARAM lParam)
{
	// we expect the CMessageString in the WParam paramater
	CMessageString* pString = (CMessageString*)wParam;

	// make sure passed string is valid (this is important to prevent unexpected
	// results if an invalid string is passed)
	if (CMessageString::IsStringValid(pString))
	{
		CBaseMessageElementsParser parser(this);
		parser.Parse(pString->GetBuffer(), pString->GetLength());
		delete pString;

		if(m_pOwnerView->IsKindOf(RUNTIME_CLASS(CBaseMessageView)))
			((CBaseMessageView *)m_pOwnerView)->ProcessXmlWParam(parser.msg_type,parser.code,parser.model, parser.param1,parser.param2, parser.param3);

		/*if(m_pOwnerView->IsKindOf(RUNTIME_CLASS(CBaseMessageFormView)))
			((CBaseMessageFormView *)m_pOwnerView)->ProcessXmlWParam(parser.msg_type,parser.code,parser.model, parser.param1,parser.param2, parser.param3);

		if(m_pOwnerView->IsKindOf(RUNTIME_CLASS(CBaseRichEditFormView)))
			((CBaseRichEditFormView *)m_pOwnerView)->ProcessXmlWParam(parser.msg_type,parser.code,parser.model, parser.param1,parser.param2, parser.param3);*/
	}
	else
	{
		CString strMessage = "ERROR! Test message using wParam received, but CMessageString passed in wParam is invalid.";
		AfxMessageBox(strMessage);

		ASSERT(FALSE);
		return MESSAGESTRING_NOT_RECEIVED;
	}

	return 0;
}


LRESULT CBaseMessageControl::OnUserLogWParam_1(WPARAM wParam, LPARAM lParam)
{
	// we expect the CMessageString in the WParam paramater
	CMessageString* pString = (CMessageString*)wParam;

	// make sure passed string is valid (this is important to prevent unexpected
	// results if an invalid string is passed)
	if (CMessageString::IsStringValid(pString))
	{
		//	ȱʡ������Ϣת����������
		CString curString;
		curString = *pString;
		// sendToOutput(curString, NULL, WM_USER_LOG_1);
		delete pString;
	}
	else
	{
		CString strMessage = "ERROR! Test message using wParam received, but CMessageString passed in wParam is invalid.";
		AfxMessageBox(strMessage);

		ASSERT(FALSE);
		return MESSAGESTRING_NOT_RECEIVED;
	}

	return 0;
}



void CBaseMessageControl::OnSetFocus(CString strTitle)
{
	
	/*����ȡ����ʱ���Զ�����ߵĹ�Ʊ���������Ѱ�Ҷ�Ӧ��*/

	//vector<string> firstMatch;
	//string strPattern = string("\\(\\d+\\)");
	//if(Pcre2Grep(strPattern.c_str(), strTitle.GetBuffer(),firstMatch )>0)
	//{
	//	//sendToOutput(strTitle, NULL, WM_USER_LOG_1);

	//	string::size_type pos1 = firstMatch[0].find(")");
	//	string codeStr = firstMatch[0].substr(1, pos1-1);

	//	FocusStockOnLeftPane(codeStr);
	//}	
	
}
