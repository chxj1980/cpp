#include "StdAfx.h"
#include "TextExtractorEx.h"


//////////////////////////////////////////////////////////////////////////


bool comp(const CLineOrCell &lhs, const CLineOrCell &rhs)
{
	double left_y = lhs.y;
	double left_x = lhs.x;

	double right_y = rhs.y;
	double right_x = rhs.x;
	if(lhs.rect.GetWidth()>0)
	{
		left_y = lhs.rect.GetBottom();
		left_x = lhs.rect.GetLeft();
	}
	if(rhs.rect.GetWidth()>0)
	{
		right_y = rhs.rect.GetBottom();
		right_x = rhs.rect.GetLeft();
	}

	if(abs(left_y - right_y) <=1)
	{
		if(left_x < right_x)
			return true;
		else 
			return false;
	}
	else if(left_y > right_y)
		return true;
	else 
		return false;
}

void SearchSerialNumber(string content, int & nSerial, int & nType)
{
	string Model[] = { "һ��", "����", "����", "�ġ�", "�塢", "����", "�ߡ�", "�ˡ�", "�š�","ʮ��", 
						"1��", "2��","3��","4��","5��","6��","7��","8��","9��","10��",
						"11��", "12��","13��","14��","15��","16��","17��","18��","19��","20��",
						"T1��", "T2��","T3��","T4��","T5��","T6��","T7��","T8��","T9��","T10��", 
						"T11��", "T12��","T13��","T14��","T15��","T16��","T17��","T18��","T19��","T20��",
						"��1��","��2��","��3��","��4��","��5��","��6��","��7��","��8��","��9��","��10��",
						"��һ��","������","������","���ģ�","���壩","������","���ߣ�","���ˣ�","���ţ�","��ʮ��" };

	int  Serail[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10 ,
				1, 2, 3, 4, 5, 6, 7, 8, 9 ,10,
				11, 12, 13, 14, 15, 16, 17, 18, 19 ,20,
				1, 2, 3, 4, 5, 6, 7, 8, 9 ,10, 
				11, 12, 13, 14, 15, 16, 17, 18, 19 ,20,
				1, 2, 3, 4, 5, 6, 7, 8, 9 ,10, 
				1, 2, 3, 4, 5, 6, 7, 8, 9 ,10 };

	int	 Type[] = { 1,1,1,1,1,1,1,1, 1, 1,
				2,2,2,2,2,2,2,2, 2,2,
				2,2,2,2,2,2,2,2, 2,2,
				3,3,3,3,3,3,3,3, 3,3,
				3,3,3,3,3,3,3,3, 3,3,
				4,4,4,4,4,4,4,4, 4,4,
				5,5,5,5,5,5,5,5, 5,5 };

	nSerial = 0; nType = 0;

	for(int i= 0; i< 70; i++)
	{
		string::size_type pos = trimString(content).find(Model[i]);
		if(pos!=string::npos && pos==0)
		{
			nSerial = Serail[i];	
			nType = Type[i];
			break;
		}
	}
}



//////////////////////////////////////////////////////////////////////////


void CPageContent::AddLineText(double x, double y, string content, double right_x, string font_name, \
							   double font_size, double renderingMode)
{
	list<CLineOrCell>::iterator it = m_Lines.begin();
	for(; it!=m_Lines.end(); it++)
	{
		if(abs(it->y - y)<=1)
			break;
	}
	if(it==m_Lines.end())
	{
		if(trimString(content).empty()==false)
		{
			CLineOrCell line;
			line.x = x;
			line.y = y;
			line.last_x = x;
			line.max_right_x = right_x;
			line.last_right_x = right_x;
			line.content = content;
			line.font_name = font_name;
			line.font_size = font_size;
			line.trender = renderingMode;
			m_Lines.push_back(line);

			if(font_size > max_font_size)	max_font_size = font_size;
			if(font_size < min_font_size)	min_font_size = font_size;
			if(x > max_x ) max_x = x;
			if(y < min_x ) min_x = x;
		}
	}
	else
	{
		it->max_right_x = right_x;
		it->last_right_x = right_x;
		it->content += content;
	}
}

