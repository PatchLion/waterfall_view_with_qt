#ifndef ImageItem_h__
#define ImageItem_h__

#include <QtCore>
#include <QtWidgets>
#include "ImageReadThread.h"

class CImageItem : public QDialog
{
	Q_OBJECT
public:
	CImageItem(const QString& path, bool isLocalFile, QWidget* parent = 0);


protected:
	void paintEvent(QPaintEvent *event);
	void showEvent(QShowEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

protected Q_SLOTS:
	void onImageLoaded();

private:
	ImageLib::CImageReadThread m_imageLoadThread;
	bool m_isLoading;
	double m_scale;
};

#endif // ImageItem_h__
