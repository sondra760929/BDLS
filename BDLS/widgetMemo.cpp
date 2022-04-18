#include "widgetMemo.h"
#include "widgetLeftView.h"

widgetMemo::widgetMemo(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_parent = parent;
}

widgetMemo::~widgetMemo()
{
}

void widgetMemo::setLevel(int level)
{
	_level = level;
	ui.leftSpace->changeSize(level * 20, 10);
}

void widgetMemo::setDate(QString date)
{
	ui.lblDateTime->setText(date);
}

void widgetMemo::setMemo(QString memo)
{
	ui.lblMemo->setText(memo);
}

void widgetMemo::setUserName(QString name)
{
	user_name = name;
	ui.lblUserName->setText(name);
}

void widgetMemo::mousePressEvent(QMouseEvent* event)
{
	state = 1;
	//repaint();

}

void widgetMemo::mouseReleaseEvent(QMouseEvent* event)
{
	state = 0;
	//repaint();
	((widgetLeftView*)(m_parent))->OnMemoClicked(this);
}

void widgetMemo::setSelect(bool select)
{
	if (select)
	{
		ui.groupBox->setStyleSheet("QGroupBox { color: white; background-color:rgb(227, 227, 227); border: 1px solid red; border-radius:6px; } QGroupBox:hover { background-color:rgb(170, 170, 255);}");
	}
	else
	{
		ui.groupBox->setStyleSheet("QGroupBox { color: white; background-color:rgb(227, 227, 227); border-width:0px; border-radius:6px;} QGroupBox:hover { background-color:rgb(170, 170, 255);}");
	}
}