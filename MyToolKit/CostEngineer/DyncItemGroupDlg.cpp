#include "StdAfx.h"
#include "DyncItemGroupDlg.h"

CDyncItemGroupDlg::CDyncItemGroupDlg()
{
	for (int g = 0; g < MAX_GROUP; g++)
	{
		for (int l = 0; l < MAX_LINE; l++)
		{
			for (int c = 0; c < MAX_COLUMN; c++)
			{
				m_vecFindItem[g][l][c].nType = 0;
				m_vecFindItem[g][l][c].bKey = false;
				m_vecFindItem[g][l][c].dwStyle = 0;
				//	���� ID
				m_vecFindItem[g][l][c].nID = (g * MAX_GROUP * MAX_LINE + l * MAX_LINE  +  c) * 2  + IDEDIT;
				m_vecFindItem[g][l][c].nID1 = (g * MAX_GROUP * MAX_LINE + l * MAX_LINE + c) * 2 + IDEDIT + 1;
			}
		}
	}

	DLGMARGIN = 10;						 // margins all around
	GROUPMARGIN = 10;
	CYSPACE = 5;						 // vertical space between controls
	CXSPACE = 5;						 // horizontal space between controls

	CYCAPTION = 8;						 // height of static text
	CXCAPTION = 10;

	CYSTATIC = 8;						 // height of static text
	CXSTATIC = 60;

	CXEDIT = 60;
	CYEDIT = 12;					 // height of edit control

	CXCHECKBOX = 60;
	CYCHECKBOX = 12;					 // height of checkbox control

	CXCOMBOX = 60;
	CYCOMBOX = 15;

	CXBUTTON = 40;					 // button width...
	CYBUTTON = 15;

	CXRADIO = 60;
	CYRADIO = 12;

	CSize sz(GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON));
	CXICON = sz.cx;
	CYICON = sz.cy;

	GROUP_NUM_PER_LINE = 3;

}

CDyncItemGroupDlg::~CDyncItemGroupDlg(void)
{
}


void CDyncItemGroupDlg::DoDataExchange(CDataExchange* pDX)
{
	for (int g = 0; g < MAX_GROUP; g++)
	{
		for (int l = 0; l < MAX_LINE; l++)
		{
			for (int c = 0; c < MAX_COLUMN; c++)
			{
				if (m_vecFindItem[g][l][c].nType == CDlgTemplateBuilder::EDIT)
				{
					DDX_Text(pDX, m_vecFindItem[g][l][c].nID, m_vecFindItem[g][l][c].strItem);

					if (m_vecFindItem[g][l][c].dbMin < m_vecFindItem[g][l][c].dbMax)
					{
						double dbVal = String2Double(m_vecFindItem[g][l][c].strItem.GetBuffer());
						DDV_MinMaxDouble(pDX, dbVal, m_vecFindItem[g][l][c].dbMin, m_vecFindItem[g][l][c].dbMax);//У�����ֵ����Сֵ
					}
					if (m_vecFindItem[g][l][c].nMin < m_vecFindItem[g][l][c].nMax)
					{
						int nVal = atoi(m_vecFindItem[g][l][c].strItem.GetBuffer());
						DDV_MinMaxDouble(pDX, nVal, m_vecFindItem[g][l][c].nMin, m_vecFindItem[g][l][c].nMax);//У�����ֵ����Сֵ
					}
				}
				if (m_vecFindItem[g][l][c].nType == CDlgTemplateBuilder::COMBOBOX)
				{
					DDX_CBString(pDX, m_vecFindItem[g][l][c].nID, m_vecFindItem[g][l][c].strItem);
				}
				if (m_vecFindItem[g][l][c].nType == CDlgTemplateBuilder::CHECKBOX)
				{
					stringstream ss;
					ss << "m_vecFindItem[" << g << "][" << l << "][" << c << "]=" << m_vecFindItem[g][l][c].intItem;
					//LOG4CPLUS_DEBUG(g_logger, ss.str());
					DDX_Check(pDX, m_vecFindItem[g][l][c].nID, m_vecFindItem[g][l][c].intItem);
				}

				if (m_vecFindItem[g][l][c].nType == CDlgTemplateBuilder::RADIOBUTTON)
				{
					//	-1 ��������û�� radio ��ѡ�� , 0 �����һ�� radio ѡ�У� 1 ���� �ڶ��� radio ѡ��
					if (m_vecFindItem[g][l][c].bKey)
					{
						// ���������еĵ�һ�� Radio ��Ҫ DDX_Radio 
						DDX_Radio(pDX, m_vecFindItem[g][l][c].nID, m_vecFindItem[g][l][c].intItem);
					}
				}

				if (m_vecFindItem[g][l][c].nType == CDlgTemplateBuilder::SPIN_EDIT)
				{
					DDX_Text(pDX, m_vecFindItem[g][l][c].nID, m_vecFindItem[g][l][c].strItem);
					if (m_vecFindItem[g][l][c].dbMin < m_vecFindItem[g][l][c].dbMax)
					{
						double dbVal = String2Double(m_vecFindItem[g][l][c].strItem.GetBuffer());
						DDV_MinMaxDouble(pDX, dbVal, m_vecFindItem[g][l][c].dbMin, m_vecFindItem[g][l][c].dbMax);//У�����ֵ����Сֵ
					}
					if (m_vecFindItem[g][l][c].nMin < m_vecFindItem[g][l][c].nMax)
					{
						int nVal = atoi(m_vecFindItem[g][l][c].strItem.GetBuffer());
						DDV_MinMaxDouble(pDX, nVal, m_vecFindItem[g][l][c].nMin, m_vecFindItem[g][l][c].nMax);//У�����ֵ����Сֵ
					}
				}
			}
		}
	}
}

