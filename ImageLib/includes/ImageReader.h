#ifndef ImageReader_h__
#define ImageReader_h__

#include <QtCore>
#include <QtGui>

#include "ImageMacros.h"
#include "ImageStructs.h"

namespace ImageLib
{
	class CImageReader
	{
	public:
		CImageReader(){}
		CImageReader(const ImageLib::stReadParam& param);

	public:
		//加载图片
		void loadImage(QImage& image, const ImageLib::stReadParam& param);
		void loadImage(QImage& image);

		//加载结果
		const ImageLib::stReadResult& result() const { return m_result; }

	private:
		ImageLib::stReadParam m_param;
		ImageLib::stReadResult m_result;
	};
}
#endif // ImageReader_h__
