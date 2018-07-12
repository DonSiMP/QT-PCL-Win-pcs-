#include "LASFile.h"
#include "pcsLogs.h"

//Qt
#include <QMessageBox>
#include <QFileInfo>
#include <QSharedPointer> //����ָ��
//System
#include <exception>������ //�쳣������
#include <fstream>		   // std::ifstream
#include <iomanip>
#include <sstream>
//LASlib
#include <liblas/point.hpp>
#include <liblas/reader.hpp>
#include <liblas/writer.hpp>
#include <liblas/factory.hpp>	// liblas::ReaderFactory

class exception;

PCS_File_Error LASFile::LoadFile()
{
	QString filename;
	std::ifstream ifs;
	ifs.open(filename.toStdString(), std::ios::in | std::ios::binary);
	if (ifs.fail())
		return PCS_FERR_READING;
	/*if (ifs == NULL)
		QMessageBox::critical(NULL, "critical", "Content", QMessageBox::Yes, QMessageBox::Yes);
		return;*/
	
	/*liblas::ReaderFactory rf;
	liblas::Reader reader = rf.CreateWithStream(ifs);*/
	liblas::Reader reader(liblas::ReaderFactory().CreateWithStream(ifs));
	try
	{
		liblas::Header const& header =  reader.GetHeader();
		pcsLogs::Print(QString("[LAS] %1 - signature: %2").arg(filename).arg(header.GetFileSignature().c_str()));
		double maxX = header.GetMaxX();
		double minX = header.GetMinX();
		double maxY = header.GetMaxY();
		double minY = header.GetMinY();
		double maxZ = header.GetMaxZ();
		double minZ = header.GetMinZ();
		int n = header.GetPointRecordsCount();//��ȡ�ܵĵ���
		double x = 0, y = 0, z = 0;
		while (reader.ReadNextPoint())//ѭ����ȡlas�ļ��еĵ�
		{
			liblas::Point const& laspoint = reader.GetPoint();
			x = laspoint.GetX();
			y = laspoint.GetY();
			z = laspoint.GetZ();
		}
		ifs.close();
	}
	catch ( ... )
	{
		ifs.close();
		return PCS_FERR_READING;
	}

}
