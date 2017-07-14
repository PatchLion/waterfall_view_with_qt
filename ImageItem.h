#ifndef ImageItem_h__
#define ImageItem_h__

#include <QtCore>
#include <QtWidgets>
#include "ImageLoadThread.h"

class CImageItem : public QDialog
{
	Q_OBJECT
public:
	CImageItem(const QString& path, QWidget* parent = 0);


protected:
	void paintEvent(QPaintEvent *event);
	void showEvent(QShowEvent *event);

protected Q_SLOTS:
	void onImageLoaded();

private:
	CImageLoadThread m_imageLoadThread;
	bool m_isLoading;
};

#endif // ImageItem_h__
