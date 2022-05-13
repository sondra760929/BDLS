#include "widgetLeftView.h"
#include <qscreen.h>
#include <QtWidgets/qmessagebox.h>
#include "BDLS.h"
#include "widgetMemo.h"
#include "widgetAddUser.h"

QStringList memo_combo_header = { QString::fromLocal8Bit("내용"), QString::fromLocal8Bit("작성자"), QString::fromLocal8Bit("날짜") };
QStringList tag_combo_header = { QString::fromLocal8Bit("해시태그") };
widgetLeftView::widgetLeftView(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	fileTree = ui.tvFiles;

	model.setRootPath("");
	//if (parser.isSet(dontUseCustomDirectoryIconsOption))
	//    model.setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
	//if (parser.isSet(dontWatchOption))
	//    model.setOption(QFileSystemModel::DontWatchForChanges);
	fileTree->setModel(&model);

	fileTree->setAnimated(false);
	fileTree->setIndentation(20);
	fileTree->setSortingEnabled(false);
	fileTree->setColumnWidth(0, 300);
	connect(fileTree->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(onCurrentChanged(QItemSelection, QItemSelection)));
	connect(fileTree, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(on_treeView_doubleClicked(const QModelIndex&)));

	//------------------------------------------------------------------------------

	//QSplitter* search_splitter = new QSplitter(ui.searchview);

	searchViewLayout = new QVBoxLayout;

	QBoxLayout* temp_add = new QHBoxLayout;
	QLabel* label = new QLabel(this);
	label->setText(QString::fromLocal8Bit("1. 메타 및 본문 검색"));
	btn_add = new QPushButton(this);
	btn_add->setText("+");
	btn_add->setFixedSize(20, 20);
	btn_dell = new QPushButton(this);
	btn_dell->setText("-");
	btn_dell->setFixedSize(20, 20);
	temp_add->addWidget(label);
	//temp_add->addStretch(1);
	temp_add->addWidget(btn_add);
	temp_add->addWidget(btn_dell);
	searchViewLayout->addLayout(temp_add);

	SearchControls* sc = new SearchControls(this);
	search_list.append(sc);
	searchViewLayout->addWidget(sc);

	QPushButton* btn_search = new QPushButton(this);
	btn_search->setText(QString::fromLocal8Bit("검색"));
	searchViewLayout->addWidget(btn_search);

	label = new QLabel(this);
	label->setText("");
	searchViewLayout->addWidget(label);

	temp_add = new QHBoxLayout;
	label = new QLabel(this);
	label->setText(QString::fromLocal8Bit("2. 메모 검색"));
	btn_memo_add = new QPushButton(this);
	btn_memo_add->setText("+");
	btn_memo_add->setFixedSize(20, 20);
	btn_memo_dell = new QPushButton(this);
	btn_memo_dell->setText("-");
	btn_memo_dell->setFixedSize(20, 20);
	temp_add->addWidget(label);
	//temp_add->addStretch(1);
	temp_add->addWidget(btn_memo_add);
	temp_add->addWidget(btn_memo_dell);
	searchViewLayout->addLayout(temp_add);

	sc = new SearchControls(this);
	sc->m_searchTitle->addItems(memo_combo_header);
	memo_list.append(sc);
	searchViewLayout->addWidget(sc);

	QPushButton* btn_search2 = new QPushButton(this);
	btn_search2->setText(QString::fromLocal8Bit("검색"));
	searchViewLayout->addWidget(btn_search2);

	label = new QLabel(this);
	label->setText("");
	searchViewLayout->addWidget(label);

	temp_add = new QHBoxLayout;
	label = new QLabel(this);
	label->setText(QString::fromLocal8Bit("3. 해시태그 검색"));
	btn_tag_add = new QPushButton(this);
	btn_tag_add->setText("+");
	btn_tag_add->setFixedSize(20, 20);
	btn_tag_dell = new QPushButton(this);
	btn_tag_dell->setText("-");
	btn_tag_dell->setFixedSize(20, 20);
	temp_add->addWidget(label);
	//temp_add->addStretch(1);
	temp_add->addWidget(btn_tag_add);
	temp_add->addWidget(btn_tag_dell);
	searchViewLayout->addLayout(temp_add);

	sc = new SearchControls(this);
	sc->m_searchTitle->addItems(tag_combo_header);
	tag_list.append(sc);
	searchViewLayout->addWidget(sc);

	QPushButton* btn_search3 = new QPushButton(this);
	btn_search3->setText(QString::fromLocal8Bit("검색"));
	searchViewLayout->addWidget(btn_search3);

	//label = new QLabel(this);
	//label->setText(QString::fromLocal8Bit("3. 해시태그 검색"));
	//searchViewLayout->addWidget(label);

	//tagSearchList = new QListView(this);
	//searchViewLayout->addWidget(tagSearchList);
	//tagSearchList->setViewMode(QListView::ViewMode::IconMode);
	//tagSearchList->setSpacing(10);

	//temp_add = new QHBoxLayout;
	//tagSearchEdit = new QLineEdit(this);
	//QPushButton* tagSearchAdd = new QPushButton(this);
	//tagSearchAdd->setText(QString::fromLocal8Bit("추가"));
	//temp_add->addWidget(tagSearchEdit);
	//temp_add->addWidget(tagSearchAdd);
	//searchViewLayout->addLayout(temp_add);

	//QPushButton* btn_search3 = new QPushButton(this);
	//btn_search3->setText(QString::fromLocal8Bit("검색"));
	//searchViewLayout->addWidget(btn_search3);

	label = new QLabel(this);
	label->setText("");
	searchViewLayout->addWidget(label);

	temp_add = new QHBoxLayout;
	label = new QLabel(this);
	label->setText(QString::fromLocal8Bit("4. 동영상 목차 검색"));
	btn_mv_add = new QPushButton(this);
	btn_mv_add->setText("+");
	btn_mv_add->setFixedSize(20, 20);
	btn_mv_dell = new QPushButton(this);
	btn_mv_dell->setText("-");
	btn_mv_dell->setFixedSize(20, 20);
	temp_add->addWidget(label);
	//temp_add->addStretch(1);
	temp_add->addWidget(btn_mv_add);
	temp_add->addWidget(btn_mv_dell);
	searchViewLayout->addLayout(temp_add);

	sc = new SearchControls(this);
	sc->m_searchTitle->addItems(mv_combo_header);
	mv_list.append(sc);
	searchViewLayout->addWidget(sc);

	QPushButton* btn_search4 = new QPushButton(this);
	btn_search4->setText(QString::fromLocal8Bit("검색"));
	searchViewLayout->addWidget(btn_search4);

	//label = new QLabel(this);
	//label->setText(QString::fromLocal8Bit("4. 동영상 목차 검색"));
	//searchViewLayout->addWidget(label);

	//mvSearchList = new QListWidget(this);
	//searchViewLayout->addWidget(mvSearchList);

	//temp_add = new QHBoxLayout;
	//mvSearchEdit = new QLineEdit(this);
	//QPushButton* mvSearchAdd = new QPushButton(this);
	//mvSearchAdd->setText(QString::fromLocal8Bit("추가"));
	//temp_add->addWidget(mvSearchEdit);
	//temp_add->addWidget(mvSearchAdd);
	//searchViewLayout->addLayout(temp_add);

	//QPushButton* btn_search4 = new QPushButton(this);
	//btn_search4->setText(QString::fromLocal8Bit("검색"));
	//searchViewLayout->addWidget(btn_search4);

	searchViewLayout->addStretch(1);

	ui.searchview->setLayout(searchViewLayout);

	connect(btn_add, &QPushButton::clicked, this, &widgetLeftView::onSearchAdd);
	connect(btn_dell, &QPushButton::clicked, this, &widgetLeftView::onSearchDell);
	connect(btn_memo_add, &QPushButton::clicked, this, &widgetLeftView::onSearchMemoAdd);
	connect(btn_memo_dell, &QPushButton::clicked, this, &widgetLeftView::onSearchMemoDell);
	connect(btn_tag_add, &QPushButton::clicked, this, &widgetLeftView::onSearchTagAdd);
	connect(btn_tag_dell, &QPushButton::clicked, this, &widgetLeftView::onSearchTagDell);
	connect(btn_mv_add, &QPushButton::clicked, this, &widgetLeftView::onSearchMVAdd);
	connect(btn_mv_dell, &QPushButton::clicked, this, &widgetLeftView::onSearchMVDell);
	//connect(tagSearchAdd, &QPushButton::clicked, this, &widgetLeftView::onSearchTagAdd);
	//connect(mvSearchAdd, &QPushButton::clicked, this, &widgetLeftView::onSearchMVAdd);

	//connect(tagSearchList, &QListView::clicked, this, &widgetLeftView::onSearchTagClicked);
	connect(mvSearchList, &QListWidget::itemClicked, this, &widgetLeftView::onSearchMVClicked);

	connect(btn_search, &QPushButton::clicked, this, &widgetLeftView::doSearch1);
	connect(btn_search2, &QPushButton::clicked, this, &widgetLeftView::doSearch2);
	connect(btn_search3, &QPushButton::clicked, this, &widgetLeftView::doSearch3);
	connect(btn_search4, &QPushButton::clicked, this, &widgetLeftView::doSearch4);

	//------------------------------------------------------------------------------
	noteViewLayout = new QVBoxLayout;
	ui.noteview->setLayout(noteViewLayout);

	label = new QLabel(this);
	label->setText(QString::fromLocal8Bit("1. 메모"));
	noteViewLayout->addWidget(label);

	techScroll = new QScrollArea(this);
	techScroll->setBackgroundRole(QPalette::Window);
	techScroll->setFrameShadow(QFrame::Plain);
	techScroll->setFrameShape(QFrame::NoFrame);
	techScroll->setWidgetResizable(true);

	memoList = new QWidget(this);
	memoList->setObjectName("techarea");

	//techArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	memoList->setLayout(new QVBoxLayout(memoList));
	memoList->layout()->setContentsMargins(5, 5, 5 , 5);
	techScroll->setWidget(memoList);

	//memoList = new QListWidget(this);
	noteViewLayout->addWidget(techScroll);
	QSizePolicy sdMemo(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sdMemo.setVerticalStretch(2);
	techScroll->setSizePolicy(sdMemo);

	temp_add = new QHBoxLayout;
	noteParent = new QPushButton(this);
	noteParent->setText(QString::fromLocal8Bit("새글"));
	memoText = new QPlainTextEdit(this);
	memoText->setMaximumHeight(50);
	QPushButton* noteAdd = new QPushButton(this);
	noteAdd->setText(QString::fromLocal8Bit("등록"));
	temp_add->addWidget(noteParent);
	temp_add->addWidget(memoText);
	temp_add->addWidget(noteAdd);
	noteViewLayout->addLayout(temp_add);

	label = new QLabel(this);
	label->setText("");
	noteViewLayout->addWidget(label);

	label = new QLabel(this);
	label->setText(QString::fromLocal8Bit("2. 해시태그"));
	noteViewLayout->addWidget(label);

	tagList = new QListWidget(this);
	noteViewLayout->addWidget(tagList);
	QSizePolicy sdTag(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sdTag.setVerticalStretch(2);
	tagList->setSizePolicy(sdTag);
	tagList->setViewMode(QListView::ViewMode::IconMode);
	tagList->setSpacing(10);

	temp_add = new QHBoxLayout;
	tagEdit = new QLineEdit(this);
	QPushButton* tagAdd = new QPushButton(this);
	tagAdd->setText(QString::fromLocal8Bit("등록"));
	temp_add->addWidget(tagEdit);
	temp_add->addWidget(tagAdd);
	noteViewLayout->addLayout(temp_add);

	label = new QLabel(this);
	label->setText("");
	noteViewLayout->addWidget(label);

	label = new QLabel(this);
	label->setText(QString::fromLocal8Bit("3. 동영상 목차"));
	noteViewLayout->addWidget(label);

	mvList = new QListWidget(this);
	noteViewLayout->addWidget(mvList);
	QSizePolicy mvTag(QSizePolicy::Preferred, QSizePolicy::Preferred);
	mvTag.setVerticalStretch(2);
	mvList->setSizePolicy(mvTag);

	temp_add = new QHBoxLayout;
	mvTime = new QTimeEdit(this);
	mvTime->setTimeRange(QTime(0, 0, 0), QTime(10, 0, 0));
	mvTime->setTime(QTime(0, 0, 0));
	mvTime->setDisplayFormat("hh:mm:ss");

	mvText = new QLineEdit(this);
	QPushButton* mvAdd = new QPushButton(this);
	mvAdd->setText(QString::fromLocal8Bit("등록"));
	temp_add->addWidget(mvTime);
	temp_add->addWidget(mvText);
	temp_add->addWidget(mvAdd);
	noteViewLayout->addLayout(temp_add);

	//fileTagModel = new QStringListModel(this);
	//tagList->setModel(fileTagModel);

	//searchTagModel = new QStringListModel(this);
	//tagSearchList->setModel(searchTagModel);

	//completer = new QCompleter(this);
	//tagEdit->setCompleter(completer);

	//search_completer = new QCompleter(this);
	//tagSearchEdit->setCompleter(search_completer);

	connect(noteAdd, &QPushButton::clicked, this, &widgetLeftView::doAddMemo);
	connect(tagAdd, &QPushButton::clicked, this, &widgetLeftView::doAddTag);
	connect(mvAdd, &QPushButton::clicked, this, &widgetLeftView::doAddMV);
	connect(noteParent, &QPushButton::clicked, this, &widgetLeftView::doNewMemo);
	connect(tagList, &QListView::clicked, this, &widgetLeftView::onFileTagClicked);
	connect(mvList, &QListWidget::currentItemChanged, this, &widgetLeftView::onFileMVClicked);
	connect(mvList, &QListWidget::itemDoubleClicked, this, &widgetLeftView::onFileMVDClicked);

	//------------------------------------------------------------------------------
	userViewLayout = new QVBoxLayout;
	ui.userview->setLayout(userViewLayout);

	label = new QLabel(this);
	label->setText(QString::fromLocal8Bit("1. 사용자"));
	userViewLayout->addWidget(label);

	userTable = new QTableWidget(this);
	userViewLayout->addWidget(userTable);
	QSizePolicy utTag(QSizePolicy::Preferred, QSizePolicy::Preferred);
	utTag.setVerticalStretch(2);
	userTable->setSizePolicy(utTag);
	userTable->setSelectionMode(QAbstractItemView::SingleSelection);
	userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	userTable->horizontalHeader()->setStretchLastSection(true);

	temp_add = new QHBoxLayout;
	QPushButton* userAdd = new QPushButton(this);
	userAdd->setText(QString::fromLocal8Bit("추가 / 변경"));
	QPushButton* userDel = new QPushButton(this);
	userDel->setText(QString::fromLocal8Bit("삭제"));
	temp_add->addWidget(userAdd);
	temp_add->addWidget(userDel);
	userViewLayout->addLayout(temp_add);

	label = new QLabel(this);
	label->setText(QString::fromLocal8Bit("2. 허용 파일 목록"));
	userViewLayout->addWidget(label);

	fileTable = new QTableWidget(this);
	userViewLayout->addWidget(fileTable);
	utTag.setVerticalStretch(2);
	fileTable->setSizePolicy(utTag);
	fileTable->setSelectionMode(QAbstractItemView::MultiSelection);
	fileTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	fileTable->horizontalHeader()->setStretchLastSection(true);

	temp_add = new QHBoxLayout;
	QPushButton* fileAdd = new QPushButton(this);
	fileAdd->setText(QString::fromLocal8Bit("추가"));
	QPushButton* fileDel = new QPushButton(this);
	fileDel->setText(QString::fromLocal8Bit("삭제"));
	temp_add->addWidget(fileAdd);
	temp_add->addWidget(fileDel);
	userViewLayout->addLayout(temp_add);

	connect(userAdd, &QPushButton::clicked, this, &widgetLeftView::doAddUser);
	connect(userDel, &QPushButton::clicked, this, &widgetLeftView::doDelUser);
	connect(fileAdd, &QPushButton::clicked, this, &widgetLeftView::doAddFile);
	connect(fileDel, &QPushButton::clicked, this, &widgetLeftView::doDelFile);
	connect(userTable->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(onUserChanged(QItemSelection, QItemSelection)));
}

widgetLeftView::~widgetLeftView()
{
}

void widgetLeftView::setTagList()
{
	tagDatas.clear();
	tags.clear();
	if (m_pView->DBConnected())
	{
		QVariantList data;
		//	tag가 존재하는지 확인
		QString query = QString("SELECT id, tags FROM hsah_tags");
		m_pView->db->exec(query, data);
		for (const auto& item : data)
		{
			auto map = item.toMap();
			int tag_id = map["id"].toInt();
			QString tag_str = map["tags"].toString();
			tags.append(tag_str);
			tagDatas[tag_id] = tag_str;
		}
	}
	delete completer;
	completer = new QCompleter(tags, this);
	completer->setMaxVisibleItems(10);
	completer->setCompletionMode(QCompleter::CompletionMode::UnfilteredPopupCompletion);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setWrapAround(true);
	tagEdit->setCompleter(completer);

	//delete search_completer;
	//search_completer = new QCompleter(tags, this);
	//search_completer->setMaxVisibleItems(10);
	//search_completer->setCompletionMode(QCompleter::CompletionMode::UnfilteredPopupCompletion);
	//search_completer->setCaseSensitivity(Qt::CaseInsensitive);
	//search_completer->setWrapAround(true);
	//tagSearchEdit->setCompleter(search_completer);
}

void widgetLeftView::setSearchCombo(QList<QString>& h_list, QMap<QString, int>& map_h_to_i)
{
	header_to_index.clear();
	header_list.clear();
	for (int i = 0; i < h_list.size(); i++)
	{
		header_to_index[h_list[i]] = map_h_to_i[h_list[i]];
		header_list.append(h_list[i]);
	}
	header_to_index[QString::fromLocal8Bit("내용 검색")] = 0;
	header_list.insert(0, QString::fromLocal8Bit("내용 검색"));
	for (int i = 0; i < search_list.size(); i++)
	{
		search_list[i]->m_searchTitle->clear();
		search_list[i]->m_searchTitle->addItems(header_list);
		search_list[i]->m_searchTitle->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	}
}

void widgetLeftView::SetCurrentFile(QString file_path)
{
	fileTree->setCurrentIndex(model.index(file_path));
}

void widgetLeftView::onCurrentChanged(const QItemSelection& current, const QItemSelection& prev)
{
	if (current.indexes().size() > 0)
	{
		QFileInfo info = model.fileInfo(current.indexes()[0]);
		m_pView->SelectFileFromTree(info.absoluteFilePath());
	}
}

void widgetLeftView::onSearchAdd()
{
	SearchControls* last_sc = search_list[search_list.size() - 1];
	SearchControls* sc = new SearchControls(this);
	sc->m_searchTitle->addItems(header_list);
	search_list.append(sc);
	searchViewLayout->insertWidget(searchViewLayout->indexOf(last_sc) + 1, sc);
	btn_dell->setEnabled(true);
}

void widgetLeftView::onSearchDell()
{
	if (search_list.size() > 1)
	{
		SearchControls* sc = search_list[search_list.size() - 1];
		searchViewLayout->removeWidget(sc);
		search_list.erase(search_list.begin() + search_list.size() - 1);
		delete sc;
	}
	if (search_list.size() < 2)
	{
		btn_dell->setEnabled(false);
	}
}

void widgetLeftView::onSearchMemoAdd()
{
	SearchControls* last_sc = memo_list[memo_list.size() - 1];
	SearchControls* sc = new SearchControls(this);
	sc->m_searchTitle->addItems(memo_combo_header);
	memo_list.append(sc);
	searchViewLayout->insertWidget(searchViewLayout->indexOf(last_sc) + 1, sc);
	btn_memo_dell->setEnabled(true);
}

void widgetLeftView::onSearchMemoDell()
{
	if (memo_list.size() > 1)
	{
		SearchControls* sc = memo_list[memo_list.size() - 1];
		searchViewLayout->removeWidget(sc);
		memo_list.erase(memo_list.begin() + memo_list.size() - 1);
		delete sc;
	}
	if (memo_list.size() < 2)
	{
		btn_memo_dell->setEnabled(false);
	}
}

void widgetLeftView::onSearchTagAdd()
{
	SearchControls* last_sc = tag_list[tag_list.size() - 1];
	SearchControls* sc = new SearchControls(this);
	sc->m_searchTitle->addItems(tag_combo_header);
	tag_list.append(sc);
	searchViewLayout->insertWidget(searchViewLayout->indexOf(last_sc) + 1, sc);
	btn_memo_dell->setEnabled(true);
}

void widgetLeftView::onSearchTagDell()
{
	if (tag_list.size() > 1)
	{
		SearchControls* sc = tag_list[memo_list.size() - 1];
		searchViewLayout->removeWidget(sc);
		tag_list.erase(tag_list.begin() + tag_list.size() - 1);
		delete sc;
	}
	if (tag_list.size() < 2)
	{
		btn_tag_dell->setEnabled(false);
	}
}

void widgetLeftView::ViewUser(bool show)
{
	ui.tabWidget->setTabVisible(3, show);
	if(show)
		setUserList();
}

void widgetLeftView::doSearch1()
{
	if (m_pView->DBConnected())
	{
		QVariantList data;
		QMap< int, bool > total_search_file_index;
		//QMap< int, QList<QPair<int, int>>> total_file_to_block;
		QMap< int, QMap<int, QMap<int, QList< QString>>>> total_file_to_block2;
		//QMap< int, QList<QString>> total_file_to_word;
		QMap< int, QList<QPair<int, QString>>> total_file_to_header;

		QString prev_condition_name;
		QString query;
		for (int i = 0; i < search_list.size(); i++)
		{
			SearchControls* sc = search_list[i];
			QString header_name = sc->m_searchTitle->currentText();
			QString search_word = sc->m_searchWord->text();

			if (search_word.length() > 0)
			{
				QString condition_name = sc->m_searchCondition->currentText();

				QList< int > search_file_index;

				int header_index = header_to_index[sc->m_searchTitle->currentText()];
				if (header_index > 0)
				{
					//	meta 검색
					query = QString("SELECT file_id, value FROM header_info WHERE header_id=%1 AND value LIKE \"%%2%\"").arg(header_index).arg(search_word);
					m_pView->db->exec(query, data);
					for (const auto& item : data)
					{
						auto map = item.toMap();
						int file_id = map["file_id"].toInt();
						QString value = map["value"].toString();
						search_file_index.append(file_id);
						if (prev_condition_name != "NOT")
						{
							int index = value.indexOf(search_word);
							QString info_str = QString("[%1] : %2<font color=\"red\">%3</font>%4").arg(header_name).arg(value.left(index)).arg(search_word).arg(value.right(value.length() - index - search_word.length()));
							total_file_to_header[file_id].append(QPair<int, QString>(header_index, info_str));
						}
					}
				}
				else
				{
					//	내용 검색
					query = QString("SELECT file_id, page_no, block_no FROM page_info WHERE block_text LIKE \"%%1%\"").arg(search_word);
					m_pView->db->exec(query, data);
					for (const auto& item : data)
					{
						auto map = item.toMap();
						int file_id = map["file_id"].toInt();
						int page_no = map["page_no"].toInt();
						int block_no = map["block_no"].toInt();
						search_file_index.append(file_id);
						if (prev_condition_name != "NOT")
						{
							total_file_to_block2[file_id][page_no][block_no].append(search_word);
							//total_file_to_block[file_id].append(QPair<int, int>(page_no, block_no));
							//total_file_to_word[file_id].append(search_word);
						}
					}
				}

				if (i == 0)
				{
					for (int j = 0; j < search_file_index.size(); j++)
					{
						total_search_file_index[search_file_index[j]] = true;
					}
				}
				else
				{
					if (prev_condition_name == "AND")
					{
						QList< int > temp_file_index;
						for (int j = 0; j < search_file_index.size(); j++)
						{
							if (total_search_file_index.contains(search_file_index[j]))
							{
								temp_file_index.append(search_file_index[j]);
							}
						}

						total_search_file_index.clear();
						for (int j = 0; j < temp_file_index.size(); j++)
						{
							total_search_file_index[temp_file_index[j]] = true;
						}
					}
					else if (prev_condition_name == "OR")
					{
						for (int j = 0; j < search_file_index.size(); j++)
						{
							total_search_file_index[search_file_index[j]] = true;
						}
					}
					else if (prev_condition_name == "NOT")
					{
						for (int j = 0; j < search_file_index.size(); j++)
						{
							total_search_file_index[search_file_index[j]] = false;
						}
					}
					else
					{
						//	이상 버림
					}
				}

				prev_condition_name = condition_name;
			}
		}

		QTreeWidgetItem* this_search = new QTreeWidgetItem();
		//	결과 표시
		int total_count = 0;
		int file_count = 0;
		QList<int> file_id_list = total_search_file_index.keys();
		for (int i = 0; i < file_id_list.size(); i++)
		{
			file_count = 0;
			int file_id = file_id_list[i];
			if (total_search_file_index[file_id])
			{
				QString file_name;
				m_pView->db->exec(QString("SELECT file_name FROM file_info WHERE id=%1").arg(file_id), data);
				for (const auto& item : data)
				{
					auto map = item.toMap();
					file_name = map["file_name"].toString();
				}

				QTreeWidgetItem* this_file = new QTreeWidgetItem(this_search);
				if (total_file_to_header.contains(file_id))
				{
					for (int j = 0; j < total_file_to_header[file_id].size(); j++)
					{
						QTreeWidgetItem* this_info = new QTreeWidgetItem(this_file);
						QLabel* this_info_label = new QLabel();
						this_info_label->setText(total_file_to_header[file_id][j].second);
						m_pView->_widgetBottomView->m_outputTree->setItemWidget(this_info, 0, this_info_label);
						QString data_str = QString("%1/0/0").arg(file_id);
						this_info->setData(0, Qt::AccessibleTextRole, data_str);
						//this_info->setText(0, total_file_to_header[file_id][j].second);
						total_count++;
						file_count++;
					}
				}

				if (total_file_to_block2.contains(file_id))
				{
					QString file_contents;
					QMap<int, QMap<int, int> > page_block_to_index;
					QList<int> page_block_to_index_order;
					query = QString("SELECT block_text, page_no, block_no FROM page_info WHERE file_id=%1 ORDER BY page_no, block_no").arg(file_id);
					m_pView->db->exec(query, data);
					for (const auto& item : data)
					{
						auto map = item.toMap();
						if (file_contents != "")
							file_contents += " ";

						int temp_page_no = map["page_no"].toInt();
						int temp_block_no = map["block_no"].toInt();
						page_block_to_index[temp_page_no][temp_block_no] = file_contents.length();
						page_block_to_index_order.append(file_contents.length());

						file_contents += map["block_text"].toString();
					}

					int file_length = file_contents.length();
					QList<int> page_no_keys = total_file_to_block2[file_id].keys();
					for (int j = 0; j < page_no_keys.size(); j++)
					{
						QList<int> block_no_keys = total_file_to_block2[file_id][page_no_keys[j]].keys();
						for (int k = 0; k < block_no_keys.size(); k++)
						{
							QStringList search_words = total_file_to_block2[file_id][page_no_keys[j]][block_no_keys[k]];
							for (int l = 0; l < search_words.size(); l++)
							{
								int start_index = page_block_to_index[page_no_keys[j]][block_no_keys[k]];
								int next_index = page_block_to_index_order.indexOf(start_index) + 1;
								int end_index = file_contents.length();
								if (next_index < page_block_to_index_order.count())
								{
									end_index = page_block_to_index_order[next_index];
								}
								int search_index = file_contents.indexOf(search_words[l], start_index);
								int search_word_count = search_words[l].length();
								while (search_index > -1 && search_index < end_index)
								{
									int temp_length = file_length - search_index - search_word_count;
									if (temp_length > 100)
										temp_length = 100;
									QString info_str = QString("[%1 page[%2] block[%3]] : <font color=\"red\">%4</font>%5")
										.arg(search_words[l])
										.arg(page_no_keys[j])
										.arg(block_no_keys[k])
										.arg(search_words[l])
										.arg(file_contents.mid(search_index + search_word_count, temp_length));

									QTreeWidgetItem* this_info = new QTreeWidgetItem(this_file);
									QLabel* this_info_label = new QLabel();
									this_info_label->setText(info_str);
									m_pView->_widgetBottomView->m_outputTree->setItemWidget(this_info, 0, this_info_label);
									QString data_str = QString("%1/%2/%3").arg(file_id).arg(page_no_keys[j]).arg(block_no_keys[k]);
									this_info->setData(0, Qt::AccessibleTextRole, data_str);
									search_index = file_contents.indexOf(search_words[l], search_index + search_word_count);
									total_count++;
									file_count++;
								}
							}
						}
					}
				}
				QString temp_info_str = QString("<font color=\"blue\">%1 [%2]</font>").arg(file_name).arg(file_count);
				QLabel* temp_label = new QLabel();
				temp_label->setText(temp_info_str);
				m_pView->_widgetBottomView->m_outputTree->setItemWidget(this_file, 0, temp_label);
				//this_file->setText(0, QString("<font color=\"blue\">%1 [%2]</font>").arg(file_name).arg(file_count));
				this_file->setExpanded(true);
			}
		}
		this_search->setText(0, QString("%1 [%2]").arg(QDateTime::currentDateTime().toString()).arg(total_count));
		this_search->setExpanded(true);
		m_pView->_widgetBottomView->AddResult(this_search);
	}
}

void widgetLeftView::doSearch2()
{
	if (m_pView->DBConnected())
	{
		QVariantList data;
		QMap< int, bool > total_search_file_index;
		QMap< int, QList<QString>> total_file_find;
		QMap< int, QList<QString>> total_file_find_info;

		QString prev_condition_name;
		QString query;
		for (int i = 0; i < memo_list.size(); i++)
		{
			SearchControls* sc = memo_list[i];
			QString header_name = sc->m_searchTitle->currentText();
			QString search_word = sc->m_searchWord->text();

			if (search_word.length() > 0)
			{
				QString condition_name = sc->m_searchCondition->currentText();

				QList< int > search_file_index;

				if (sc->m_searchTitle->currentText() == QString::fromLocal8Bit("내용"))
				{
					query = QString("SELECT reply_info.id, reply_info.file_id, reply_info.parent_id, reply_info.user_id, reply_info.value, reply_info.date_time, user_info.user_name FROM reply_info INNER JOIN user_info ON reply_info.user_id = user_info.user_id WHERE reply_info.value LIKE \"%%1%\"").arg(search_word);
					m_pView->db->exec(query, data);
					for (const auto& item : data)
					{
						auto map = item.toMap();
						int memo_id = map["id"].toInt();
						int file_id = map["file_id"].toInt();
						int parent_id = map["parent_id"].toInt();
						QString user_id = map["user_id"].toString();
						QString user_name = map["user_name"].toString();
						QString memo_str = map["value"].toString();
						QString date_time = map["date_time"].toString();
						search_file_index.append(file_id);
						if (prev_condition_name != "NOT")
						{
							int index = memo_str.indexOf(search_word);
							while (index > -1)
							{
								QString info_str = QString::fromLocal8Bit("[%1] : %2<font color=\"red\">%3</font>%4").arg(QString::fromLocal8Bit("내용")).arg(memo_str.left(index)).arg(search_word).arg(memo_str.right(memo_str.length() - index - search_word.length()));
								total_file_find[file_id].append(info_str);
								QString info_info_str = QString("%1/%2/%3/%4").arg(file_id).arg(memo_id).arg(index).arg(search_word.length());
								total_file_find_info[file_id].append(info_info_str);

								index = memo_str.indexOf(search_word, index + search_word.length());
							}
						}
					}
				}
				else if (sc->m_searchTitle->currentText() == QString::fromLocal8Bit("작성자"))
				{
					query = QString("SELECT reply_info.id, reply_info.file_id, reply_info.parent_id, reply_info.user_id, reply_info.value, reply_info.date_time, user_info.user_name FROM reply_info INNER JOIN user_info ON reply_info.user_id = user_info.user_id WHERE user_info.user_name LIKE \"%%1%\"").arg(search_word);
					m_pView->db->exec(query, data);
					for (const auto& item : data)
					{
						auto map = item.toMap();
						int memo_id = map["id"].toInt();
						int file_id = map["file_id"].toInt();
						int parent_id = map["parent_id"].toInt();
						QString user_id = map["user_id"].toString();
						QString user_name = map["user_name"].toString();
						QString memo_str = map["value"].toString();
						QString date_time = map["date_time"].toString();
						search_file_index.append(file_id);
						if (prev_condition_name != "NOT")
						{
							int index = user_name.indexOf(search_word);
							while (index > -1)
							{
								QString info_str = QString::fromLocal8Bit("[%1] : %2<font color=\"red\">%3</font>%4").arg(QString::fromLocal8Bit("작성자")).arg(user_name.left(index)).arg(search_word).arg(user_name.right(user_name.length() - index - search_word.length()));
								total_file_find[file_id].append(info_str);
								QString info_info_str = QString("%1/%2/%3/%4").arg(file_id).arg(memo_id).arg(index).arg(search_word.length());
								total_file_find_info[file_id].append(info_info_str);

								index = user_name.indexOf(search_word, index + search_word.length());
							}
						}
					}
				}
				else if (sc->m_searchTitle->currentText() == QString::fromLocal8Bit("날짜"))
				{
					QDateTime search_time = QDateTime::fromString(search_word, "yyyy-MM-dd");
					query = QString("SELECT reply_info.id, reply_info.file_id, reply_info.parent_id, reply_info.user_id, reply_info.value, reply_info.date_time, user_info.user_name FROM reply_info INNER JOIN user_info ON reply_info.user_id = user_info.user_id WHERE reply_info.date_time LIKE \"%%1%\"").arg(search_time.toString("yyyy-MM-dd"));
					m_pView->db->exec(query, data);
					for (const auto& item : data)
					{
						auto map = item.toMap();
						int memo_id = map["id"].toInt();
						int file_id = map["file_id"].toInt();
						int parent_id = map["parent_id"].toInt();
						QString user_id = map["user_id"].toString();
						QString user_name = map["user_name"].toString();
						QString memo_str = map["value"].toString();
						QString date_time = map["date_time"].toString();
						search_file_index.append(file_id);
						if (prev_condition_name != "NOT")
						{
							QString info_str = QString::fromLocal8Bit("[%1 : <font color=\"red\">%2</font>] : %3")
								.arg(QString::fromLocal8Bit("날짜"))
								.arg(search_time.toString("yyyy-MM-dd"))
								.arg(memo_str);
							total_file_find[file_id].append(info_str);
							QString info_info_str = QString("%1/%2/%3/%4").arg(file_id).arg(memo_id).arg(-1).arg(-1);
							total_file_find_info[file_id].append(info_info_str);
						}
					}
				}

				if (i == 0)
				{
					for (int j = 0; j < search_file_index.size(); j++)
					{
						total_search_file_index[search_file_index[j]] = true;
					}
				}
				else
				{
					if (prev_condition_name == "AND")
					{
						QList< int > temp_file_index;
						for (int j = 0; j < search_file_index.size(); j++)
						{
							if (total_search_file_index.contains(search_file_index[j]))
							{
								temp_file_index.append(search_file_index[j]);
							}
						}

						total_search_file_index.clear();
						for (int j = 0; j < temp_file_index.size(); j++)
						{
							total_search_file_index[temp_file_index[j]] = true;
						}
					}
					else if (prev_condition_name == "OR")
					{
						for (int j = 0; j < search_file_index.size(); j++)
						{
							total_search_file_index[search_file_index[j]] = true;
						}
					}
					else if (prev_condition_name == "NOT")
					{
						for (int j = 0; j < search_file_index.size(); j++)
						{
							total_search_file_index[search_file_index[j]] = false;
						}
					}
					else
					{
						//	이상 버림
					}
				}

				prev_condition_name = condition_name;
			}
		}

		QTreeWidgetItem* this_search = new QTreeWidgetItem();
		//	결과 표시
		int total_count = 0;
		int file_count = 0;
		QList<int> file_id_list = total_search_file_index.keys();
		for (int i = 0; i < file_id_list.size(); i++)
		{
			file_count = 0;
			int file_id = file_id_list[i];
			if (total_search_file_index[file_id])
			{
				QString file_name;
				m_pView->db->exec(QString("SELECT file_name FROM file_info WHERE id=%1").arg(file_id), data);
				for (const auto& item : data)
				{
					auto map = item.toMap();
					file_name = map["file_name"].toString();
				}

				QTreeWidgetItem* this_file = new QTreeWidgetItem(this_search);
				if (total_file_find.contains(file_id))
				{
					for (int j = 0; j < total_file_find[file_id].size(); j++)
					{
						QTreeWidgetItem* this_info = new QTreeWidgetItem(this_file);
						QLabel* this_info_label = new QLabel();
						this_info_label->setText(total_file_find[file_id][j]);
						m_pView->_widgetBottomView->m_outputTree->setItemWidget(this_info, 0, this_info_label);
						//QString data_str = QString("%1/0/0").arg(file_id);
						this_info->setData(0, Qt::AccessibleTextRole, total_file_find_info[file_id][j]);
						//this_info->setText(0, total_file_to_header[file_id][j].second);
						total_count++;
						file_count++;
					}
				}
				this_file->setText(0, QString("%1 [%2]").arg(file_name).arg(file_count));
			}
		}
		this_search->setText(0, QString("%1 [%2]").arg(QDateTime::currentDateTime().toString()).arg(total_count));

		m_pView->_widgetBottomView->AddResult(this_search);
	}
}

void widgetLeftView::doSearch3()
{
	if (m_pView->DBConnected())
	{
		QVariantList data;
		QMap< int, bool > total_search_file_index;
		QMap< int, QList<QString>> total_file_find;
		QMap< int, QList<QString>> total_file_find_info;

		QMap< int, QList<int> > check_file_tags;

		QString prev_condition_name;
		QString query;
		for (int i = 0; i < tag_list.size(); i++)
		{
			SearchControls* sc = tag_list[i];
			QString header_name = sc->m_searchTitle->currentText();
			QString search_word = sc->m_searchWord->text();

			if (search_word.length() > 0)
			{
				QString condition_name = sc->m_searchCondition->currentText();

				QList< int > search_file_index;
				
				query = QString("SELECT file_to_hash.file_id, file_to_hash.tag_id FROM file_to_hash INNER JOIN hsah_tags ON file_to_hash.tag_id = hsah_tags.id WHERE hsah_tags.tags LIKE \"%%1%\"").arg(search_word);
				m_pView->db->exec(query, data);
				for (const auto& item : data)
				{
					auto map = item.toMap();
					int file_id = map["file_id"].toInt();
					int tag_id = map["tag_id"].toInt();
					search_file_index.append(file_id);
					check_file_tags[file_id].append(tag_id);
				}

				if (i == 0)
				{
					for (int j = 0; j < search_file_index.size(); j++)
					{
						total_search_file_index[search_file_index[j]] = true;
					}
				}
				else
				{
					if (prev_condition_name == "AND")
					{
						QList< int > temp_file_index;
						for (int j = 0; j < search_file_index.size(); j++)
						{
							if (total_search_file_index.contains(search_file_index[j]))
							{
								temp_file_index.append(search_file_index[j]);
							}
						}

						total_search_file_index.clear();
						for (int j = 0; j < temp_file_index.size(); j++)
						{
							total_search_file_index[temp_file_index[j]] = true;
						}
					}
					else if (prev_condition_name == "OR")
					{
						for (int j = 0; j < search_file_index.size(); j++)
						{
							total_search_file_index[search_file_index[j]] = true;
						}
					}
					else if (prev_condition_name == "NOT")
					{
						for (int j = 0; j < search_file_index.size(); j++)
						{
							total_search_file_index[search_file_index[j]] = false;
						}
					}
					else
					{
						//	이상 버림
					}
				}

				prev_condition_name = condition_name;
			}
		}

		QTreeWidgetItem* this_search = new QTreeWidgetItem();
		//	결과 표시
		int total_count = 0;
		int file_count = 0;
		QList<int> file_id_list = total_search_file_index.keys();
		for (int i = 0; i < file_id_list.size(); i++)
		{
			file_count = 0;
			int file_id = file_id_list[i];
			if (total_search_file_index[file_id])
			{
				QString file_name;
				m_pView->db->exec(QString("SELECT file_name FROM file_info WHERE id=%1").arg(file_id), data);
				for (const auto& item : data)
				{
					auto map = item.toMap();
					file_name = map["file_name"].toString();
				}

				QString output_string = "";
				QString tag_string = "";
				m_pView->db->exec(QString("SELECT tag_id FROM file_to_hash WHERE file_id=%1").arg(file_id), data);
				for (const auto& item : data)
				{
					auto map = item.toMap();
					int temp_tag_id = map["tag_id"].toInt();

					QString temp_info_str;
					if (check_file_tags[file_id].contains(temp_tag_id))
					{
						temp_info_str = QString("<font color=\"red\">#%1</font>").arg(tagDatas[temp_tag_id]);
						if (tag_string == "")
						{
							tag_string = tagDatas[temp_tag_id];
						}
						else
						{
							tag_string += ("," + tagDatas[temp_tag_id]);
						}
					}
					else
					{
						temp_info_str = ("#" + tagDatas[temp_tag_id]);
					}

					if (output_string == "")
					{
						output_string = temp_info_str;
					}
					else
					{
						output_string += (", " + temp_info_str);
					}
				}

				output_string = QString("%1 : [%2]").arg(file_name).arg(output_string);
				QTreeWidgetItem* this_info = new QTreeWidgetItem(this_search);
				QLabel* this_info_label = new QLabel();
				this_info_label->setText(output_string);
				m_pView->_widgetBottomView->m_outputTree->setItemWidget(this_info, 0, this_info_label);
				QString data_str = QString("%1/%2").arg(file_id).arg(tag_string);
				this_info->setData(0, Qt::AccessibleTextRole, data_str);
				//this_info->setText(0, total_file_to_header[file_id][j].second);
				total_count++;
			}
		}
		this_search->setText(0, QString("%1 [%2]").arg(QDateTime::currentDateTime().toString()).arg(total_count));

		m_pView->_widgetBottomView->AddResult(this_search);
	}
}

void widgetLeftView::onSearchMVClicked(QListWidgetItem* item)
{
	if (item != NULL)
	{
		QString tag_str = item->text();
		QMessageBox::StandardButton reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("[%1]을 삭제하시겠습니까?").arg(tag_str),
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
		{
			if (serchVMDatas.contains(tag_str))
			{
				serchVMDatas.remove(tag_str);
			}
			mvSearchList->takeItem(mvSearchList->row(item));
			delete item;
		}
	}
}

void widgetLeftView::onFileMVClicked(QListWidgetItem* current, QListWidgetItem* previous)
{
	if (current != NULL)
	{
		if (m_pView->m_iCurrentSelectedItemType == 3)
		{
			QString tag_str = current->data(Qt::AccessibleTextRole).toString();
			QStringList time_str_list = tag_str.split(":");
			if (time_str_list.count() == 3)
			{
				QTime target_time(time_str_list[0].toInt(), time_str_list[1].toInt(), time_str_list[2].toInt());
				int seconds = (((time_str_list[0].toInt() * 60) + time_str_list[1].toInt()) * 60) + time_str_list[2].toInt();
				m_pView->_widgetRightView->JumpTo(seconds);
			}
		}
	}
}

void widgetLeftView::onFileMVDClicked(QListWidgetItem* item)
{
	if (item != NULL)
	{
		if (m_pView->m_iCurrentFileDBID > 0)
		{
			QString tag_str = item->data(Qt::AccessibleTextRole).toString();
			QStringList time_str_list = tag_str.split(":");
			QTime target_time(time_str_list[0].toInt(), time_str_list[1].toInt(), time_str_list[2].toInt());
			int seconds = (((time_str_list[0].toInt() * 60) + time_str_list[1].toInt()) * 60) + time_str_list[2].toInt();
			if (timeToMemo.contains(seconds))
			{
				QMessageBox::StandardButton reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("[%1  %2]을 삭제하시겠습니까?")
					.arg(tag_str)
					.arg(timeToMemo[seconds]),
					QMessageBox::Yes | QMessageBox::No);
				if (reply == QMessageBox::Yes)
				{
					if (m_pView->DBConnected())
					{
						QString query = QString("DELETE FROM play_info WHERE file_id=%1 AND s_time=%2")
							.arg(m_pView->m_iCurrentFileDBID)
							.arg(seconds);
						m_pView->db->exec(query);

						timeToMemo.remove(seconds);

						refreshMVList();
					}
				}
			}
		}
	}
}

void widgetLeftView::onFileTagClicked(const QModelIndex& index)
{
	if (index.row() > -1)
	{
		QString tag_str = index.data().toString();
		int tag_id = fileTagData[tag_str];
		if (tag_id > 0)
		{
			QMessageBox::StandardButton reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("[%1]을 삭제하시겠습니까?").arg(tag_str),
				QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes)
			{
				if (m_pView->DBConnected())
				{
					QString query = QString("DELETE FROM file_to_hash WHERE file_id=%1 AND tag_id=%2")
						.arg(m_pView->m_iCurrentFileDBID)
						.arg(tag_id);
					m_pView->db->exec(query);
				}
				tagList->model()->removeRow(index.row());
				//fileTagModel->removeRow(index.row());
			}
		}
	}
}

