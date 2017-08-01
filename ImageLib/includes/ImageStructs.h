#ifndef ImageStructs_h__
#define ImageStructs_h__

#include <QtCore>
#include <QtGui>
#include "ImageMacros.h"

namespace ImageLib
{
	//读取参数
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

		QUrl fileUrl; //文件的url
		int limitSize; //限制大小
	};

	//读取结果
	struct stReadResult
	{
		stReadResult()
			: isSuccess(false)
			, error(QImageReader::UnknownError)
		{}

		bool isSuccess; //是否成功
		QImageReader::ImageReaderError error; //错误
	};

	//读取参数
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
		int limitSize; //限制大小
	};


	//写图片结果
	struct stWriteResult
	{
		stWriteResult()
			: isSuccess(false)
			, error(QImageWriter::UnknownError)
		{}

		bool isSuccess; //是否成功
		QImageWriter::ImageWriterError error; //错误
	};
}

#endif // ImageStructs_h__