//	������ӿؼ��ĺ���
void CDyncItemGroupDlg::PositionItemRect(CRect rcItem, int nGroup, int nLine, int nCol)
{
	CRect rc;
	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::STATIC)
	{
		rc.top = rcItem.top;
		rc.bottom = rc.top + CYSTATIC;
		rc.left = rcItem.left;
		rc.right = rc.left + CXSTATIC;

		m_dtb.AddItem(CDlgTemplateBuilder::STATIC,		// add it
			WS_VISIBLE | WS_CHILD | SS_RIGHT, rc, m_vecFindItem[nGroup][nLine][nCol].caption);
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::EDIT)
	{
		rc.top = rcItem.top;
		rc.bottom = rc.top + CYCAPTION;
		rc.left = rcItem.left;
		rc.right = rc.left + CXCAPTION;

		m_dtb.AddItem(CDlgTemplateBuilder::STATIC,		// add it
			WS_VISIBLE | WS_CHILD | SS_RIGHT, rc, m_vecFindItem[nGroup][nLine][nCol].caption);

		rc.top = rcItem.top;
		rc.bottom = rc.top + CYEDIT;
		rc.left = rcItem.left + CXCAPTION + CXSPACE;
		rc.right = rc.left + CXEDIT;
		m_dtb.AddItem(CDlgTemplateBuilder::EDIT, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP, 
			rc, m_vecFindItem[nGroup][nLine][nCol].strItem, m_vecFindItem[nGroup][nLine][nCol].nID);

	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::COMBOBOX)
	{
		rc.top = rcItem.top;
		rc.bottom = rc.top + CYCAPTION;
		rc.left = rcItem.left;
		rc.right = rc.left + CXCAPTION;

		m_dtb.AddItem(CDlgTemplateBuilder::STATIC,		// add it
			WS_VISIBLE | WS_CHILD | SS_RIGHT, rc, m_vecFindItem[nGroup][nLine][nCol].caption);

		rc.top = rcItem.top;
		rc.bottom = rc.top + CYCOMBOX;  
		rc.bottom += 4 * CYCOMBOX;			//	�������� �Ա��ܹ���ʾ ������
		rc.left = rcItem.left + CXCAPTION + CXSPACE;
		rc.right = rc.left + CXCOMBOX;
		m_dtb.AddItem(CDlgTemplateBuilder::COMBOBOX, WS_VISIBLE | WS_CHILD | WS_BORDER | CBS_DROPDOWNLIST | WS_TABSTOP,
			rc, "123;234;567;", m_vecFindItem[nGroup][nLine][nCol].nID);

	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::CHECKBOX)
	{
		rc.top = rcItem.top;
		rc.bottom = rc.top + CYCHECKBOX;
		rc.left = rcItem.left;
		rc.right = rc.left + CXCHECKBOX;

		if (BS_PUSHLIKE == (BS_PUSHLIKE & m_vecFindItem[nGroup][nLine][nCol].dwStyle))
			rc.right += CXCHECKBOX;

		DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTOCHECKBOX | m_vecFindItem[nGroup][nLine][nCol].dwStyle;

		m_dtb.AddItem(CDlgTemplateBuilder::BUTTON, dwStyle,
			rc, m_vecFindItem[nGroup][nLine][nCol].caption, m_vecFindItem[nGroup][nLine][nCol].nID);
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::RADIOBUTTON)
	{
		rc.top = rcItem.top;
		rc.bottom = rc.top + CYRADIO;
		rc.left = rcItem.left;
		rc.right = rc.left + CXRADIO;

		//	Radio �ؼ��ǰ��� Tab ����˳����з���ģ� Tab ����˳��ǰ�Ŀؼ��� rc �ļ��е� DIALOGEX ����������
		if (m_vecFindItem[nGroup][nLine][nCol].bKey)
		{
			//	˵��Ϊ�����е� ��һ�� Radio ��������� WS_GROUP
			m_dtb.AddItem(CDlgTemplateBuilder::BUTTON, WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
				rc, m_vecFindItem[nGroup][nLine][nCol].caption, m_vecFindItem[nGroup][nLine][nCol].nID);
		}
		else
		{
			m_dtb.AddItem(CDlgTemplateBuilder::BUTTON, WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON ,
				rc, m_vecFindItem[nGroup][nLine][nCol].caption, m_vecFindItem[nGroup][nLine][nCol].nID);
		}

		/*stringstream ss;
		ss << nGroup << "," << nLine << "," << nCol << ", RADIOBUTTON";
		LOG4CPLUS_INFO(g_logger, ss.str());*/
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::ICON)
	{
		rc.top = rcItem.top;
		rc.bottom = rc.top + CYICON;
		rc.left = rcItem.left;
		rc.right = rc.left + CXICON;

		if (m_vecFindItem[nGroup][nLine][nCol].intItem) {
			if (m_vecFindItem[nGroup][nLine][nCol].intItem >= (WORD)IDI_APPLICATION) {
				// if using a system icon, I load it here and set it in OnInitDialog
				// because can't specify system icon in template, only icons from
				// application resource file.
				m_vecFindItem[nGroup][nLine][nCol].hicon = ::LoadIcon(NULL, MAKEINTRESOURCE(m_vecFindItem[nGroup][nLine][nCol].intItem));
				m_vecFindItem[nGroup][nLine][nCol].intItem = 0;
			}
			else {
				m_vecFindItem[nGroup][nLine][nCol].hicon = NULL;
			}

			m_dtb.AddItem(CDlgTemplateBuilder::STATIC, WS_VISIBLE | WS_CHILD | SS_LEFT | SS_ICON,
				rc, m_vecFindItem[nGroup][nLine][nCol].intItem, m_vecFindItem[nGroup][nLine][nCol].nID);

		}
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::CONTROL)
	{
		rc.top = rcItem.top;
		rc.bottom = rc.top + CYEDIT;
		rc.left = rcItem.left;
		rc.right = rc.left + CXEDIT;

		// msctls_updown32   SysDateTimePick32

		m_dtb.AddItem("msctls_updown32", WS_VISIBLE | WS_CHILD | WS_TABSTOP ,
			rc, m_vecFindItem[nGroup][nLine][nCol].caption, m_vecFindItem[nGroup][nLine][nCol].nID);
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::SPIN_EDIT)
	{
		rc.top = rcItem.top;
		rc.bottom = rc.top + CYCAPTION;
		rc.left = rcItem.left;
		rc.right = rc.left + CXCAPTION;

		m_dtb.AddItem(CDlgTemplateBuilder::STATIC,		// add it
			WS_VISIBLE | WS_CHILD | SS_RIGHT, rc, m_vecFindItem[nGroup][nLine][nCol].caption);

		rc.top = rcItem.top;
		rc.bottom = rc.top + CYEDIT;
		rc.left = rcItem.left + CXCAPTION + CXSPACE;
		rc.right = rc.left + CXEDIT;
		m_dtb.AddItem(CDlgTemplateBuilder::EDIT, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | WS_TABSTOP,
			rc, m_vecFindItem[nGroup][nLine][nCol].strItem, m_vecFindItem[nGroup][nLine][nCol].nID);

		rc.top = rcItem.top;
		rc.bottom = rc.top + CYEDIT;
		rc.left = rcItem.left + CXCAPTION + CXSPACE + CXEDIT;
		rc.right = rc.left + 12;
		m_dtb.AddItem("msctls_updown32", WS_VISIBLE | WS_CHILD | UDS_SETBUDDYINT | UDS_ARROWKEYS,
			rc, m_vecFindItem[nGroup][nLine][nCol].strItem, m_vecFindItem[nGroup][nLine][nCol].nID1);

	}
		
}


