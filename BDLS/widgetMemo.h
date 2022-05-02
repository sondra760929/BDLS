#pragma once

#include <QWidget>
#include <QtWidgets>
#include "ui_widgetMemo.h"

class widgetMemo : public QWidget
{
	Q_OBJECT

public:
	widgetMemo(QWidget *parent = Q_NULLPTR);
	~widgetMemo();

	int _level = 0;
	QWidget* m_parent;
	int memo_id = 0;
	int state = 0;
	QString user_id;
	QString user_name;
	void setLevel(int level);
	void setDate(QString date);
	void setMemo(QString memo);
	void setUserName(QString name);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);
	void setSelect(bool select);

private:
	Ui::widgetMemo ui;
};


class MemoData
{
public:
	MemoData(int id, int parent_id, QString user_id, QString user_name, QString memo, QString date)
		: m_id(id)
		, m_parent_id(parent_id)
		, m_userid(user_id)
		, m_username(user_name)
		, m_memo(memo)
	{
		m_datetime = QDateTime::fromString(date, "yyyy-MM-dd HH:mm:ss");
		m_str_datetime = date;
	}

	int m_id;
	int m_parent_id;
	QString m_userid;
	QString m_username;
	QString m_memo;
	QString m_str_datetime;
	QDateTime m_datetime;
	int m_level = 0;

	QList< MemoData* > chileMemo;
	widgetMemo* connected_control = NULL;
};

