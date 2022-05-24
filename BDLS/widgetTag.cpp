#include "widgetTag.h"
#include "widgetLeftView.h"

widgetTagList::widgetTagList(QWidget* parent)
	: QListWidget(parent)
{
	m_parent = parent;
}

void widgetTagList::mouseReleaseEvent(QMouseEvent* event)
{
	((widgetLeftView*)(m_parent_parent))->OnTagListClicked((widgetTag*)m_parent);
}


widgetTag::widgetTag(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_parent = parent;

	//QBoxLayout* b_layout = new QVBoxLayout;
	//ui.setLayout(b_layout);

	lblPageNo = new QLabel(this);
	ui.verticalLayout->addWidget(lblPageNo);

	tag_list = new widgetTagList(this);
	tag_list->m_parent_parent = parent;
	ui.verticalLayout->addWidget(tag_list);
	tag_list->setViewMode(QListView::ViewMode::IconMode);
	tag_list->setSpacing(10);
}

widgetTag::~widgetTag()
{
}

void widgetTag::mousePressEvent(QMouseEvent* event)
{
	state = 1;
	//repaint();

}

void widgetTag::mouseReleaseEvent(QMouseEvent* event)
{
	state = 0;
	//repaint();
	((widgetLeftView*)(m_parent))->OnTagListClicked(this);
}


void widgetTag::setPageNo(int page_no)
{
	m_page_no = page_no;
	lblPageNo->setText(QString("%1 p").arg(page_no + 1));
}
