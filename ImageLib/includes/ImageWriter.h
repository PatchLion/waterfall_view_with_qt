#ifndef ImageWriter_h__
#define ImageWriter_h__

#include <QtCore>
#include <QtGui>

#include "ImageMacros.h"
#include "ImageStructs.h"

namespace ImageLib
{
	class CImageWriter
	{
	public:
		CImageWriter(){}
		CImageWriter(const ImageLib::stWriteParam& param);

	public:
		//加载图片
		void writeImage(const QImage& image, const ImageLib::stWriteParam& param);
		void writeImage(const QImage& image);

		//加载结果
		const ImageLib::stWriteResult& result() const { return m_result; }

	private:
		ImageLib::stWriteParam m_param;
		ImageLib::stWriteResult m_result;
	};
}

#endif // ImageWriter_h__
