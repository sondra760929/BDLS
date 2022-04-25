#include "MyTabWidget.h"

MyTabWidget::MyTabWidget(QWidget *parent)
	: QTabWidget(parent)
{
    // text - color
    QHash <QString, QColor> dict;

    dict["파일"] = QColor("#50ABC1");
    dict["상세 검색"] = QColor("#9C2330");
    dict["노트"] = QColor("#E1BA4C");
    dict["사용자"] = QColor("#2F65AF");

    setTabBar(new TabBar(dict));
}

MyTabWidget::~MyTabWidget()
{
}
