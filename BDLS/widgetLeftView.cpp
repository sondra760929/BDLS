#include "widgetLeftView.h"
#include <qscreen.h>
#include <QtWidgets/qmessagebox.h>
#include "BDLS.h"
#include "db_manager.h"
#include "MemoControls.h"
#include "widgetAddUser.h"

QStringList memo_combo_header = { "내용", "날짜" };
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

	//------------------------------------------------------------------------------
	searchViewLayout = new QVBoxLayout;

	QBoxLayout* temp_add = new QHBoxLayout;
	QLabel* label = new QLabel(this);
	label->setText("1. 메타 및 본문 검색");
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
	btn_search->setText("검색");
	searchViewLayout->addWidget(btn_search);

	label = new QLabel(this);
	label->setText("");
	searchViewLayout->addWidget(label);

	temp_add = new QHBoxLayout;
	label = new QLabel(this);
	label->setText("2. 메모 검색");
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
	btn_search2->setText("검색");
	searchViewLayout->addWidget(btn_search2);

	label = new QLabel(this);
	label->setText("");
	searchViewLayout->addWidget(label);

	label = new QLabel(this);
	label->setText("3. 해시태그 검색");
	searchViewLayout->addWidget(label);

	tagSearchList = new QListView(this);
	searchViewLayout->addWidget(tagSearchList);
	tagSearchList->setViewMode(QListView::ViewMode::IconMode);
	tagSearchList->setSpacing(10);

	temp_add = new QHBoxLayout;
	tagSearchEdit = new QLineEdit(this);
	QPushButton* tagSearchAdd = new QPushButton(this);
	tagSearchAdd->setText("추가");
	temp_add->addWidget(tagSearchEdit);
	temp_add->addWidget(tagSearchAdd);
	searchViewLayout->addLayout(temp_add);

	QPushButton* btn_search3 = new QPushButton(this);
	btn_search3->setText("검색");
	searchViewLayout->addWidget(btn_search3);

	label = new QLabel(this);
	label->setText("");
	searchViewLayout->addWidget(label);

	label = new QLabel(this);
	label->setText("4. 동영상 목차 검색");
	searchViewLayout->addWidget(label);

	mvSearchList = new QListWidget(this);
	searchViewLayout->addWidget(mvSearchList);

	temp_add = new QHBoxLayout;
	mvSearchEdit = new QLineEdit(this);
	QPushButton* mvSearchAdd = new QPushButton(this);
	mvSearchAdd->setText("추가");
	temp_add->addWidget(mvSearchEdit);
	temp_add->addWidget(mvSearchAdd);
	searchViewLayout->addLayout(temp_add);

	QPushButton* btn_search4 = new QPushButton(this);
	btn_search4->setText("검색");
	searchViewLayout->addWidget(btn_search4);

	searchViewLayout->addStretch(1);
	ui.searchview->setLayout(searchViewLayout);

	connect(btn_add, &QPushButton::clicked, this, &widgetLeftView::onSearchAdd);
	connect(btn_dell, &QPushButton::clicked, this, &widgetLeftView::onSearchDell);
	connect(btn_memo_add, &QPushButton::clicked, this, &widgetLeftView::onSearchMemoAdd);
	connect(btn_memo_dell, &QPushButton::clicked, this, &widgetLeftView::onSearchMemoDell);
	connect(tagSearchAdd, &QPushButton::clicked, this, &widgetLeftView::onSearchTagAdd);
	connect(mvSearchAdd, &QPushButton::clicked, this, &widgetLeftView::onSearchMVAdd);

	connect(tagSearchList, &QListView::clicked, this, &widgetLeftView::onSearchTagClicked);
	connect(mvSearchList, &QListWidget::itemClicked, this, &widgetLeftView::onSearchMVClicked);

	connect(btn_search, &QPushButton::clicked, this, &widgetLeftView::doSearch1);
	connect(btn_search2, &QPushButton::clicked, this, &widgetLeftView::doSearch2);
	connect(btn_search3, &QPushButton::clicked, this, &widgetLeftView::doSearch3);
	connect(btn_search4, &QPushButton::clicked, this, &widgetLeftView::doSearch4);

	//------------------------------------------------------------------------------
	noteViewLayout = new QVBoxLayout;
	ui.noteview->setLayout(noteViewLayout);

	label = new QLabel(this);
	label->setText("1. 메모");
	noteViewLayout->addWidget(label);

	QScrollArea* techScroll = new QScrollArea(this);
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
	noteParent->setText("새글");
	memoText = new QTextEdit(this);
	memoText->setMaximumHeight(50);
	QPushButton* noteAdd = new QPushButton(this);
	noteAdd->setText("등록");
	temp_add->addWidget(noteParent);
	temp_add->addWidget(memoText);
	temp_add->addWidget(noteAdd);
	noteViewLayout->addLayout(temp_add);

	label = new QLabel(this);
	label->setText("");
	noteViewLayout->addWidget(label);

	label = new QLabel(this);
	label->setText("2. 해시태그");
	noteViewLayout->addWidget(label);

	tagList = new QListView(this);
	noteViewLayout->addWidget(tagList);
	QSizePolicy sdTag(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sdTag.setVerticalStretch(2);
	tagList->setSizePolicy(sdTag);
	tagList->setViewMode(QListView::ViewMode::IconMode);
	tagList->setSpacing(10);

	temp_add = new QHBoxLayout;
	tagEdit = new QLineEdit(this);
	QPushButton* tagAdd = new QPushButton(this);
	tagAdd->setText("등록");
	temp_add->addWidget(tagEdit);
	temp_add->addWidget(tagAdd);
	noteViewLayout->addLayout(temp_add);

	label = new QLabel(this);
	label->setText("");
	noteViewLayout->addWidget(label);

	label = new QLabel(this);
	label->setText("3. 동영상 목차");
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
	mvAdd->setText("등록");
	temp_add->addWidget(mvTime);
	temp_add->addWidget(mvText);
	temp_add->addWidget(mvAdd);
	noteViewLayout->addLayout(temp_add);

	fileTagModel = new QStringListModel(this);
	tagList->setModel(fileTagModel);

	searchTagModel = new QStringListModel(this);
	tagSearchList->setModel(searchTagModel);

	completer = new QCompleter(this);
	tagEdit->setCompleter(completer);

	search_completer = new QCompleter(this);
	tagSearchEdit->setCompleter(search_completer);

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
	label->setText("1. 사용자");
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
	userAdd->setText("추가 / 변경");
	QPushButton* userUpdate = new QPushButton(this);
	userUpdate->setText("파일 목록 갱신");
	QPushButton* userDel = new QPushButton(this);
	userDel->setText("삭제");
	temp_add->addWidget(userAdd);
	temp_add->addWidget(userDel);
	temp_add->addWidget(userUpdate);
	userViewLayout->addLayout(temp_add);

	connect(userAdd, &QPushButton::clicked, this, &widgetLeftView::doAddUser);
	connect(userDel, &QPushButton::clicked, this, &widgetLeftView::doDelUser);
	connect(userUpdate, &QPushButton::clicked, this, &widgetLeftView::doUpdateUser);
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

	delete search_completer;
	search_completer = new QCompleter(tags, this);
	search_completer->setMaxVisibleItems(10);
	search_completer->setCompletionMode(QCompleter::CompletionMode::UnfilteredPopupCompletion);
	search_completer->setCaseSensitivity(Qt::CaseInsensitive);
	search_completer->setWrapAround(true);
	tagSearchEdit->setCompleter(search_completer);
}

