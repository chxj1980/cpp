#pragma once
#include "FontLib.h"
class TTF_table;
//CAD ʸ������ 
class fontchrlink
{
public://����	
	unsigned short  code; //������	
	short  defsz; //���ݵĳ��ȣ�def �ĳ��ȣ�	
	char  *def;   //ʸ��������Ϣ

	float charWidth;//�ֿ�
	char* symbolName;//������
	CharData* m_dataPtr;
public:
	fontchrlink(void);
	~fontchrlink(void);
	//��������Ϣת��Ϊʸ������
	bool ShapeCreateVec(CharData* pOut);
	static long	gr_parsetext(                       // R:  Unicode of character of control code
		_TCHAR**                cpp,    // IO: String of text that should be parsed
		UINT                    dwg_code_page,  // for converting from multibyte to Unicode
		FontType   type,    // I:  Font type. May be: SHAPE_1_0, SHAPE_1_1, UNIFONT, BIGFONT, TRUETYPE
		TTF_table* pFontTable
		);
};