CSize CDyncItemGroupDlg::CalcItemRect(int nGroup, int nLine, int nCol)
{
	int nWidth = 0;
	int nHeight = 0;
	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::STATIC)
	{
		nWidth = CXSTATIC + CXSPACE;
		nHeight = CYSTATIC;
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::EDIT)
	{
		nWidth = CXCAPTION + CXSPACE + CXEDIT;
		nHeight = CYCAPTION > CYEDIT ? CYCAPTION : CYEDIT;
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::COMBOBOX)
	{
		nWidth = CXCAPTION + CXSPACE + CXCOMBOX;
		nHeight = CYCAPTION > CYCOMBOX ? CYCAPTION : CYCOMBOX;
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::CHECKBOX)
	{
		nWidth = CXCHECKBOX;
		if(BS_PUSHLIKE == (BS_PUSHLIKE & m_vecFindItem[nGroup][nLine][nCol].dwStyle))
			nWidth += CXCHECKBOX;
		nHeight = CYCHECKBOX;
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::RADIOBUTTON)
	{
		nWidth = CXRADIO;
		nHeight = CYRADIO;
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::ICON)
	{
		nWidth = CXICON;
		nHeight = CYICON;
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::CONTROL)
	{
		nWidth = CXEDIT;
		nHeight = CYEDIT;
	}

	if (m_vecFindItem[nGroup][nLine][nCol].nType == CDlgTemplateBuilder::SPIN_EDIT)
	{
		nWidth = CXCAPTION + CXSPACE + CXEDIT + 12;
		nHeight = CYCAPTION > CYEDIT ? CYCAPTION : CYEDIT;
	}

	CSize  sz(nWidth, nHeight);
	return sz;
}


