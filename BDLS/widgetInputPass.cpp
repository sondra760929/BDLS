#include "widgetInputPass.h"

widgetInputPass::widgetInputPass(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.btnOK, &QPushButton::clicked, this, &widgetInputPass::onOKButtonClicked);
	connect(ui.btnCancel, &QPushButton::clicked, this, &widgetInputPass::onCancelButtonClicked);
}

widgetInputPass::~widgetInputPass()
{}

void widgetInputPass::onOKButtonClicked()
{
	pass = ui.lineEdit_3->text();
	accept();
}

void widgetInputPass::onCancelButtonClicked()
{
	reject();
}