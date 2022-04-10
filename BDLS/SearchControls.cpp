#include "SearchControls.h"

#include <QComboBox>
#include <QLineEdit>
#include <QComboBox>
#include <QBoxLayout>

SearchControls::SearchControls(QWidget *parent)
	: QWidget(parent)
{
	m_searchTitle = new QComboBox(this);
	m_searchWord = new QLineEdit(this);
    m_searchCondition = new QComboBox(this);
    m_searchCondition->addItem("AND");
    m_searchCondition->addItem("OR");
    m_searchCondition->addItem("NOT");

    QBoxLayout* layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_searchTitle);
    layout->addWidget(m_searchWord);
    layout->addWidget(m_searchCondition);
    setLayout(layout);

}

SearchControls::~SearchControls()
{
}
