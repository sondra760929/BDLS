#pragma once

#include <QDialog>
#include "ui_widgetLogin.h"

class widgetLogin : public QDialog
{
	Q_OBJECT

public:
	widgetLogin(QWidget *parent = Q_NULLPTR);
	~widgetLogin();

	QString user_name;
	QString user_pass;

private:
	Ui::widgetLogin ui;

private slots:
	void onOKButtonClicked();
};