//////////////////
// Initialize dialog: if I loaded a system icon, set it in static control.
//
BOOL CDyncItemGroupDlg::OnInitDialog()
{
	for (int g = 0; g < MAX_GROUP; g++)
	{
		for (int l = 0; l < MAX_LINE; l++)
		{
			for (int c = 0; c < MAX_COLUMN; c++)
			{
				if (m_vecFindItem[g][l][c].nType == CDlgTemplateBuilder::COMBOBOX)
				{
					CComboBox * pComBox = (CComboBox*)GetDlgItem(m_vecFindItem[g][l][c].nID);
					if (pComBox)
					{
						pComBox->ResetContent();

						string str = m_vecFindItem[g][l][c].strData.GetBuffer();
						vector<string> vec;
						splitString(str, ";", vec);
						for (int k = 0; k < vec.size(); k++)
						{
							pComBox->AddString(vec[k].c_str());
						}
					}
				}

				if (m_vecFindItem[g][l][c].nType == CDlgTemplateBuilder::ICON)
				{
					CStatic* pStatic = (CStatic*)GetDlgItem(m_vecFindItem[g][l][c].nID);
					ASSERT(pStatic);
					if (m_vecFindItem[g][l][c].hicon)
					{
						pStatic->SetIcon(m_vecFindItem[g][l][c].hicon);
						SetIcon(m_vecFindItem[g][l][c].hicon, TRUE);		// Set big icon
						SetIcon(m_vecFindItem[g][l][c].hicon, FALSE);		// Set small icon
					}

				}

				if (m_vecFindItem[g][l][c].nType == CDlgTemplateBuilder::SPIN_EDIT)
				{
					CSpinButtonCtrl * pSpin = (CSpinButtonCtrl*)GetDlgItem(m_vecFindItem[g][l][c].nID1);
					pSpin->SetBuddy(GetDlgItem(m_vecFindItem[g][l][c].nID));
					pSpin->SetRange(0, 100);
					pSpin->SetPos(11);
				}
			}
		}
	}


	// ���� DoDataExchange �� OnInitDialog �б�����
	BOOL bResult = CDialog::OnInitDialog();

	return bResult;
}


