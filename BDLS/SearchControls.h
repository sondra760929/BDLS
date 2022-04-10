#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QLineEdit;
class QComboBox;
QT_END_NAMESPACE
class SearchControls : public QWidget
{
	Q_OBJECT

public:
	SearchControls(QWidget *parent = nullptr);
	~SearchControls();

	QComboBox* m_searchTitle;
	QLineEdit* m_searchWord;
	QComboBox* m_searchCondition;
};