//void widgetLeftView::onSearchTagClicked(const QModelIndex& index)
//{
//	if (index.row() > -1)
//	{
//		QString tag_str = index.data().toString();
//		QMessageBox::StandardButton reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("[%1]을 삭제하시겠습니까?").arg(tag_str),
//			QMessageBox::Yes | QMessageBox::No);
//		if (reply == QMessageBox::Yes)
//		{
//			if (searchTagToIndex.contains(tag_str))
//			{
//				int tag_index = searchTagToIndex[tag_str];
//
//				searchTagToIndex.remove(tag_str);
//				searchTagDatas.remove(tag_index);
//			}
//			searchTagModel->removeRow(index.row());
//		}
//	}
//}

void widgetLeftView::doSearch4()
{
	if (m_pView->DBConnected() == false)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스를 먼저 생성하세요."));
		return;
	}

	QList<QString> search_mv_list = serchVMDatas.keys();

	if (search_mv_list.size() > 0)
	{
		QVariantList data;
		QMap< int, int > check_file_ids;
		QMap< int, QList<QString> > file_to_result;
		for (int i = 0; i < search_mv_list.size(); i++)
		{
			QString search_text = search_mv_list[i];
			QString query = QString("SELECT file_id, s_title FROM play_info WHERE s_title LIKE \"%%1%\"").arg(search_text);
			m_pView->db->exec(query, data);
			if (i == 0)
			{
				for (const auto& item : data)
				{
					auto map = item.toMap();
					int file_id = map["file_id"].toInt();
					QString s_title = map["s_title"].toString();
					check_file_ids[file_id] = 0;

					QList<int> find_index;
					int index = s_title.indexOf(search_text);
					while (index > -1)
					{
						find_index.append(index);
						index = s_title.indexOf(search_text, index + 1);
					}

					QString result_info;
					index = 0;
					for (int j = 0; j < find_index.size(); j++)
					{
						int current_index = find_index[j];
						if (current_index > index)
							result_info += s_title.mid(index, current_index - index);

						result_info += QString("<font color=\"red\">%1</font>").arg(search_text);
						index = current_index + search_text.length();
					}
					result_info += s_title.right(s_title.length() - index);

					file_to_result[file_id].append(result_info);
				}
			}
			else
			{
				for (const auto& item : data)
				{
					auto map = item.toMap();
					int file_id = map["file_id"].toInt();
					if (check_file_ids.contains(file_id))
						check_file_ids[file_id] = i;
				}

				QList<int> temp_file_ids = check_file_ids.keys();
				for (int j = 0; j < temp_file_ids.size(); j++)
				{
					if (check_file_ids[temp_file_ids[j]] < i)
					{
						check_file_ids.remove(temp_file_ids[j]);
					}
				}

				if (check_file_ids.size() < 1)
				{
					break;
				}
			}
		}

		QTreeWidgetItem* this_search = new QTreeWidgetItem();
		//	결과 표시
		int total_count = 0;
		int file_count = 0;
		QList<int> find_file_ids = check_file_ids.keys();
		for (int i = 0; i < find_file_ids.size(); i++)
		{
			int file_id = find_file_ids[i];
			QString file_name;
			file_count = 0;
			m_pView->db->exec(QString("SELECT file_name FROM file_info WHERE id=%1").arg(file_id), data);
			for (const auto& item : data)
			{
				auto map = item.toMap();
				file_name = map["file_name"].toString();
			}

			QTreeWidgetItem* this_file = new QTreeWidgetItem(this_search);
			for (int j = 0; j < file_to_result[file_id].size(); j++)
			{
				QTreeWidgetItem* this_info = new QTreeWidgetItem(this_file);
				QLabel* this_info_label = new QLabel();
				this_info_label->setText(file_to_result[file_id][j]);
				m_pView->_widgetBottomView->m_outputTree->setItemWidget(this_info, 0, this_info_label);
				QString data_str = QString("%1/0/0").arg(file_id);
				this_info->setData(0, Qt::AccessibleTextRole, data_str);
				//this_info->setText(0, total_file_to_header[file_id][j].second);
				total_count++;
				file_count++;
			}
			this_file->setText(0, QString("%1 [%2]").arg(file_name).arg(file_count));
		}
		this_search->setText(0, QString("%1 [%2]").arg(QDateTime::currentDateTime().toString()).arg(total_count));

		m_pView->_widgetBottomView->AddResult(this_search);
	}
}

