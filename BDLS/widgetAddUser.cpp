#include "widgetAddUser.h"

widgetAddUser::widgetAddUser(QString id, QString pass, QString name, bool super, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.lineEdit_4->setText(id);
	ui.lineEdit_3->setText(pass);
	ui.lineEdit_5->setText(name);
	ui.chkSuper->setChecked(super);

	connect(ui.btnOK, &QPushButton::clicked, this, &widgetAddUser::onOKButtonClicked);
	connect(ui.btnCancel, &QPushButton::clicked, this, &widgetAddUser::onCancelButtonClicked);
}

widgetAddUser::~widgetAddUser()
{
}

void widgetAddUser::onOKButtonClicked()
{
	user_id = ui.lineEdit_4->text();
	user_pass = ui.lineEdit_3->text();
	user_name = ui.lineEdit_5->text();
	user_super = ui.chkSuper->isChecked();
	accept();
}

void widgetAddUser::onCancelButtonClicked()
{
	reject();
}