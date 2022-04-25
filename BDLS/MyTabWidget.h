#pragma once

#include <QTabWidget>
#include <QTabBar>
#include <QStylePainter>
#include <QStyleOptionTab>

class TabBar : public QTabBar
{
public:
    TabBar(const QHash<QString, QColor>& colors, QWidget* parent = 0) :QTabBar(parent) {
        mColors = colors;
    }

protected:
    void paintEvent(QPaintEvent*/*event*/) {

        QStylePainter painter(this);
        QStyleOptionTab opt;

        for (int i = 0; i < count(); i++)
        {
            initStyleOption(&opt, i);
            if (mColors.contains(opt.text)) {
                opt.palette.setColor(QPalette::Button, mColors[opt.text]);
                opt.palette.setBrush(QPalette::WindowText, Qt::white);
            }

            painter.drawControl(QStyle::CE_TabBarTabShape, opt);
            painter.drawControl(QStyle::CE_TabBarTabLabel, opt);
            //painter.setPen(Qt::white);
            //painter.drawText(this->tabRect(i), Qt::AlignBottom | Qt::AlignHCenter, this->tabText(i));
        }
    }


private:
    QHash<QString, QColor> mColors;
};

class MyTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	MyTabWidget(QWidget *parent);
	~MyTabWidget();
};
