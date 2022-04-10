#include "MemoControls.h"
#include <QBoxLayout>
#include <QLabel>
#include "widgetLeftView.h"

MemoControls::MemoControls(QWidget *parent, int level)
	: QWidget(parent)
	, _level(level)
	, m_parent(parent)
{
	lblDateTime = new QLabel(this);
	lblMemo = new QLabel(this);
	lblDateTime->setStyleSheet("QLabel { background-color:white; font:bold; font-size: " + QString::number(5) + "pt; qproperty-alignment: 'AlignRight';}");
	lblMemo->setStyleSheet("QLabel { background-color:white; font-size: " + QString::number(10) + "pt; text-align:left;}");

    layout = new QVBoxLayout;
	layout->setSpacing(0);
    layout->setContentsMargins(_level * 15, 0, 0, 0);
    layout->addWidget(lblDateTime);
    layout->addWidget(lblMemo);
    setLayout(layout);
}

MemoControls::~MemoControls()
{
}

void MemoControls::setLevel(int level)
{
	_level = level;
	layout->setContentsMargins(_level * 5, 0, 0, 0);
}

void MemoControls::setDate(QString date)
{
	lblDateTime->setText(date);
}

void MemoControls::setMemo(QString memo)
{
	lblMemo->setText(memo);
}

void MemoControls::mousePressEvent(QMouseEvent* event)
{
    state = 1;
    //repaint();

}

void MemoControls::mouseReleaseEvent(QMouseEvent* event)
{
    state = 0;
    //repaint();
	((widgetLeftView*)(m_parent))->OnMemoClicked(this);
}
