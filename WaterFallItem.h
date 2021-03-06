#ifndef WaterFallItem_h__
#define WaterFallItem_h__

#include <QtCore>
#include <QtWidgets>

class CWaterFallItem : public QWidget
{
	Q_OBJECT

	friend class CWaterFallWidget;
public:
	CWaterFallItem(const QPixmap& thumb, const QString& path, QWidget* parent = 0);
	~CWaterFallItem();

public:
	QSize imageSize() const{ return m_size; }
	void setThumb(const QPixmap& thumb, const QString& path);
	QString originImagePath() const;
	QPixmap thumb() const { return m_thumb; }

	void dump();
protected:
	void paintEvent(QPaintEvent *event);
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void removeDumpFile();
private:
	QSize m_size;
	bool m_isDumped;
	QString m_dumpedPath;
	QString m_originImagePath;
	QPixmap m_thumb;
	bool m_isHovering;
};

#endif // WaterFallItem_h__
