#pragma once

class fontchrlink;
//CAD�����д��������
class  ShapeFont
{
public:
	ShapeFont(void);
	~ShapeFont(void);
	bool Load(const char* fileName);
	void Display(CDC* pDC,unsigned short charCode,int orgX,int orgY);//���������������
	fontchrlink* GetFromCode(unsigned short code);//��������
	char GetFontType(){return m_type;}
	fontchrlink* GetFromName(const char* symbolName);//��������
	int FindCodeByName(const char* name);
	int Count(){return m_data.Count();}
	fontchrlink* Get(int i){return m_data[i];}
	int Height(){return m_height;}

	string Patch(unsigned short charCode,float orgX,float orgY,float scX,float scY);
	//string Patch(unsigned short charCode,float orgX,float orgY,float scX,float scY);

protected:
	bool ReadUnifont(CFile& pFile,char* head);
	bool ReadShapes(CFile& pFile,char* head);
	bool ReadBigfont(CFile& pFile,char* head);
	bool ReadSHP(CFile& pFile,char* head,int &fileType);
protected:
	char* m_desc;

	unsigned char           above,  /* Or height for extended bigfont */
		below;
	char                    modes;
	unsigned char           width;  /* Extended bigfont */
	char                    encoding;
	char m_type;

	char                    nesc;
	char                   *esc; 

	xArray<fontchrlink* > m_data;//���ݼ�¼
	int m_height;//����߶�
};