void widgetLeftView::UpdateMemo(SEARCH_TYPE search_type, QString file_info1, QString file_info2, QString file_info3)
{
	if (m_pView->m_iCurrentFileDBID > 0)
	{
		if (m_pView->DBConnected())
		{
			clearMemo();

			int search_memo_id = -1;
			int search_index = -1;
			int search_length = -1;
			if (search_type == MEMO)
			{
				if (file_info1 != "")
				{
					search_memo_id = file_info1.toInt();
				}
				if (file_info2 != "")
				{
					search_index = file_info2.toInt();
				}
				if (file_info3 != "")
				{
					search_length = file_info3.toInt();
				}
			}

			QList< MemoData* > temp_memo_list;
			QVariantList data;
			//QString query = QString("SELECT * FROM reply_info WHERE file_id=%1 ORDER BY date_time")
			//	.arg(m_pView->m_iCurrentFileDBID);
			QString query = QString("SELECT reply_info.id, reply_info.parent_id, reply_info.user_id, reply_info.value, reply_info.date_time, user_info.user_name FROM reply_info INNER JOIN user_info ON reply_info.user_id = user_info.user_id WHERE reply_info.file_id=%1 ORDER BY date_time")
				.arg(m_pView->m_iCurrentFileDBID);
			m_pView->db->exec(query, data);
			int memo_id = 0;
			int parent_id = 0;
			QString user_id;
			QString user_name;
			QString memo_text;
			QString memo_date;
			widgetMemo* current_memo = NULL;

			for (const auto& item : data)
			{
				auto map = item.toMap();
				memo_id = map["id"].toInt();
				parent_id = map["parent_id"].toInt();
				user_id = map["user_id"].toString();
				user_name = map["user_name"].toString();
				memo_text = map["value"].toString();
				memo_date = map["date_time"].toString();

				MemoData* new_memo = new MemoData(memo_id, parent_id, user_id, user_name, memo_text, memo_date);
				if (search_memo_id == memo_id)
				{
					if (search_index == -1)
					{
						new_memo->m_str_datetime = QString("<font color=\"green\">%1</font>").arg(new_memo->m_str_datetime);
					}
					else
					{
						new_memo->m_memo = new_memo->m_memo.insert(search_index + search_length, "</font>");
						new_memo->m_memo = new_memo->m_memo.insert(search_index, "<font color=\"green\">");
					}
				}

				memoDatas[memo_id] = new_memo;
				if (parent_id > 0)
				{
					if (memoDatas.contains(parent_id))
					{
						new_memo->m_level = memoDatas[parent_id]->m_level + 1;
						memoDatas[parent_id]->chileMemo.append(new_memo);
					}
					else
					{
						temp_memo_list.append(new_memo);
					}
				}
				else
				{
					temp_memo_list.append(new_memo);
				}
			}

			for (int i = 0; i < temp_memo_list.size(); i++)
			{
				MemoData* new_memo = temp_memo_list[i];
				widgetMemo* temp_memo = AddMemoControl(new_memo, search_memo_id);
				if (temp_memo != NULL)
					current_memo = temp_memo;
			}

			if (current_memo != NULL)
			{
				techScroll->ensureWidgetVisible(current_memo);
			}
			else
			{
				techScroll->verticalScrollBar()->setSliderPosition(techScroll->verticalScrollBar()->maximum());
			}


			clearTags();

			QStringList tags;
			if (search_type == HASHTAG)
			{
				tags = file_info1.split(",");
			}
			query = QString("SELECT tag_id FROM file_to_hash WHERE file_id=%1")
				.arg(m_pView->m_iCurrentFileDBID);
			m_pView->db->exec(query, data);
			int tag_id = 0;
			for (const auto& item : data)
			{
				auto map = item.toMap();
				tag_id = map["tag_id"].toInt();

				if (tagDatas.contains(tag_id))
				{
					//int row = fileTagModel->rowCount();
					//fileTagModel->insertRow(row);
					//QModelIndex _index = fileTagModel->index(row);
					QString new_tag = "#" + tagDatas[tag_id];

					QListWidgetItem* item = new QListWidgetItem(new_tag);
					tagList->addItem(item);
					if (tags.contains(tagDatas[tag_id]))
					{
						item->setForeground(Qt::green);
					}
					fileTagData[new_tag] = tag_id;
				}
			}

			clearMVs();

			query = QString("SELECT s_time, s_title FROM play_info WHERE file_id=%1")
				.arg(m_pView->m_iCurrentFileDBID);
			m_pView->db->exec(query, data);
			for (const auto& item : data)
			{
				auto map = item.toMap();
				int s_time = map["s_time"].toInt();
				QString s_title = map["s_title"].toString();

				timeToMemo[s_time] = s_title;
			}
			refreshMVList();
		}
	}
}

