#pragma once

#include <QDialog>
#include "ui_widgetAddUser.h"

class widgetAddUser : public QDialog
{
	Q_OBJECT

public:
	widgetAddUser(QWidget *parent = Q_NULLPTR);
	~widgetAddUser();

	QString user_id;
	QString user_pass;
	QString user_name;

private:
	Ui::widgetAddUser ui;

private slots:
	void onOKButtonClicked();
	void onCancelButtonClicked();
};