void widgetLeftView::setSearchCombo(QMap<QString, int>& map_h_to_i)
{
	header_to_index.clear();
	QStringList key_list = map_h_to_i.keys();
	for (int i = 0; i < key_list.size(); i++)
	{
		header_to_index[key_list[i]] = map_h_to_i[key_list[i]];
	}
	header_to_index["내용 검색"] = 0;

	for (int i = 0; i < search_list.size(); i++)
	{
		search_list[i]->m_searchTitle->clear();
		search_list[i]->m_searchTitle->addItems(header_to_index.keys());
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
	sc->m_searchTitle->addItems(header_to_index.keys());
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

void widgetLeftView::ViewUser(bool show)
{
	ui.tabWidget->setTabEnabled(3, show);
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
					query = QString("SELECT block_text FROM page_info WHERE file_id=%1 ORDER BY page_no, block_no").arg(file_id);
					m_pView->db->exec(query, data);
					for (const auto& item : data)
					{
						auto map = item.toMap();
						if (file_contents != "")
							file_contents += " ";
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
								int search_index = file_contents.indexOf(search_words[l]);
								int search_word_count = search_words[l].length();
								while (search_index > -1)
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
				this_file->setText(0, QString("%1 [%2]").arg(file_name).arg(file_count));
			}
		}
		this_search->setText(0, QString("%1 [%2]").arg(QDateTime::currentDateTime().toString()).arg(total_count));

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

				if (sc->m_searchTitle->currentText() == "내용")
				{
					query = QString("SELECT * FROM reply_info INNER JOIN user_info ON reply_info.user_id = user_info.user_id WHERE reply_info.value LIKE \"%%1%\"").arg(search_word);
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
							QString info_str = QString("[%1] : %2<font color=\"red\">%3</font>%4").arg("내용").arg(memo_str.left(index)).arg(search_word).arg(memo_str.right(memo_str.length() - index - search_word.length()));
							total_file_find[file_id].append(info_str);
						}
					}
				}
				else if (sc->m_searchTitle->currentText() == "날짜")
				{
					QDateTime search_time = QDateTime::fromString(search_word, "yyyy-MM-dd");
					query = QString("SELECT * FROM reply_info INNER JOIN user_info ON reply_info.user_id = user_info.user_id WHERE reply_info.date_time LIKE \"%%1%\"").arg(search_time.toString("yyyy-MM-dd"));
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
							QString info_str = QString("[%1 : <font color=\"red\">%2</font>] : %3")
								.arg("날짜")
								.arg(search_time.toString("yyyy-MM-dd"))
								.arg(memo_str);
							total_file_find[file_id].append(info_str);
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
						QString data_str = QString("%1/0/0").arg(file_id);
						this_info->setData(0, Qt::AccessibleTextRole, data_str);
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
	QList<int> search_tag_ids = searchTagDatas.keys();

	if (search_tag_ids.size() > 0)
	{
		if (m_pView->DBConnected())
		{
			QVariantList data;
			QMap< int, int > check_file_ids;
			for (int i = 0; i < search_tag_ids.size(); i++)
			{
				QString query = QString("SELECT file_id FROM file_to_hash WHERE tag_id=%1").arg(search_tag_ids[i]);
				m_pView->db->exec(query, data);
				if (i == 0)
				{
					for (const auto& item : data)
					{
						auto map = item.toMap();
						int file_id = map["file_id"].toInt();
						check_file_ids[file_id] = 0;
					}
				}
				else
				{
					for (const auto& item : data)
					{
						auto map = item.toMap();
						int file_id = map["file_id"].toInt();
						if(check_file_ids.contains(file_id))
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
			QList<int> find_file_ids = check_file_ids.keys();
			for (int i = 0; i < find_file_ids.size(); i++)
			{
				int file_id = find_file_ids[i];
				QString file_name;
				m_pView->db->exec(QString("SELECT file_name FROM file_info WHERE id=%1").arg(file_id), data);
				for (const auto& item : data)
				{
					auto map = item.toMap();
					file_name = map["file_name"].toString();
				}

				QString output_string = "";
				m_pView->db->exec(QString("SELECT tag_id FROM file_to_hash WHERE file_id=%1").arg(file_id), data);
				for (const auto& item : data)
				{
					auto map = item.toMap();
					int temp_tag_id = map["tag_id"].toInt();

					QString temp_info_str;
					if (searchTagDatas.contains(temp_tag_id))
					{
						temp_info_str = QString("<font color=\"red\">#%1</font>").arg(tagDatas[temp_tag_id]);
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
				QString data_str = QString("%1/0/0").arg(file_id);
				this_info->setData(0, Qt::AccessibleTextRole, data_str);
				//this_info->setText(0, total_file_to_header[file_id][j].second);
				total_count++;
			}
			this_search->setText(0, QString("%1 [%2]").arg(QDateTime::currentDateTime().toString()).arg(total_count));

			m_pView->_widgetBottomView->AddResult(this_search);
		}
	}
}

void widgetLeftView::onSearchMVClicked(QListWidgetItem* item)
{
	if (item != NULL)
	{
		QString tag_str = item->text();
		QMessageBox::StandardButton reply = QMessageBox::question(this, QString("확인"), QString("[%1]을 삭제하시겠습니까?").arg(tag_str),
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
				QMessageBox::StandardButton reply = QMessageBox::question(this, QString("확인"), QString("[%1  %2]을 삭제하시겠습니까?")
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
			QMessageBox::StandardButton reply = QMessageBox::question(this, QString("확인"), QString("[%1]을 삭제하시겠습니까?").arg(tag_str),
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
				fileTagModel->removeRow(index.row());
			}
		}
	}
}

void widgetLeftView::onSearchTagClicked(const QModelIndex& index)
{
	if (index.row() > -1)
	{
		QString tag_str = index.data().toString();
		QMessageBox::StandardButton reply = QMessageBox::question(this, QString("확인"), QString("[%1]을 삭제하시겠습니까?").arg(tag_str),
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
		{
			if (searchTagToIndex.contains(tag_str))
			{
				int tag_index = searchTagToIndex[tag_str];

				searchTagToIndex.remove(tag_str);
				searchTagDatas.remove(tag_index);
			}
			searchTagModel->removeRow(index.row());
		}
	}
}
void widgetLeftView::doSearch4()
{
	QList<QString> search_mv_list = serchVMDatas.keys();

	if (search_mv_list.size() > 0)
	{
		if (m_pView->DBConnected())
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
}

void widgetLeftView::UpdateMemo()
{
	if (m_pView->m_iCurrentFileDBID > 0)
	{
		if (m_pView->DBConnected())
		{
			clearMemo();
			QList< MemoData* > temp_memo_list;
			QVariantList data;
			QString query = QString("SELECT * FROM reply_info WHERE file_id=%1 ORDER BY date_time")
				.arg(m_pView->m_iCurrentFileDBID);
			//QString query = QString("SELECT * FROM reply_info INNER JOIN user_info ON reply_info.user_id = user_info.user_id WHERE reply_info.file_id=%1 ORDER BY date_time")
			//	.arg(m_pView->m_iCurrentFileDBID);
			m_pView->db->exec(query, data);
			int memo_id = 0;
			int parent_id = 0;
			QString user_id;
			QString user_name;
			QString memo_text;
			QString memo_date;
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
				AddMemoControl(new_memo);
			}


			clearTags();
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
					int row = fileTagModel->rowCount();
					fileTagModel->insertRow(row);
					QModelIndex _index = fileTagModel->index(row);
					QString new_tag = "#" + tagDatas[tag_id];
					fileTagModel->setData(_index, new_tag);
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
	fileTagModel->removeRows(0, fileTagModel->rowCount());
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

void widgetLeftView::AddMemoControl(MemoData* new_memo, MemoData* parent_memo)
{
	MemoControls* memo = new MemoControls(this, new_memo->m_level);
	memo->setObjectName("mymemo");
	memo->setStyleSheet("QWidget#mymemo{background:white; border: 1px solid red;}");
	memo->setDate(new_memo->m_datetime.toString("yyyy-MM-dd  HH:mm:ss"));
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
		AddMemoControl(new_memo->chileMemo[j]);
	}
}

void widgetLeftView::doAddMemo()
{
	if (m_pView->m_iCurrentFileDBID > 0)
	{
		QString memo_str = memoText->toPlainText();
		if (memo_str != "")
		{
			if (m_pView->DBConnected())
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
				QString memo_date = QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss");
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

				AddMemoControl(new_memo, parent_memo);

				memoText->clear();
			}
		}
	}
}

void widgetLeftView::onSearchMVAdd()
{
	QString tag_str = mvSearchEdit->text();
	if (tag_str != "")
	{
		if (!serchVMDatas.contains(tag_str))
		{
			serchVMDatas[tag_str] = 1;
			QListWidgetItem* mv_item = new QListWidgetItem(mvSearchList);
			mv_item->setText(tag_str);
			mvSearchList->addItem(mv_item);
			mvSearchEdit->clear();
		}
	}
}

void widgetLeftView::onSearchTagAdd()
{
	QString tag_str = tagSearchEdit->text();
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
				return;
			}

			if (!searchTagDatas.contains(tag_id))
			{
				searchTagDatas[tag_id] = tag_str;

				int row = searchTagModel->rowCount();
				searchTagModel->insertRow(row);
				QModelIndex _index = searchTagModel->index(row);
				QString new_tag = "#" + tag_str;
				searchTagModel->setData(_index, new_tag);

				searchTagToIndex[new_tag] = tag_id;
			}

			tagSearchEdit->clear();
		}
	}
}

void widgetLeftView::doAddTag()
{
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

					delete search_completer;
					search_completer = new QCompleter(tags, this);
					search_completer->setMaxVisibleItems(10);
					search_completer->setCompletionMode(QCompleter::CompletionMode::UnfilteredPopupCompletion);
					search_completer->setCaseSensitivity(Qt::CaseInsensitive);
					search_completer->setWrapAround(true);
					tagSearchEdit->setCompleter(search_completer);
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

					int row = fileTagModel->rowCount();
					fileTagModel->insertRow(row);
					QModelIndex _index = fileTagModel->index(row);
					QString new_tag = "#" + tag_str;
					fileTagModel->setData(_index, new_tag);
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
	if (m_pView->m_iCurrentFileDBID > 0)
	{
		QTime mv_time = mvTime->time();
		int seconds = QTime(0, 0, 0).secsTo(mv_time);

		QString mv_title = mvText->text();
		if (mv_title != "")
		{
			if (timeToMemo.contains(seconds))
			{
				QMessageBox::question(this, QString("확인"), QString("동일한 시간에 목차가 존재합니다."));
				return;
			}
			else
			{
				if (m_pView->DBConnected())
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
}

void widgetLeftView::OnMemoClicked(MemoControls* pmemo)
{
	if (pmemo)
	{
		if (pmemo->memo_id > 0)
		{
			parent_memo_id = pmemo->memo_id;
			noteParent->setText("답글");
		}
	}
}

void widgetLeftView::doNewMemo()
{
	parent_memo_id = 0;
	noteParent->setText("새글");
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
		QStringList table_list = m_pView->db->tables();
		if (!table_list.contains("user_info"))
		{
			m_pView->db->exec("CREATE TABLE user_info (id INTEGER PRIMARY KEY, user_id TEXT, user_pass TEXT, user_name TEXT, read_only INTEGER)");
		}

		userTable->setRowCount(0);
		userTable->setColumnCount(2);
		userTable->setHorizontalHeaderLabels(QStringList() << "ID" << "이름");
		QVariantList data;
		//	tag가 존재하는지 확인
		QString query = QString("SELECT user_id, user_name FROM user_info ORDER BY user_id");
		int row_count = 0;
		m_pView->db->exec(query, data);
		for (const auto& item : data)
		{
			auto map = item.toMap();
			QString tag_id = map["user_id"].toString();
			QString tag_str = map["user_name"].toString();

			row_count++;
			userTable->setRowCount(row_count);
			userTable->setItem(row_count - 1, 0, new QTableWidgetItem(tag_id));
			userTable->setItem(row_count - 1, 1, new QTableWidgetItem(tag_str));
		}
	}
}

void widgetLeftView::doAddUser()
{
	widgetAddUser login_dlg(this);
	login_dlg.setModal(true);
	login_dlg.setWindowFlags(Qt::FramelessWindowHint);
	login_dlg.move(this->rect().center() - QPoint(login_dlg.width() / 2, login_dlg.height() / 2));
	login_dlg.setFocus();
	if (login_dlg.exec() == QDialog::Accepted)
	{
		QString user_id = login_dlg.user_id;
		QString user_pass = login_dlg.user_pass;
		QString user_name = login_dlg.user_name;

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
			reply = QMessageBox::question(this, QString("확인"), QString("[%1] 사용자가 존재합니다. 암호와 이름을 변경하시겠습니까?").arg(user_id),
				QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes)
			{
				QString query = QString("UPDATE user_info SET user_pass=\"%2\", user_name=\"%3\" WHERE user_id=\"%1\"")
					.arg(user_id)
					.arg(user_pass)
					.arg(user_name);
				m_pView->db->exec(query);

				setUserList();
			}
		}
		else
		{
			query = QString("INSERT INTO user_info VALUES (NULL, \"%1\", \"%2\", \"%3\", 1)")
				.arg(user_id)
				.arg(user_pass)
				.arg(user_name);
			m_pView->db->exec(query);

			setUserList();
		}
	}
}

void widgetLeftView::doDelUser()
{
	QModelIndexList selection = userTable->selectionModel()->selectedRows();
	if (selection.count() > 0)
	{
		QModelIndex index = selection.at(0);
		QString user_id = userTable->item(index.row(), 0)->text();
		QString user_name = userTable->item(index.row(), 1)->text();
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this, QString("확인"), QString("[%1] [%2] 사용자를 삭제하시겠습니까?").arg(user_id).arg(user_name),
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

void widgetLeftView::doUpdateUser()
{

}