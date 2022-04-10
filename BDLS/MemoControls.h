#pragma once

#include <QWidget>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QComboBox;
class QBoxLayout;
QT_END_NAMESPACE

class MemoControls : public QWidget
{
	Q_OBJECT

public:
	MemoControls(QWidget *parent, int level = 0);
	~MemoControls();

	QLabel* lblDateTime;
	QLabel* lblMemo;
	int _level = 0;
	QBoxLayout* layout;
	QWidget* m_parent;
	int memo_id = 0;
	int state = 0;
	void setLevel(int level);
	void setDate(QString date);
	void setMemo(QString memo);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
private:
};

class MemoData
{
public:
	MemoData(int id, int parent_id, QString memo, QString date)
		: m_id(id)
		, m_parent_id(parent_id)
		, m_memo(memo)
	{
		m_datetime = QDateTime::fromString(date, "yyyy-MM-dd HH:mm:ss");
	}

	int m_id;
	int m_parent_id;
	QString m_memo;
	QDateTime m_datetime;
	int m_level = 0;

	QList< MemoData* > chileMemo;
	MemoControls* connected_control = NULL;
};
