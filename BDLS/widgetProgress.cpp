#include "widgetProgress.h"

widgetProgress::widgetProgress(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

widgetProgress::~widgetProgress()
{
}

void widgetProgress::SetStatus1(QString status)
{
	ui.lblStatus->setText(status);
}

void widgetProgress::SetStatus2(QString status)
{
	ui.lblStatus2->setText(status);
}

void widgetProgress::SetProgress1(int pos)
{
	ui.progressBar1->setValue(pos);
}

void widgetProgress::SetProgress2(int pos)
{
	ui.progressBar2->setValue(pos);
}
