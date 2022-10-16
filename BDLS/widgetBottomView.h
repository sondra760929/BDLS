#pragma once

#include <QWidget>
#include "ui_widgetBottomView.h"
#include <QtWidgets>

class BDLS;

class HtmlDelegate : public QStyledItemDelegate
{
protected:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
	void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const;
};

class widgetBottomView : public QWidget
{
	Q_OBJECT

public:
	widgetBottomView(QWidget *parent = Q_NULLPTR);
	~widgetBottomView();
	BDLS* m_pView;

	//int font_size = 10;
	//QTreeWidget* m_outputTree;
	QTreeView* m_outputTree;
	QStandardItemModel* model;
	void AddResult(QTreeWidgetItem* item);

private:
	Ui::widgetBottomView ui;
private slots:
	void onPlus();
	void onMinus();
	void onClear();
	void itemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
	void onDoubleClicked(const QModelIndex& index);
	void onClicked(const QModelIndex& index);
};
