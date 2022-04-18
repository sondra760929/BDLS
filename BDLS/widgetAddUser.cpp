#include "widgetAddUser.h"

widgetAddUser::widgetAddUser(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.btnOK, &QPushButton::clicked, this, &widgetAddUser::onOKButtonClicked);
	connect(ui.btnCancel, &QPushButton::clicked, this, &widgetAddUser::onCancelButtonClicked);
}

widgetAddUser::~widgetAddUser()
{
}

void widgetAddUser::onOKButtonClicked()
{
	user_id = ui.lineEdit_3->text();
	user_pass = ui.lineEdit_4->text();
	user_name = ui.lineEdit_5->text();
	accept();
}

void widgetAddUser::onCancelButtonClicked()
{
	reject();
}