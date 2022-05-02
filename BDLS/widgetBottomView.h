#pragma once

#include <QWidget>
#include "ui_widgetBottomView.h"
#include <QtWidgets>

class BDLS;
class widgetBottomView : public QWidget
{
	Q_OBJECT

public:
	widgetBottomView(QWidget *parent = Q_NULLPTR);
	~widgetBottomView();
	BDLS* m_pView;

	int font_size = 10;
	QTreeWidget* m_outputTree;
	void AddResult(QTreeWidgetItem* item);

private:
	Ui::widgetBottomView ui;
private slots:
	void onPlus();
	void onMinus();
	void onClear();
	void itemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
	void onDoubleClicked(const QModelIndex& index);

};
