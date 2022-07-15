#pragma once

#include <QDialog>
#include "ui_widgetInputPass.h"

class widgetInputPass : public QDialog
{
	Q_OBJECT

public:
	widgetInputPass(QWidget *parent = nullptr);
	~widgetInputPass();

	QString pass;

private:
	Ui::widgetInputPassClass ui;
	void onOKButtonClicked();
	void onCancelButtonClicked();
};