void CDyncItemGroupDlg::PositionLineRect(CRect rcLine, int groupid, int lineid)
{
	int nY = rcLine.top;
	int nX = rcLine.left;
	for (int i = 0; i< MAX_COLUMN; i++)
	{
		CSize rc = CalcItemRect(groupid, lineid, i);
		if (rc.cx > 0 && rc.cy > 0)
		{
			CRect rc1;
			rc1.top = nY;
			rc1.bottom = rc1.top + rc.cy;
			rc1.left = nX;
			rc1.right = rc1.left + rc.cx;
			PositionItemRect(rc1, groupid,  lineid, i);
			nX += rc.cx + CXSPACE;
		}
	}
}

void CDyncItemGroupDlg::PositionGroupRect(CRect rcGroup, int nGroup)
{

	/*m_vecFindItem*/
	m_dtb.AddItem(CDlgTemplateBuilder::BUTTON,		// add Cancel button
		WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_GROUPBOX, rcGroup, _T(""));

	int nY = rcGroup.top + GROUPMARGIN;
	int nX = rcGroup.left + GROUPMARGIN;
	for (int i = 0; i < MAX_LINE; i++)
	{
		CSize rc = CalcLineRect(nGroup, i);
		if (rc.cx > 0 && rc.cy > 0)
		{
			CRect rc1;
			rc1.top = nY;
			rc1.bottom = rc1.top + rc.cy;
			rc1.left = nX;
			rc1.right = rc1.left + rc.cx;
			PositionLineRect(rc1, nGroup, i);
			nY += rc.cy + CYSPACE;
		}
	}
}


CSize CDyncItemGroupDlg::CalcLineRect(int nGroup, int nLine)
{
	int nWidth = 0;
	int nHeigth = 0;
	for (int i = 0; i < MAX_COLUMN; i++)
	{
		if (m_vecFindItem[nGroup][nLine][i].nType > 0)
		{
			//	��һ�в��Ӽ��
			if (nWidth>0)
				nWidth += CXSPACE;
			CSize sz = CalcItemRect(nGroup, nLine, i);
			nHeigth = sz.cy > nHeigth ? sz.cy : nHeigth;
			nWidth += sz.cx;
		}
	}

	CSize  sz(nWidth, nHeigth);
	return sz;
}

CSize CDyncItemGroupDlg::CalcGroupRect(int nGroup)
{
	int nWidth = 0;
	int nHeight = 0;
	for (int i = 0; i < MAX_LINE; i++)
	{
		CSize rc = CalcLineRect(nGroup, i);
		if ( rc.cx > 0 && rc.cy >0 )
		{
			//	��һ��ǰ�����Ӽ��
			if (nHeight > 0)
				nHeight += CYSPACE;
			nHeight += rc.cy;

			if(rc.cx > nWidth)
				nWidth = rc.cx;
		}
	}

	if (nWidth > 0 && nHeight > 0)
	{
		nWidth += 2 * GROUPMARGIN;
		nHeight += 2 * GROUPMARGIN;
	}
	CSize  sz(nWidth, nHeight);
	return sz;
}


//////////////////
// Create string dialog. If no icon specified, use IDI_QUESTION. Note that
// the order in which the controls are added is the TAB order.
//

