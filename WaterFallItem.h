#ifndef WaterFallItem_h__
#define WaterFallItem_h__

#include <QtCore>
#include <QtWidgets>

class CWaterFallItem : public QWidget
{
	Q_OBJECT
public:
	CWaterFallItem(const QPixmap& thumb, const QString& path, QWidget* parent = 0);

public:
	void setThumb(const QPixmap& thumb, const QString& path);
	QString originImagePath() const;
	QPixmap thumb() const { return m_thumb; }

protected:
	void paintEvent(QPaintEvent *event);
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *event);

private:
	QString m_originImagePath;
	QPixmap m_thumb;
	bool m_isHovering;
};

#endif // WaterFallItem_h__
