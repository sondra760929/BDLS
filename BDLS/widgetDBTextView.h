#pragma once

#include <QDialog>
#include "ui_widgetDBTextView.h"

class BDLS;
class widgetDBTextView : public QDialog
{
	Q_OBJECT

public:
	widgetDBTextView(BDLS* parent, QString file_id);
	~widgetDBTextView();
	BDLS* m_pView;

private:
	Ui::widgetDBTextView ui;
};