// �Ի��򴴽��󣬸ú���Ӧ�ô��ֶ�����
BOOL CDyncItemGroupDlg::Init(LPCTSTR caption, LPCTSTR prompt,  CWnd* pParent, WORD nIDIcon)
{
	
	CDlgTemplateBuilder& dtb = m_dtb;
	// create dialog header
	
	CSize lineSize[MAX_GROUP];

	for (int i = 0; i < MAX_GROUP; i++)
	{
		lineSize[i].cx = 0;
		lineSize[i].cy = 0;
	}


	//	ȷ��ÿ�����У�group row����Ҫ�ĳߴ�
	for (int i = 0; i < MAX_GROUP; i++)
	{
		CSize rc = CalcGroupRect(i);

		if (rc.cx > 0 && rc.cy > 0)
		{
			//	��Group ��������
			int lineNo = i / GROUP_NUM_PER_LINE;

			if (lineSize[lineNo].cx > 0)
				lineSize[lineNo].cx += CXSPACE;
			lineSize[lineNo].cx += rc.cx;

			if (rc.cy > lineSize[lineNo].cy)
				lineSize[lineNo].cy = rc.cy;
		}
	}

	//	��ȷ���Ի���� ��С
	int nWidth = 0;
	int nHeight = 0;
	for (int i = 0; i < MAX_GROUP; i++)
	{
		CSize rc = lineSize[i];
		if (rc.cx > 0 && rc.cy > 0)
		{
			//	��һ�� group row ���Ӽ��
			if (nHeight >0)
				nHeight += CYSPACE;

			nHeight += rc.cy;

			if (rc.cx > nWidth)
				nWidth = rc.cx;
		}
	}

	int  nGroupHeight = nHeight;
	int  nGroupWidth = nWidth;
	nHeight += 2 * DLGMARGIN + CYSPACE + CYBUTTON; // ������ ��OK�� �� ��CANCEL�� ��ť
	nWidth += 2 * DLGMARGIN;
	CRect rc(CPoint(0, 0), CSize(nWidth, nHeight));

	DLGTEMPLATE* pTempl = dtb.Begin(WS_POPUPWINDOW | DS_MODALFRAME | WS_DLGFRAME, rc, caption);

	// ����ÿ�� Group Row �е�ÿ�� Group Ӧ��ƽ�������Ŀ��
	int nMakeup[MAX_GROUP];
	for (int i = 0; i < MAX_GROUP; i++)
		nMakeup[i] = 0;

	for (int i = 0; i < MAX_GROUP; i++)
	{
		CSize rc = lineSize[i];
		if (rc.cx > 0 && rc.cy > 0)
		{
			nMakeup[i] = (nGroupWidth - rc.cx) / GROUP_NUM_PER_LINE;
		}
	}

	// ����ÿ�� Group �ķ���λ��
	int nX = DLGMARGIN;
	int nY = DLGMARGIN;
	int	nLineNo = 0;
	for (int i = 0; i < MAX_GROUP; i++)
	{
		CSize rc = CalcGroupRect(i);
		if (rc.cx > 0 && rc.cy > 0)
		{
			//	��Group ��������
			int lineNo = i / GROUP_NUM_PER_LINE;
			if (lineNo > nLineNo)
			{
				//	���д���
				nY += lineSize[nLineNo].cy + CYSPACE;
				nLineNo = lineNo;

				nX = DLGMARGIN;
			}


			{
				CRect rc1;
				rc1.top = nY;
				rc1.bottom = rc1.top + lineSize[nLineNo].cy;
				rc1.left = nX;
				rc1.right = rc1.left + rc.cx + nMakeup[nLineNo];
				PositionGroupRect(rc1, i);
				nX += rc.cx + nMakeup[nLineNo] +  CXSPACE;
			}
		}
	}		
		
	// add OK button
	rc.top = DLGMARGIN + nGroupHeight + CYSPACE;
	rc.bottom = rc.top + CYBUTTON;
	rc.right = DLGMARGIN + nGroupWidth - CXBUTTON - CXSPACE;
	rc.left = rc.right - CXBUTTON;
	dtb.AddItem(CDlgTemplateBuilder::BUTTON,		// add it
		WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_DEFPUSHBUTTON, rc, _T("&ȷ��"), IDOK);

	// add Cancel button
	rc.right = DLGMARGIN + nGroupWidth;
	rc.left = rc.right - CXBUTTON;
	dtb.AddItem(CDlgTemplateBuilder::BUTTON, 
		WS_VISIBLE|WS_CHILD|WS_TABSTOP , rc, _T("&ȡ��"), IDCANCEL);

	return InitModalIndirect(pTempl, pParent);

}



BEGIN_MESSAGE_MAP(CDyncItemGroupDlg, CDialog)
	//{{AFX_MSG_MAP(CStringDialog)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////
// User pressed OK: check for empty string if required flag is set.
//
void CDyncItemGroupDlg::OnOK()
{
	//	CDialog::OnOK() �лᱻ����, �ʺ���
	// UpdateData(TRUE);

	
	CDialog::OnOK();
}