void widgetLeftView::clearMVs()
{
	mvList->clear();
	timeToMemo.clear();
}

void widgetLeftView::clearTags()
{
	tagList->model()->removeRows(0, tagList->model()->rowCount());
	//fileTagModel->removeRows(0, fileTagModel->rowCount());
}

void widgetLeftView::clearMemo()
{
	QList<MemoData*> memo_list = memoDatas.values();
	for (int i = 0; i < memo_list.count(); i++)
	{
		delete memo_list[i];
	}

	for (int i = 0; i < memo_control_list.count(); i++)
	{
		memoList->layout()->removeWidget(memo_control_list[i]);
		delete memo_control_list[i];
	}
	memoDatas.clear();
	memo_control_list.clear();
}

widgetMemo* widgetLeftView::AddMemoControl(MemoData* new_memo, int search_memo_id, MemoData* parent_memo)
{
	widgetMemo* search_memo = NULL;
	widgetMemo* memo = new widgetMemo(this);
	memo->setLevel(new_memo->m_level);
	//memo->setObjectName("mymemo");
	//memo->setStyleSheet("QWidget#mymemo{background:white; border: 1px solid red;}");
	memo->setDate(new_memo->m_str_datetime);
	memo->setMemo(new_memo->m_memo);
	memo->setUserName(new_memo->m_username);
	memo->memo_id = new_memo->m_id;
	memo_control_list.append(memo);
	new_memo->connected_control = memo;

	if (parent_memo != NULL && parent_memo->connected_control != NULL)
	{
		int p_index = memoList->layout()->indexOf(parent_memo->connected_control);
		((QVBoxLayout*)(memoList->layout()))->insertWidget(p_index + 1, memo);
	}
	else
	{
		memoList->layout()->addWidget(memo);
	}
	for (int j = 0; j < new_memo->chileMemo.size(); j++)
	{
		widgetMemo* temp_memo = AddMemoControl(new_memo->chileMemo[j], search_memo_id);
		if (temp_memo != NULL)
			search_memo = temp_memo;
	}

	if (memo->memo_id == search_memo_id)
		return memo;
	return search_memo;
}

