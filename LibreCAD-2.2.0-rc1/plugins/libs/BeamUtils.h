
#ifndef BeamUtils_H
#define BeamUtils_H

#include "qc_plugininterface.h"
#include "document_interface.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>

#include "../libs/AnalyticGeometry.h"

class BeamBaseData {
	/**
	* Default constructor. Leaves the data object uninitialized.
	*/
public:
	BeamBaseData() {};

	QString name;				// ������
	QString prefix;				// ������ǰ׺
	QString bxh;				//  ����ߴ�
	QString steelTop;
	QString steelBottom;
	QString steelHooping;		//	����
	QString steelMiddle;		//	����

	vector<int>	floors;			//  ����¥����

								/*
								* ��ʵ��set�������ж�����Ԫ��a���²���Ԫ��b�Ƿ����ʱ������ô���ģ�
								* 1����a��Ϊ���������b��Ϊ�в����������ñȽϺ����������رȽ�ֵ
								* 2����b��Ϊ���������a��Ϊ�в��������ٵ���һ�αȽϺ����������رȽ�ֵ��
								* ���1��2�����ķ���ֵ����false������Ϊa��b����ȵģ���b���ᱻ����set�����У�
								* ���1��2�����ķ���ֵ����true������ܷ���δ֪��Ϊ����ˣ���סһ��׼����Զ�ñȽϺ�������ͬԪ�ط���false��
								*/
	bool operator<(const BeamBaseData & right) const   //����<�����
	{
		return this->name < right.name;
	};
};


void readBeamData(Document_Interface *doc, QString layerName, vector< BeamBaseData>& beams);
vector<BeamBaseData> mergeBeams(vector<BeamBaseData>& newBeams, vector<BeamBaseData>& oldBeams);
vector<BeamBaseData> writeBeamData(Document_Interface *doc, vector< BeamBaseData>& newBeams, QString layerName);
void newBeamGraph(std::vector<BeamBaseData>& beams, QString layerPrefix, QString graphId, Document_Interface *doc);
void newBeamTable(std::vector<BeamBaseData>& beams, QString layerPrefix, QString tableId, Document_Interface *doc);


#endif // LIST_H