// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FONTLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FONTLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once

#include "Array.h"
typedef xArray<float> vex2Ds;
class  CharData
{
public:
	CharData(){}
	GLYPHMETRICS m_charInfo;//������Ϣ
	xArray<vex2Ds> m_parts;
};

enum FontType {SHAPE_1_0, SHAPE_1_1, UNIFONT, BIGFONT, TRUETYPE};

class IFontBase {
public:	
	
	//���ܣ�����ɾ�����ͷſռ�
	virtual void Release()=0;
	virtual const char* GetName()=0;//����
	//���ܣ��������ļ��������ݵ��ڴ�
	//@fileName:�����ļ�����·��
	//@return:true-���سɹ���false-����ʧ��
	virtual bool LoadFromFile(const char* fileName,long styleNum=0x8602,HDC dc=NULL)=0;

	//���ܣ��������������ȡ�ֶ��ڵ�ʸ����Ϣ
	//@charCode:�ֱ��루֧�ֵ��ֽں�˫�ֽ����֣�
	//@pOut:�����ά�����б�(XY,XY��...)
	//@reurn:true-�����ɹ���false-��֧�ֵ����ֻ����ʧ��
	virtual CharData* GetCharData(unsigned short charCode)=0;

	//���ԣ���������
	virtual FontType get_FontType()=0;

	//���ԣ������и�
	virtual float Height()=0;
};


////Shape����
//class DISPLAYLIB_API Font_Shape:public IFontBase
//{
//
//};
//