void widgetLeftView::doAddMemo()
{
	if (m_pView->m_loginUserID == "admin")
	{
		QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("admin 계정으로는 메모를 작성할 수 없습니다."));
		return;
	}

	if (m_pView->DBConnected() == false)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스를 먼저 생성하세요."));
		return;
	}

	if (m_pView->m_iCurrentFileDBID > 0)
	{
		QString memo_str = memoText->toPlainText();
		if (memo_str != "")
		{
			QVariantList data;
			QString query = QString("INSERT INTO reply_info VALUES (NULL, %1, %2, \"%3\", \"%4\", datetime('now', 'localtime'))")
				.arg(m_pView->m_iCurrentFileDBID)
				.arg(parent_memo_id)
				.arg(m_pView->m_loginUserID)
				.arg(memo_str);
			m_pView->db->exec(query);

			query = QString("SELECT max(id) FROM reply_info");
			m_pView->db->exec(query, data);
			int memo_id = 0;
			for (const auto& item : data)
			{
				auto map = item.toMap();
				memo_id = map["max(id)"].toInt();
			}
			QString memo_date = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
			MemoData* new_memo = new MemoData(memo_id, parent_memo_id, m_pView->m_loginUserID, m_pView->m_loginUserName, memo_str, memo_date);
			memoDatas[memo_id] = new_memo;
			MemoData* parent_memo = NULL;
			if (parent_memo_id > 0)
			{
				if (memoDatas.contains(parent_memo_id))
				{
					parent_memo = memoDatas[parent_memo_id];
					new_memo->m_level = memoDatas[parent_memo_id]->m_level + 1;
					memoDatas[parent_memo_id]->chileMemo.append(new_memo);
				}
			}

			AddMemoControl(new_memo, -1, parent_memo);

			memoText->clear();
		}
	}
}