void CPageContent::AddTableText(double x, double y, PdfRect cellRect, string content)
{
	list<CLineOrCell>::iterator it = m_Lines.begin();
	for(; it!=m_Lines.end(); it++)
	{
		if(abs(it->rect.GetLeft() - cellRect.GetLeft()) <=1 &&
			abs(it->rect.GetBottom() - cellRect.GetBottom()) <=1 &&
			abs(it->rect.GetWidth() - cellRect.GetWidth()) <=1 &&
			abs(it->rect.GetHeight() - cellRect.GetHeight()) <=1)
			break;
	}
	if(it==m_Lines.end())
	{
		CLineOrCell cell;
		cell.rect = cellRect;
		cell.content = content;
		cell.x = x;
		cell.y = y;
		m_Lines.push_back(cell);
	}
	else
	{
		it->x = x;
		it->y = y;
		it->content += content;
	}
}

//////////////////////////////////////////////////////////////////////////

TextExtractorEx::TextExtractorEx()
{

}

TextExtractorEx::~TextExtractorEx()
{
}

void TextExtractorEx::Init( const char* pszInput , long lLen)
{
    if( !pszInput )
    {
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }


    //PdfMemDocument document( pszInput );

	PdfMemDocument document;

	document.Load(pszInput, lLen, false);
	PdfObject * pobj = document.GetCatalog();


	//////////////////////////////////////////////////////////////////////////
	//	�� pdf �е�ÿ��ҳ�水���н��� �ֽ�

    int nCount = document.GetPageCount();
    for( int i=0; i<nCount; i++ ) 
    {
		CPageContent p;
		m_mapPageContent[i] = p; 
		m_nCurrentPage = i;

        PdfPage* pPage = document.GetPage( i );
        this->ExtractText( &document, pPage );

		m_mapPageContent[i].m_Lines.sort(comp);
    }

	

	//////////////////////////////////////////////////////////////////////////
	//	��ÿ���н��ж���Ĺ鲢�� �Ա���е�Ԫ��ת��Ϊ����
	m_lstSegment.clear();

	//	�����Ԫ���� �鲢�����
	m_nTable = 0;
	double nWidthOfLastCell = 0;

	vector<CLineOrCell>	vecColumn;		//	�����ͷ�� ��Ԫ��
	vector<CLineOrCell>	vecRow;
	vector<CLineOrCell>	vecCell;

	for(int i=0; i<nCount; i++)
	{
		list<CLineOrCell>::iterator it = m_mapPageContent[i].m_Lines.begin();
		for(; it!=m_mapPageContent[i].m_Lines.end(); it++)
		{
			CLineOrCell ll = *it;

			if(ll.rect.GetWidth() > 0)
			{

				//	�Ա��Ԫ���й鲢���Ա��ϲ� �Լ����д���
				if(m_mapTable.count(m_nTable)==0)
				{
					vector<CLineOrCell> vecTmp;
					m_mapTable[m_nTable] = vecTmp;
				}
				m_mapTable[m_nTable].insert(m_mapTable[m_nTable].end(), ll);

				//	�Թ�������д�����Ҫ��� ���������ع��桱
				vecCell.insert(vecCell.end(), ll);
				int  nSize = vecColumn.size();
				if(nSize==0)
				{
					vecColumn.insert(vecColumn.end(), ll);
				}
				else if( abs(vecColumn[nSize-1].rect.GetBottom() + vecColumn[nSize-1].rect.GetHeight() \
					- ll.rect.GetBottom() - ll.rect.GetHeight())<1 || 
					abs(vecColumn[nSize-1].rect.GetBottom() - ll.rect.GetBottom())<1)
				{
					// Ϊ�˴������ϳ�Ͷ��ҵ���ı�ͷ���ϵ׻��µ���һ����ȣ�����Ϊ�Ǳ�ͷ
					vecColumn.insert(vecColumn.end(), ll);
				}
				else 
				{
					//	��ѯ�������ߵ�λ��
					double minLeft = 10000;
					for(int j = 0; j< vecColumn.size(); j++)
					{
						if(vecColumn[j].rect.GetLeft() < minLeft) 
							minLeft = vecColumn[j].rect.GetLeft();
					}
					if( abs(minLeft - ll.rect.GetLeft())<1)
						vecRow.insert(vecRow.end(), ll);
				}
			}
			else
			{
				if(vecColumn.size()>0)
				{
					//	ȥ�����ϱ�ͷ�е� �ص�����, �ӵ�һ����ͷ��ʼ
					int nFound = 0;
					do{
						int i=0;
						for(; i< vecColumn.size(); i++)
						{
							if(vecColumn[nFound].rect.GetBottom() - vecColumn[i].rect.GetBottom()>1)
								break;
						}
						if(i< vecColumn.size())
						{
							vecColumn.erase(vecColumn.begin() + nFound);
							if(nFound == vecColumn.size())
								break;
						}
						else if(nFound< vecColumn.size() -1 )
							nFound++;
						else
							break;

					}while(1);

					//	��������Ľ��
					for(int i=0; i<vecRow.size(); i++)
					{
						char tmp[32] = { 0 };
						sprintf_s(tmp, 32, "T%d��", i + 1);
						string strRow = string(tmp) ;
						for(int j=0; j< vecColumn.size(); j++)
						{
							//	���ݱ�ͷ�ĺ����� �� �е������� ȷ����Ԫ��ĳߴ�
							PdfRect rc;
							rc.SetBottom(vecRow[i].rect.GetBottom() + 1);
							rc.SetLeft(vecColumn[j].rect.GetLeft() + 1);
							rc.SetWidth(vecColumn[j].rect.GetWidth() - 2);
							rc.SetHeight(vecRow[i].rect.GetHeight() - 2);

							for(int c = 0 ; c < vecCell.size(); c++)
							{
								PdfRect lltmp = vecCell[c].rect;
								lltmp.Intersect(rc);

								if(rc.GetBottom()==lltmp.GetBottom() &&
									rc.GetLeft() == lltmp.GetLeft() &&
									rc.GetWidth() == lltmp.GetWidth() &&
									rc.GetHeight() == lltmp.GetHeight())
								{
									//	����Ԫ�������ݵġ�����ת��Ϊ������
									string strTitle = vecColumn[j].content;
									strTitle = ReplaceString(strTitle, "                         ", "");
									strTitle = ReplaceString(strTitle, "          ", "");
									strTitle = ReplaceString(strTitle, " ", "");
									strTitle = ReplaceString(strTitle,_T("��"), "");
									strRow += strTitle + "<=>" + ReplaceString(vecCell[c].content,_T("��"),_T("��"));
									break;
								}
							}

							if(j< vecColumn.size()-1)
								strRow += _T("��");
							else
								strRow += _T("��");
							
						}

						//	����ÿ��
						CLineOrCell llRow;
						llRow.content = strRow;
						llRow.x = vecRow[i].rect.GetLeft();
						llRow.y = vecRow[i].rect.GetBottom();
						m_lstSegment.push_back(llRow);
						
					}

					vecColumn.clear();
					vecRow.clear();
					vecCell.clear();
				}
				

				if(trimString(ll.content).empty()==false)
				{
					if(m_lstSegment.empty())
					{
						m_lstSegment.push_back(ll);
					}
					else
					{
						int nSerailTmp, nTypeTmp;
						SearchSerialNumber(ll.content, nSerailTmp, nTypeTmp);
						list<CLineOrCell>::reverse_iterator it_segment = m_lstSegment.rbegin();
						if( abs(it_segment->font_size - ll.font_size) > 0.5		/*���巢�����Ա仯*/
							|| ll.x - it_segment->last_x > 3.0					/*��������*/ 
							|| ( it_segment->x == it_segment->last_x &&  abs(ll.x - it_segment->x) < 3.0) 
							||	it_segment->max_right_x - it_segment->last_right_x > 72.0	/*������������Խ϶�*/
							|| abs(it_segment->trender - ll.trender) > 1 /*��ʾ��ʽ�������Ա仯*/ 
							|| nTypeTmp > 0  /*����������С����*/ )
						{
							m_lstSegment.push_back(ll);
						}
						else
						{
							it_segment->last_x = ll.x;
							it_segment->last_right_x = ll.last_right_x;
							it_segment->content += ll.content;
							if(ll.max_right_x > it_segment->max_right_x)
								it_segment->max_right_x = ll.max_right_x;
						}
					}
				}

			}	

			//	˵���ñ������� �����Ŀ + 1
			if(nWidthOfLastCell>0 && ll.rect.GetWidth()==0)
			{
				m_nTable ++;
			}

			nWidthOfLastCell = ll.rect.GetWidth();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//	����ƪ�����е�ÿ������в�ηֽ�
	m_pdf.clear();	
		
	
	list<CLineOrCell>::iterator it = m_lstSegment.begin();
	for(; it!=m_lstSegment.end(); it++)
	{
		//	����Ѿ��������Ľ��
		int nSerailLast = 0 ,nTypeLast = 0;
		CLineOrCell last;
		if(m_pdf.size()>0)
		{
			last = m_pdf[m_pdf.size()-1];
			SearchSerialNumber(last.content, nSerailLast, nTypeLast);
		}

		//	Ҫ������½��
		CLineOrCell ll = *it;
		int nSerail = 0 ,nType = 0;
		SearchSerialNumber(ll.content, nSerail, nType );

		if(nType == nTypeLast)
		{
			//	��Ϊǰһ�����ġ��ֵܡ�������
			ll.parent = last.parent;
			m_pdf.insert(m_pdf.end(), ll);
		}
		else
		{
			if(nType>0 && nSerail ==1)
			{
				//	��Ϊǰһ�����ġ����ӡ�������
				ll.parent = m_pdf.size()-1;
				m_pdf.insert(m_pdf.end(), ll);
			}
			else if(nType>0 && nSerail >1)
			{
				//	����Ѱ�Ҹ���㣬��Ϊ���ġ����ӡ�������
				int nParent = m_pdf[m_pdf.size()-1].parent;
				while(nParent>=0)
				{
					CLineOrCell tmp = m_pdf[nParent];
					int nSerailTmp = 0 ,nTypeTmp = 0;
					SearchSerialNumber(tmp.content, nSerailTmp, nTypeTmp);
					nParent = tmp.parent;
					if(nType == nTypeTmp && nSerailTmp < nSerail)
					{
						break;
					}
				}
				if(nParent<0)	nParent =0;
								
				ll.parent = nParent;
				m_pdf.insert(m_pdf.end(), ll);
			}
			else
			{
				//	��Ϊǰһ�����ġ��ֵܡ�������

				ll.parent = m_pdf.size()-1;
				m_pdf.insert(m_pdf.end(), ll);
			}
		}
		
	}

	int nEnd = 1;
}

void TextExtractorEx::ExtractText( PdfMemDocument* pDocument, PdfPage* pPage ) 
{
    const char*      pszToken = NULL;
    PdfVariant       var;
    EPdfContentsType eType;

	PdfRect rc = pPage->GetMediaBox();

    PdfContentsTokenizer tokenizer( pPage );


	Matrix	tlm(3, 3);		//	�о���
	Matrix	tm(3,3);		//	�־���
	PdfRect currentRC;		//	��ǰ re

	//	graphic state ,�� q �� Q �����б��漰�ָ�
	CGraphicsState gs;
	gs.clippingPath = rc;

	
    double dCurPosX     = 0.0;
    double dCurPosY     = 0.0;
    bool   bTextBlock   = false;
    PdfFont* pCurFont   = NULL;

	string	strNameOfBDC = "";
	bool   bFirstString = true;

    std::stack<PdfVariant>		stack;
	std::stack<CGraphicsState>	statckGS;

	
    while( tokenizer.ReadNext( eType, pszToken, var ) )
    {
		if( eType == ePdfContentsType_Keyword )
        {
			// support 'l' and 'm' tokens
            if( strcmp( pszToken, "l" ) == 0 || 
                strcmp( pszToken, "m" ) == 0 )
            {
                dCurPosX = stack.top().GetReal();
                stack.pop();
                dCurPosY = stack.top().GetReal();
                stack.pop();
            }
			else if( strcmp( pszToken, "re" ) == 0 ) 
			{
				double height = stack.top().GetReal();
				stack.pop();
				double width = stack.top().GetReal();
				stack.pop();
				double y = stack.top().GetReal();
				stack.pop();
				double x = stack.top().GetReal();
				stack.pop();

				currentRC.SetBottom(y);
				currentRC.SetLeft(x);
				currentRC.SetWidth(width);
				currentRC.SetHeight(height);

				/*char tmp[512] = { 0 };
				sprintf_s(tmp, 512, "<re-%.3f, %.3f, %.3f, %.3f>", x, y, x + width, y + height );
				fwrite(tmp,1,strlen(tmp) ,fp);*/
			}
			else if( strcmp( pszToken, "Tc" ) == 0 )
			{
				gs.tc = stack.top().GetReal();
				stack.pop();
			}
			else if( strcmp( pszToken, "Tw" ) == 0 )
			{
				gs.tw = stack.top().GetReal();
				stack.pop();
			}
			else if( strcmp( pszToken, "Tz" ) == 0 )
			{
				gs.th = stack.top().GetReal();
				stack.pop();
			}
			else if( strcmp( pszToken, "Tr" ) == 0 )
			{
				gs.trender = stack.top().GetReal();
				stack.pop();
			}
			else if( strcmp( pszToken, "TL" ) == 0 )
			{
				gs.tl = stack.top().GetReal();
				stack.pop();
			}
			else if( strcmp( pszToken, "q" ) == 0 ) 
			{
				statckGS.push(gs);
			}
			else if( strcmp( pszToken, "Q" ) == 0 ) 
			{
				gs = statckGS.top();
				statckGS.pop();
			}
			else if( strcmp( pszToken, "W" ) == 0  || strcmp( pszToken, "W*" ) == 0) 
			{
				gs.clippingPath.Intersect(currentRC);
			}
			
			else if( strcmp( pszToken, "n" ) == 0 ) 
			{
				currentRC.SetBottom(0);
				currentRC.SetLeft(0);
				currentRC.SetWidth(0);
				currentRC.SetHeight(0);
			}
			else if( strcmp( pszToken, "f" ) == 0 || strcmp( pszToken, "f*" ) == 0 || strcmp( pszToken, "F" ) == 0) 
			{
				currentRC.SetBottom(0);
				currentRC.SetLeft(0);
				currentRC.SetWidth(0);
				currentRC.SetHeight(0);
			}
			else if( strcmp( pszToken, "BT" ) == 0 ) 
            {
                bTextBlock   = true;     
                // BT does not reset font
                // pCurFont     = NULL;

				
				tlm << 1 << 0 << 0
					<< 0 << 1 << 0
					<< 0 << 0 << 1;

				tm = tlm;
            }
            else if( strcmp( pszToken, "ET" ) == 0 ) 
            {
                if( !bTextBlock ) 
                    fprintf( stderr, "WARNING: Found ET without BT!\n" );
            }
			else if(strcmp( pszToken , "BDC")==0)
			{
				stack.pop();
				PdfVariant  var1 = stack.top();

				if(var1.IsName())
				{
					const PdfName & nm =  var1.GetName();

					strNameOfBDC = nm.GetName();
				}
				if(var1.IsDictionary())
				{
					const PdfDictionary & dic =  var1.GetDictionary();
					TKeyMap keys =  dic.GetKeys();
					int k = 1;
				}
			}
			else if(strcmp( pszToken , "EMC")==0)
			{
				strNameOfBDC = "";
			}
			else
			{
				
			}

            if( bTextBlock && strNameOfBDC !="Artifact") 
            {
				
                if( strcmp( pszToken, "Tf" ) == 0 ) 
                {
					gs.tfs = stack.top().GetReal();
                    stack.pop();		//	�����С
                    PdfName fontName = stack.top().GetName();	//	��������
					stack.pop();
					gs.tfont = fontName.GetName();

                    PdfObject* pFont = pPage->GetFromResources( PdfName("Font"), fontName );
					
                    if( !pFont ) 
                    {
                        PODOFO_RAISE_ERROR_INFO( ePdfError_InvalidHandle, "Cannot create font!" );
                    }

                    pCurFont = pDocument->GetFont( pFont );
                    if( !pCurFont ) 
                    {
                        fprintf( stderr, "WARNING: Unable to create font for object %i %i R\n",
                                 pFont->Reference().ObjectNumber(),
                                 pFont->Reference().GenerationNumber() );
                    }
                }
                else if( strcmp( pszToken, "Tj" ) == 0 ||
                         strcmp( pszToken, "'" ) == 0 ) 
                {
					//	Tj ��ǩǰ��ʱ �ı�����
					PdfString str = stack.top().GetString();
					stack.pop();

                    AddTextElement( tm, 0, pCurFont,  str, bFirstString, gs );
                    
                }
                else if( strcmp( pszToken, "\"" ) == 0 )
                {
					PdfString str = stack.top().GetString();
					stack.pop();
					gs.tc = stack.top().GetReal();
					stack.pop();	// remove char spacing from stack
					gs.tw = stack.top().GetReal();
					stack.pop();	// remove word spacing from stack

					Matrix lma(3, 3);
					lma << 1 << 0 << 0
						<< 0 << 1 << 0
						<< 0 << gs.tl << 1;

					tlm = lma * tlm;
					tm = tlm;

                    AddTextElement( tm, 0, pCurFont, str, bFirstString, gs );
                }
                else if( strcmp( pszToken, "TJ" ) == 0 ) 
                {
                    PdfArray array = stack.top().GetArray();
                    stack.pop();
                    
					double tj = 0.0;
                    for( int i=0; i<static_cast<int>(array.GetSize()); i++ ) 
                    {
                        if( array[i].IsString() || array[i].IsHexString() )
						{
							AddTextElement( tm, tj, pCurFont, array[i].GetString(), bFirstString , gs);
						}
						else if(array[i].IsNumber())
						{
							tj = array[i].GetReal();	
						}
						
                    }
                }
				else if( strcmp( pszToken, "Td" ) == 0 || strcmp( pszToken, "TD" ) == 0 ) 
				{
					double y = stack.top().GetReal();
					stack.pop();
					double x = stack.top().GetReal();
					stack.pop();

					if(strcmp( pszToken, "TD" ) == 0)
					{
						//	-ty   TL
						gs.tl = -y;
					}

					Matrix lma(3, 3);
					lma << 1 << 0 << 0
						<< 0 << 1 << 0
						<< x << y << 1;

					tlm = lma * tlm;
					tm = tlm;
				}
				else if( strcmp( pszToken, "Tm" ) == 0 ) 
				{
					double f = stack.top().GetReal();
					stack.pop();
					double e = stack.top().GetReal();
					stack.pop();
					double d = stack.top().GetReal();
					stack.pop();
					double c = stack.top().GetReal();
					stack.pop();
					double b = stack.top().GetReal();
					stack.pop();
					double a = stack.top().GetReal();
					stack.pop();

					tlm(1,1) = a;
					tlm(1,2) = b;
					tlm(2,1) = c;
					tlm(2,2) = d;
					tlm(3,1) = e;
					tlm(3,2) = f;

					tm = tlm;					
				}
				else if( strcmp( pszToken, "T*" ) == 0 )
				{
					Matrix lma(3, 3);
					lma << 1 << 0 << 0
						<< 0 << 1 << 0
						<< 0 << -gs.tl << 1;

					double yy = tlm(3,2);

					tlm = lma * tlm;

					yy = tlm(3,2);
					tm = tlm;
				}
				else if(strcmp(pszToken, "g") == 0)
				{
					//	SetGray
					stack.pop();
				}
				else if(strcmp(pszToken, "w") == 0)
				{
					//  setlineWidth
					stack.pop();
				}
				else
				{
					
				}
            }
        }
        else if ( eType == ePdfContentsType_Variant )
        {
            stack.push( var );
        }
        else
        {
            // Impossible; type must be keyword or variant
            PODOFO_RAISE_ERROR( ePdfError_InternalLogic );
        }
    }

	int kkk = 1;
}

void TextExtractorEx::AddTextElement( Matrix &tm,  double tj,
		PdfFont* pCurFont, const PdfString & rString, bool & bFirstString , CGraphicsState gs)
{
	if( !pCurFont ) 
    {
        fprintf( stderr, "WARNING: Found text but do not have a current font: %s\n", rString.GetString() );
        return;
    }

    if( !pCurFont->GetEncoding() ) 
    {
        fprintf( stderr, "WARNING: Found text but do not have a current encoding: %s\n", rString.GetString() );
        return;
    }

	// For now just write to console
	
	string strGbk;
	int nLen;

	if(rString.IsHex())
	{
		PdfString unicode = pCurFont->GetEncoding()->ConvertToUnicode( rString, pCurFont );
		strGbk = Utf8_GBK(unicode.GetStringUtf8());
		nLen = unicode.GetUnicodeLength();

		// /finalpage/2016-04-19/1202194215.PDF
		/*if(strGbk.find("����������")!=string::npos)
		{
			int url_UTF8_buffer_size = 1024;

			unsigned char url_UTF8[1024];
			memset(url_UTF8,0,1024);

			if(unicode.IsUnicode() )
			{
				int len = UnicodeToGBK( (wchar_t *)unicode.GetStringW().c_str(), url_UTF8, 1024);
				len++;
			}
		}*/
	}
	else
	{
		strGbk = rString.GetString();
		nLen = strGbk.length();
	}
	double displaceMent = /*pCurFont->GetFontMetrics()->CharWidth(0)*/ 1;
	double fontSize = pCurFont->GetFontSize();
	double tx = ((displaceMent - tj/1000) * gs.tfs + gs.tc + gs.tw ) * gs.th /100 * nLen;

	Matrix lma(3, 3);
	lma << 1 << 0 << 0
		<< 0 << 1 << 0
		<< tx << 0 << 1;

	lma = lma * tm;
   
	char tmp[512] = { 0 };
	if(gs.clippingPath.GetLeft()==0 && gs.clippingPath.GetBottom()==0)
	{
		// �����е�����
		
		m_mapPageContent[m_nCurrentPage].AddLineText( tm(3,1), tm(3,2), strGbk, 
			lma(3,1), gs.tfont, gs.tfs, gs.trender);
	}
	else
	{
		//	����е�����
		
		m_mapPageContent[m_nCurrentPage].AddTableText( tm(3,1), tm(3,2), gs.clippingPath, strGbk);
	}

	tm = lma;
	
	return ;
	//printf("%s", unicode.GetStringUtf8().c_str() );
}


