#ifndef ImageStructs_h__
#define ImageStructs_h__

#include <QtCore>
#include <QtGui>
#include "ImageMacros.h"

namespace ImageLib
{
	//��ȡ����
	struct stReadParam
	{
		stReadParam(){}
		stReadParam(const QString& path, bool isLocalFile, int limit = ImageLib::kInvalidSize)
			: limitSize(ImageLib::kInvalidSize)
		{
			if (isLocalFile)
			{
				fileUrl = QUrl::fromLocalFile(path);
			}
			else
			{
				fileUrl = QUrl(path);
			}
			
			limitSize = limit;
		}

		bool operator==(const stReadParam& other) const
		{
			return fileUrl == other.fileUrl;
		}

		QUrl fileUrl; //�ļ���url
		int limitSize; //���ƴ�С
	};

	//��ȡ���
	struct stReadResult
	{
		stReadResult()
			: isSuccess(false)
			, error(QImageReader::UnknownError)
		{}

		bool isSuccess; //�Ƿ�ɹ�
		QImageReader::ImageReaderError error; //����
	};

	//��ȡ����
	struct stWriteParam
	{
		stWriteParam(){}
		stWriteParam(const QString& filePath, int limit = ImageLib::kInvalidSize)
			: limitSize(ImageLib::kInvalidSize)
		{
			this->filePath = filePath;
			this->limitSize = limit;
		}

		QString filePath;
		int limitSize; //���ƴ�С
	};


	//дͼƬ���
	struct stWriteResult
	{
		stWriteResult()
			: isSuccess(false)
			, error(QImageWriter::UnknownError)
		{}

		bool isSuccess; //�Ƿ�ɹ�
		QImageWriter::ImageWriterError error; //����
	};
}

#endif // ImageStructs_h__