//void widgetLeftView::onSearchMVAdd()
//{
//	QString tag_str = mvSearchEdit->text();
//	if (tag_str != "")
//	{
//		if (!serchVMDatas.contains(tag_str))
//		{
//			serchVMDatas[tag_str] = 1;
//			QListWidgetItem* mv_item = new QListWidgetItem(mvSearchList);
//			mv_item->setText(tag_str);
//			mvSearchList->addItem(mv_item);
//			mvSearchEdit->clear();
//		}
//	}
//}

//void widgetLeftView::onSearchTagAdd()
//{
//	if (m_pView->DBConnected() == false)
//	{
//		QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스를 먼저 생성하세요."));
//		return;
//	}
//
//	QString tag_str = tagSearchEdit->text();
//	if (tag_str != "")
//	{
//		QVariantList data;
//		//	tag가 존재하는지 확인
//		QString query = QString("SELECT id FROM hsah_tags WHERE tags=\"%1\"")
//			.arg(tag_str);
//		m_pView->db->exec(query, data);
//		int tag_id = 0;
//		for (const auto& item : data)
//		{
//			auto map = item.toMap();
//			tag_id = map["id"].toInt();
//		}
//
//		if (tag_id < 1)
//		{
//			//	tag가 존재하지 않음
//			return;
//		}
//
//		if (!searchTagDatas.contains(tag_id))
//		{
//			searchTagDatas[tag_id] = tag_str;
//
//			int row = searchTagModel->rowCount();
//			searchTagModel->insertRow(row);
//			QModelIndex _index = searchTagModel->index(row);
//			QString new_tag = "#" + tag_str;
//			searchTagModel->setData(_index, new_tag);
//
//			searchTagToIndex[new_tag] = tag_id;
//		}
//
//		tagSearchEdit->clear();
//	}
//}

