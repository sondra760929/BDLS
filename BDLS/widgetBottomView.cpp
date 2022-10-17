#include "widgetBottomView.h"
#include "BDLS.h"
#include "db_manager.h"
#include <QStyledItemDelegate>

int font_size = 10;

void HtmlDelegate::initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const {
	QStyledItemDelegate::initStyleOption(option, index);
	option->font.setPointSize(font_size);
	option->font.setPixelSize(font_size);
	option->font.setPointSizeF(font_size);
}

void HtmlDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionViewItem optionV4 = option;
	initStyleOption(&optionV4, index);

	QStyle* style = optionV4.widget ? optionV4.widget->style() : QApplication::style();

	QTextDocument doc;
	doc.setHtml(optionV4.text);

	/// Painting item without text
	optionV4.text = QString();
	style->drawControl(QStyle::CE_ItemViewItem, &optionV4, painter);

	QAbstractTextDocumentLayout::PaintContext ctx;

	// Highlighting text if item is selected
	if (optionV4.state & QStyle::State_Selected)
		ctx.palette.setColor(QPalette::Text, optionV4.palette.color(QPalette::Active, QPalette::HighlightedText));

	QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &optionV4);
	painter->save();
	painter->translate(textRect.topLeft());
	painter->setClipRect(textRect.translated(-textRect.topLeft()));
	doc.documentLayout()->draw(painter, ctx);
	painter->restore();
}

QSize HtmlDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionViewItem optionV4 = option;
	initStyleOption(&optionV4, index);

	QTextDocument doc;
	doc.setHtml(optionV4.text);
	doc.setTextWidth(optionV4.rect.width());
	return QSize(doc.idealWidth(), doc.size().height());
}

widgetBottomView::widgetBottomView(QWidget* parent)
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

	m_outputTree = new QTreeView(this);
	layout->addWidget(m_outputTree);

	//m_outputTree->clear();
	m_outputTree->setHeaderHidden(true);

	model = new QStandardItemModel();
	m_outputTree->setModel(model);

	HtmlDelegate* delegate = new HtmlDelegate();
	m_outputTree->setItemDelegate(delegate);

	connect(btn_add, &QPushButton::clicked, this, &widgetBottomView::onPlus);
	connect(btn_dell, &QPushButton::clicked, this, &widgetBottomView::onMinus);
	connect(btn_clear, &QPushButton::clicked, this, &widgetBottomView::onClear);

	//connect(m_outputTree, &QTreeWidget::currentItemChanged, this, &widgetBottomView::itemChanged);
	//connect(m_outputTree, &QTreeWidget::doubleClicked, this, &widgetBottomView::onDoubleClicked);
	connect(m_outputTree, &QTreeView::clicked, this, &widgetBottomView::onClicked);
	connect(m_outputTree, &QTreeView::doubleClicked, this, &widgetBottomView::onDoubleClicked);
}

widgetBottomView::~widgetBottomView()
{
}


void widgetBottomView::AddResult(QTreeWidgetItem* item)
{
	//m_outputTree->addTopLevelItem(item);
	m_outputTree->expandAll();
}

void widgetBottomView::onPlus()
{
	font_size++;
	//m_outputTree->setStyleSheet("QTreeView::item { font-size: " + QString::number(font_size) + "pt; } QLabel { font-size: " + QString::number(font_size) + "pt; }");
}
void widgetBottomView::onMinus()
{
	font_size--;
	//m_outputTree->setStyleSheet("QTreeView::item { font-size: " + QString::number(font_size) + "pt; } QLabel { font-size: " + QString::number(font_size) + "pt; }");
}
void widgetBottomView::onClear()
{
	//m_outputTree->clear();
	model->clear();
	m_pView->resetSelectBySearch();
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
				QString file_name = m_pView->selectFromFileID(data_list[0].toInt());

				if (data_list[1] == "CH")
				{
					if (data_list.count() > 3)
					{
						m_pView->SetCurrentFile(CONTENT_META, file_name, data_list[2], data_list[3]);	//	page_no, block_no
					}
				}
				else if (data_list[1] == "CC")
				{
					if (data_list.count() > 4)
					{
						m_pView->SetCurrentFile(CONTENT_TEXT, file_name, data_list[2], data_list[3], data_list[4]);	//	page_no, search_string, search_index
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
					if (data_list.count() > 3)
					{
						m_pView->SetCurrentFile(MV, file_name, data_list[3]);
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

void widgetBottomView::onClicked(const QModelIndex& index)
{
	QString data_str = model->data(index, Qt::AccessibleTextRole).toString();
	QStringList data_list = data_str.split("/");
	if (data_list.count() >= 2)
	{
		if (m_pView->db->Connected())
		{
			QString file_name = m_pView->selectFromFileID(data_list[0].toInt());

			if (data_list[1] == "CH")
			{
				if (data_list.count() > 3)
				{
					m_pView->SetCurrentFile(CONTENT_META, file_name, data_list[2], data_list[3]);	//	page_no, block_no
				}
			}
			else if (data_list[1] == "CC")
			{
				if (data_list.count() > 4)
				{
					m_pView->SetCurrentFile(CONTENT_TEXT, file_name, data_list[2], data_list[3], data_list[4]);	//	page_no, search_string, search_index
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
				if (data_list.count() > 3)
				{
					m_pView->SetCurrentFile(MV, file_name, data_list[3]);
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

void widgetBottomView::onDoubleClicked(const QModelIndex& index)
{
	QString data_str = model->data(index, Qt::AccessibleTextRole).toString();
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