#include "widgetLogin.h"

widgetLogin::widgetLogin(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.btnLogin, &QPushButton::clicked, this, &widgetLogin::onOKButtonClicked);
}

widgetLogin::~widgetLogin()
{
}


void widgetLogin::onOKButtonClicked()
{
	user_name = ui.lineEdit->text();
	user_pass = ui.lineEdit_2->text();
	accept();
}