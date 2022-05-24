#pragma once

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include "ui_widgetTag.h"

class widgetTagList : public QListWidget
{
	Q_OBJECT

public:
	widgetTagList(QWidget* parent = Q_NULLPTR);

	QWidget* m_parent_parent;
	QWidget* m_parent;
	void mouseReleaseEvent(QMouseEvent*);

private:
};

class widgetTag : public QWidget
{
	Q_OBJECT

public:
	widgetTag(QWidget *parent = Q_NULLPTR);
	~widgetTag();

	QWidget* m_parent;
	widgetTagList* tag_list;
	QLabel* lblPageNo;
	int m_page_no;
	void setPageNo(int page_no);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);

private:
	Ui::widgetTag ui;
	int state;
};