void widgetLeftView::doAddTag()
{
	if (m_pView->DBConnected() == false)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스를 먼저 생성하세요."));
		return;
	}

	if (m_pView->m_iCurrentFileDBID > 0)
	{
		QString tag_str = tagEdit->text();
		if (tag_str != "")
		{
			if (m_pView->DBConnected())
			{
				QVariantList data;
				//	tag가 존재하는지 확인
				QString query = QString("SELECT id FROM hsah_tags WHERE tags=\"%1\"")
					.arg(tag_str);
				m_pView->db->exec(query, data);
				int tag_id = 0;
				for (const auto& item : data)
				{
					auto map = item.toMap();
					tag_id = map["id"].toInt();
				}

				if (tag_id < 1)
				{
					//	tag가 존재하지 않음
					query = QString("INSERT INTO hsah_tags VALUES (NULL, \"%1\")")
						.arg(tag_str);
					m_pView->db->exec(query);

					query = QString("SELECT id FROM hsah_tags WHERE tags=\"%1\"")
						.arg(tag_str);
					m_pView->db->exec(query, data);
					for (const auto& item : data)
					{
						auto map = item.toMap();
						tag_id = map["id"].toInt();
					}
					tags.append(tag_str);
					tagDatas[tag_id] = tag_str;

					delete completer;
					completer = new QCompleter(tags, this);
					completer->setMaxVisibleItems(10);
					completer->setCompletionMode(QCompleter::CompletionMode::UnfilteredPopupCompletion);
					completer->setCaseSensitivity(Qt::CaseInsensitive);
					completer->setWrapAround(true);
					tagEdit->setCompleter(completer);

					//delete search_completer;
					//search_completer = new QCompleter(tags, this);
					//search_completer->setMaxVisibleItems(10);
					//search_completer->setCompletionMode(QCompleter::CompletionMode::UnfilteredPopupCompletion);
					//search_completer->setCaseSensitivity(Qt::CaseInsensitive);
					//search_completer->setWrapAround(true);
					//tagSearchEdit->setCompleter(search_completer);
				}

				query = QString("SELECT id FROM file_to_hash WHERE file_id=%1 AND tag_id=%2")
					.arg(m_pView->m_iCurrentFileDBID)
					.arg(tag_id);
				m_pView->db->exec(query, data);
				int temp_id = 0;
				for (const auto& item : data)
				{
					auto map = item.toMap();
					temp_id = map["id"].toInt();
				}

				if (temp_id > 0)
				{
					//	이미 등록됨
				}
				else
				{
					query = QString("INSERT INTO file_to_hash VALUES (NULL, %1, %2)")
						.arg(m_pView->m_iCurrentFileDBID)
						.arg(tag_id);
					m_pView->db->exec(query);

					//int row = fileTagModel->rowCount();
					//fileTagModel->insertRow(row);
					//QModelIndex _index = fileTagModel->index(row);
					QString new_tag = "#" + tag_str;
					//fileTagModel->setData(_index, new_tag);
					QListWidgetItem* item = new QListWidgetItem(new_tag);
					tagList->addItem(item);
					fileTagData[new_tag] = tag_id;
				}

				tagEdit->clear();
			}
		}
	}
}

