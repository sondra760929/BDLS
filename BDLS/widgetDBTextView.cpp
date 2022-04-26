#include "widgetDBTextView.h"
#include "BDLS.h"

widgetDBTextView::widgetDBTextView(BDLS* parent, QString file_id)
	: QDialog(NULL)
{
	ui.setupUi(this);

	m_pView = (BDLS*)parent;
	if (m_pView)
	{
		QStandardItemModel* originModel = new QStandardItemModel(this);
		originModel->insertColumn(0);
		originModel->setHeaderData(0, Qt::Horizontal, "Page");
		originModel->insertColumn(1);
		originModel->setHeaderData(1, Qt::Horizontal, "Block");
		originModel->insertColumn(2);
		originModel->setHeaderData(2, Qt::Horizontal, "Text");
		int index = 0;
		QVariantList data;
		QString query = QString("SELECT * FROM page_info WHERE file_id=%1 ORDER BY page_no, block_no").arg(file_id);
		m_pView->db->exec(query, data);
		for (const auto& item : data)
		{
			auto map = item.toMap();
			int temp_page_no = map["page_no"].toInt();
			int temp_block_no = map["block_no"].toInt();
			QString temp_block_text = map["block_text"].toString();
			originModel->insertRow(index);
			originModel->setData(originModel->index(index, 0), temp_page_no);
			originModel->setData(originModel->index(index, 1), temp_block_no);
			originModel->setData(originModel->index(index, 2), temp_block_text);
			index++;
		}

		ui.tableView->setModel(originModel);
		ui.tableView->horizontalHeader()->setStretchLastSection(true);
		ui.tableView->setWordWrap(true);
		ui.tableView->setTextElideMode(Qt::ElideMiddle);
		ui.tableView->resizeRowsToContents();
	}
}

widgetDBTextView::~widgetDBTextView()
{
}
