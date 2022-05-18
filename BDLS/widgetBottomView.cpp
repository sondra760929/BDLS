#include "widgetBottomView.h"
#include "BDLS.h"
#include "db_manager.h"

widgetBottomView::widgetBottomView(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QBoxLayout* layout = new QVBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	setLayout(layout);

	QBoxLayout* temp_add = new QHBoxLayout;
	QPushButton* btn_clear = new QPushButton(this);
	btn_clear->setText("clear");
	btn_clear->setFixedSize(100, 20);
	QPushButton* btn_add = new QPushButton(this);
	btn_add->setText("+");
	btn_add->setFixedSize(20, 20);
	QPushButton* btn_dell = new QPushButton(this);
	btn_dell->setText("-");
	btn_dell->setFixedSize(20, 20);
	temp_add->addWidget(btn_add);
	temp_add->addWidget(btn_dell);
	temp_add->addStretch(1);
	temp_add->addWidget(btn_clear);
	layout->addLayout(temp_add);

	m_outputTree = new QTreeWidget(this);
	layout->addWidget(m_outputTree);

	m_outputTree->clear();
	m_outputTree->setHeaderHidden(true);

	connect(btn_add, &QPushButton::clicked, this, &widgetBottomView::onPlus);
	connect(btn_dell, &QPushButton::clicked, this, &widgetBottomView::onMinus);
	connect(btn_clear, &QPushButton::clicked, this, &widgetBottomView::onClear);

	connect(m_outputTree, &QTreeWidget::currentItemChanged, this, &widgetBottomView::itemChanged);
	connect(m_outputTree, &QTreeWidget::doubleClicked, this, &widgetBottomView::onDoubleClicked);
}

widgetBottomView::~widgetBottomView()
{
}


void widgetBottomView::AddResult(QTreeWidgetItem* item)
{
	m_outputTree->addTopLevelItem(item);
	m_outputTree->expandAll();
}

void widgetBottomView::onPlus()
{
	font_size++;
	m_outputTree->setStyleSheet("QTreeWidget { font-size: " + QString::number(font_size) + "pt; } QLabel { font-size: " + QString::number(font_size) + "pt; }");
}
void widgetBottomView::onMinus()
{
	font_size--;
	m_outputTree->setStyleSheet("QTreeWidget { font-size: " + QString::number(font_size) + "pt; } QLabel { font-size: " + QString::number(font_size) + "pt; }");
}
void widgetBottomView::onClear()
{
	m_outputTree->clear();
}

void widgetBottomView::itemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
	if (current)
	{
		QString data_str = current->data(0, Qt::AccessibleTextRole).toString();
		QStringList data_list = data_str.split("/");
		if (data_list.count() >= 2)
		{
			if (m_pView->db->Connected())
			{
				QString file_path;
				QString file_name;
				QString query = QString("SELECT file_name, file_path FROM file_info WHERE id=%1").arg(data_list[0]);
				QVariantList data;
				m_pView->db->exec(query, data);
				for (const auto& item : data)
				{
					auto map = item.toMap();
					file_name = map["file_name"].toString();
					file_path = map["file_path"].toString();
				}

				if (data_list[1] == "C")
				{
					if (data_list.count() > 3)
					{
						m_pView->SetCurrentFile(CONTENT, file_name, data_list[2], data_list[3]);	//	page_no, block_no
					}
				}
				else if (data_list[1] == "H")
				{
					if (data_list.count() > 3)
					{
						m_pView->SetCurrentFile(HASHTAG, file_name, data_list[3], data_list[2]);	//	page_no, tag_name
					}
				}
				else if (data_list[1] == "V")
				{
					if (data_list.count() > 2)
					{
						m_pView->SetCurrentFile(MV, file_name, data_list[2]);
					}
				}
				else if (data_list[1] == "MC")
				{
					if (data_list.count() > 5)
					{
						m_pView->SetCurrentFile(MEMO_CONTENT, file_name, data_list[5], data_list[2], data_list[3], data_list[4]);	//	page_no, memo_id, find_start_index, find_length
					}
				}
				else if (data_list[1] == "MW")
				{
					if (data_list.count() > 5)
					{
						m_pView->SetCurrentFile(MEMO_USER, file_name, data_list[5], data_list[2], data_list[3], data_list[4]);	//	page_no, memo_id, find_start_index, find_length
					}
				}
				else if (data_list[1] == "MD")
				{
					if (data_list.count() > 4)
					{
						m_pView->SetCurrentFile(MEMO_DATE, file_name, data_list[4], data_list[2], data_list[3]);	//	page_no, memo_id, date
					}
				}
			}
		}
	}
}

void widgetBottomView::onDoubleClicked(const QModelIndex& index)
{
	QString data_str = index.data(Qt::AccessibleTextRole).toString();
	QStringList data_list = data_str.split("/");
	if (data_list.count() == 3)
	{
		if (m_pView->db->Connected())
		{
			QString file_path;
			QString file_name;
			QString query = QString("SELECT file_name, file_path FROM file_info WHERE id=%1").arg(data_list[0]);
			QVariantList data;
			m_pView->db->exec(query, data);
			for (const auto& item : data)
			{
				auto map = item.toMap();
				file_name = map["file_name"].toString();
				file_path = map["file_path"].toString();
			}

			if (QFile::exists(file_path))
			{
				QDesktopServices::openUrl(QUrl::fromLocalFile(file_path));
			}
		}
	}
}