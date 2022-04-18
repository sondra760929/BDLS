#pragma once

#include <QWidget>
#include "ui_widgetProgress.h"

class widgetProgress : public QWidget
{
	Q_OBJECT

public:
	widgetProgress(QWidget *parent = Q_NULLPTR);
	~widgetProgress();

	void SetStatus1(QString status);
	void SetStatus2(QString status);
	void SetProgress1(int pos);
	void SetProgress2(int pos);

private:
	Ui::widgetProgress ui;
};