void widgetLeftView::refreshMVList()
{
	mvList->clear();
	QList<int> times = timeToMemo.keys();
	std::sort(times.begin(), times.end());
	for (int i = 0; i < times.size(); i++)
	{
		QListWidgetItem* mv_item = new QListWidgetItem(mvList);
		mvList->addItem(mv_item);

		QLabel* mv_item_label = new QLabel();
		QTime temp_time(0, 0, 0);
		temp_time = temp_time.addSecs(times[i]);
		QString output_string = QString("<font color=\"blue\">%1</font>  %2").arg(temp_time.toString("hh:mm:ss")).arg(timeToMemo[times[i]]);
		mv_item_label->setText(output_string);
		mvList->setItemWidget(mv_item, mv_item_label);
		mv_item->setData(Qt::AccessibleTextRole, temp_time.toString("hh:mm:ss"));
	}
}

void widgetLeftView::doAddMV()
{
	if (m_pView->DBConnected() == false)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스를 먼저 생성하세요."));
		return;
	}

	if (m_pView->m_iCurrentFileDBID > 0)
	{
		QTime mv_time = mvTime->time();
		int seconds = QTime(0, 0, 0).secsTo(mv_time);

		QString mv_title = mvText->text();
		if (mv_title != "")
		{
			if (timeToMemo.contains(seconds))
			{
				QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("동일한 시간에 목차가 존재합니다."));
				return;
			}
			else
			{
				QString query = QString("INSERT INTO play_info VALUES (NULL, %1, %2, \"%3\")")
					.arg(m_pView->m_iCurrentFileDBID)
					.arg(seconds)
					.arg(mv_title);
				m_pView->db->exec(query);

				timeToMemo[seconds] = mv_title;

				refreshMVList();

				mvText->clear();
			}
		}
	}
}

void widgetLeftView::clearMemoSelection()
{
	for (int i = 0; i < memo_control_list.count(); i++)
	{
		memo_control_list[i]->setSelect(false);
	}
}

void widgetLeftView::OnMemoClicked(widgetMemo* pmemo)
{
	if (pmemo)
	{
		if (pmemo->memo_id > 0)
		{
			clearMemoSelection();
			//memo->setStyleSheet("QWidget#mymemo{background:white; border: 1px solid red;}");
			pmemo->setSelect(true);
			parent_memo_id = pmemo->memo_id;
			noteParent->setText(QString::fromLocal8Bit("답글 > ") + pmemo->user_name);
		}
	}
}

void widgetLeftView::doNewMemo()
{
	clearMemoSelection();
	parent_memo_id = 0;
	noteParent->setText(QString::fromLocal8Bit("새글"));
}

void widgetLeftView::setMVPos(int secs)
{
	QTime a(0, 0, 0);
	a = a.addSecs(secs);
	mvTime->setTime(a);
}

void widgetLeftView::setUserList()
{
	if (m_pView->DBConnected())
	{
		userTable->setRowCount(0);
		userTable->setColumnCount(3);
		userTable->setHorizontalHeaderLabels(QStringList() << "ID" << QString::fromLocal8Bit("이름") << QString::fromLocal8Bit("관리자"));
		QVariantList data;
		//	tag가 존재하는지 확인
		QString query = QString("SELECT user_id, user_name, read_only FROM user_info ORDER BY user_id");
		int row_count = 0;
		m_pView->db->exec(query, data);
		for (const auto& item : data)
		{
			auto map = item.toMap();
			QString tag_id = map["user_id"].toString();
			QString tag_str = map["user_name"].toString();
			int read_only = map["read_only"].toInt();

			row_count++;
			userTable->setRowCount(row_count);
			userTable->setItem(row_count - 1, 0, new QTableWidgetItem(tag_id));
			userTable->setItem(row_count - 1, 1, new QTableWidgetItem(tag_str));
			if (read_only == 1)
			{
				userTable->setItem(row_count - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("관리자")));
			}
			else
			{
				userTable->setItem(row_count - 1, 2, new QTableWidgetItem("-"));
			}
		}
	}
}

void widgetLeftView::doAddFile()
{
	QModelIndexList selection = userTable->selectionModel()->selectedRows();
	if (selection.count() > 0)
	{
		QModelIndex index = selection.at(0);
		QString user_id = userTable->item(index.row(), 0)->text();
		m_pView->AddFileList(user_id);
		setFileList(user_id);
	}
}

void widgetLeftView::setFileList(QString user_id)
{
	if (m_pView->DBConnected())
	{
		userTable_user_id = user_id;
		fileTable->setRowCount(0);
		fileTable->setColumnCount(2);
		fileTable->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("파일명") << QString::fromLocal8Bit("경로"));
		QVariantList data;
		//	tag가 존재하는지 확인
		QString query = QString("SELECT file_info.file_name, file_info.id FROM file_info INNER JOIN user_file_info on file_info.id = user_file_info.file_id WHERE user_file_info.user_id = \"%1\"").arg(user_id);
		int row_count = 0;
		m_pView->db->exec(query, data);
		for (const auto& item : data)
		{
			auto map = item.toMap();
			QString file_path = map["file_name"].toString();
			QString file_id = map["id"].toString();
			QFileInfo f_info(file_path);
			QString file_name = f_info.fileName();
			QString file_dir = file_path.left(file_path.length() - file_name.length());
			row_count++;
			fileTable->setRowCount(row_count);
			QTableWidgetItem* file_item = new QTableWidgetItem(file_name);
			file_item->setData(Qt::AccessibleTextRole, file_id);
			fileTable->setItem(row_count - 1, 0, file_item);
			fileTable->setItem(row_count - 1, 1, new QTableWidgetItem(file_dir));
		}
	}
}

void widgetLeftView::doDelFile()
{
	if (m_pView->DBConnected())
	{
		QModelIndexList selection = fileTable->selectionModel()->selectedRows();
		if (selection.count() > 0)
		{
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("[%1]개 파일을 삭제하시겠습니까?").arg(selection.count()),
				QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes)
			{
				for (int i = 0; i < selection.count(); i++)
				{
					QModelIndex index = selection.at(i);
					QString file_id = fileTable->item(index.row(), 0)->data(Qt::AccessibleTextRole).toString();
					QString query = QString("DELETE FROM user_file_info WHERE user_id=\"%1\" AND file_id=%2")
						.arg(userTable_user_id)
						.arg(file_id);
					m_pView->db->exec(query);
				}
				setFileList(userTable_user_id);
			}
		}
	}
}

void widgetLeftView::doAddUser()
{
	if(m_pView->DBConnected() == false)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스를 먼저 생성하세요."));
		return;
	}

	widgetAddUser login_dlg(this);
	login_dlg.setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	login_dlg.move(this->rect().center() - QPoint(login_dlg.width() / 2, login_dlg.height() / 2));
	if (login_dlg.exec() == QDialog::Accepted)
	{
		QString user_id = login_dlg.user_id;
		QString user_pass = login_dlg.user_pass;
		QString user_name = login_dlg.user_name;
		bool user_super = login_dlg.user_super;

		bool user_exist = false;
		QString prev_user_name;
		QVariantList data;
		QString query = QString("SELECT user_id, user_name FROM user_info WHERE user_id=\"%1\"").arg(user_id);
		m_pView->db->exec(query, data);
		for (const auto& item : data)
		{
			auto map = item.toMap();
			prev_user_name = map["user_name"].toString();
			user_exist = true;
		}

		if (user_exist)
		{
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("[%1] 사용자가 존재합니다. 암호와 이름을 변경하시겠습니까?").arg(user_id),
				QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes)
			{
				QString query = QString("UPDATE user_info SET user_pass=\"%2\", user_name=\"%3\", read_only=%4 WHERE user_id=\"%1\"")
					.arg(user_id)
					.arg(user_pass)
					.arg(user_name)
					.arg(user_super ? 1 : 0);
				m_pView->db->exec(query);

				setUserList();
			}
		}
		else
		{
			query = QString("INSERT INTO user_info VALUES (NULL, \"%1\", \"%2\", \"%3\", %4)")
				.arg(user_id)
				.arg(user_pass)
				.arg(user_name)
				.arg(user_super ? 1 : 0);
			m_pView->db->exec(query);

			setUserList();
		}
	}
}

void widgetLeftView::doDelUser()
{
	if (m_pView->DBConnected() == false)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스를 먼저 생성하세요."));
		return;
	}

	QModelIndexList selection = userTable->selectionModel()->selectedRows();
	if (selection.count() > 0)
	{
		QModelIndex index = selection.at(0);
		QString user_id = userTable->item(index.row(), 0)->text();
		QString user_name = userTable->item(index.row(), 1)->text();
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("[%1] [%2] 사용자를 삭제하시겠습니까?").arg(user_id).arg(user_name),
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
		{
			QString query = QString("DELETE FROM user_info WHERE user_id=\"%1\"")
				.arg(user_id);
			m_pView->db->exec(query);

			setUserList();
		}
	}
}

void widgetLeftView::onUserChanged(const QItemSelection& current, const QItemSelection& prev)
{
	if (current.indexes().size() > 0)
	{
		QModelIndex index = current.indexes()[0];
		QString user_id = userTable->item(index.row(), 0)->text();
		setFileList(user_id);
	}
}


void widgetLeftView::clearAll()
{
	clearMemo();
	clearTags();
	clearMVs();
}


void widgetLeftView::on_treeView_doubleClicked(const QModelIndex& index)
{
	//QMessageBox::information(this, "info", model.filePath(index));
	QDesktopServices::openUrl(QUrl::fromLocalFile(model.filePath(index)));
}