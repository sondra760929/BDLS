#include "BDLS.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include <QTextCodec>
#include "FilterTableHeader.h"

QString m_strKey = QString("HKEY_CURRENT_USER\\SOFTWARE\\DIGIBOOK\\PDFIndexExplorer\\Settings");
QSettings m(m_strKey, QSettings::Registry64Format);
QStringList media_file_format;
BDLS::BDLS(QWidget* parent)
	: QMainWindow(parent)
	, db(NULL)
{
	ui.setupUi(this);
	style = QStyleFactory::create("Fusion");
	QApplication::setStyle(style);

	QString color_theme = m.value("THEME").toString();
	if (color_theme == "")
	{
		setColor3();
	}
	else if (color_theme == "1")
	{
		setColor1();
	}
	else if (color_theme == "2")
	{
		setColor2();
	}
	else if (color_theme == "3")
	{
		setColor3();
	}

	//m_titleBar = new TitleBar(this);
	//setMenuWidget(m_titleBar);
	//title_string = "BDLS (Big Data Library System)";
	//setWindowTitle(title_string);
	//m_titleBar->SetTitleBarIcon(":/BDLS/icons/database_search_icon.png");

	setWindowTitle("BDLS(Big Data Library System)");

	QPushButton* btnColor1 = new QPushButton(this);
	btnColor1->setFixedSize(20, 20);
	//btnColor1->setFlat(true);
	btnColor1->setStyleSheet("background-color:white");

	QPushButton* btnColor2 = new QPushButton(this);
	btnColor2->setFixedSize(20, 20);
	//btnColor2->setFlat(true);
	btnColor2->setStyleSheet("background-color:black");

	QPushButton* btnColor3 = new QPushButton(this);
	btnColor3->setFixedSize(20, 20);
	//btnColor3->setFlat(true);
	btnColor3->setStyleSheet("background-color:rgb(196, 218, 250)");

	ui.statusBar->addPermanentWidget(btnColor1);
	ui.statusBar->addPermanentWidget(btnColor2);
	ui.statusBar->addPermanentWidget(btnColor3);

	connect(btnColor1, &QPushButton::clicked, this, &BDLS::setColor1);
	connect(btnColor2, &QPushButton::clicked, this, &BDLS::setColor2);
	connect(btnColor3, &QPushButton::clicked, this, &BDLS::setColor3);

	media_file_format.append("mp4");
	media_file_format.append("mov");
	media_file_format.append("wmv");
	media_file_format.append("avi");
	media_file_format.append("avchd");
	media_file_format.append("mpg");
	media_file_format.append("mpeg");

	proxyModel = new MySortFilterProxyModel(this);
	originModel = new QStandardItemModel(this);
	proxyModel->setSourceModel(originModel);

	ui.tableView->m_pView = this;
	ui.tableView->setModel(proxyModel);
	ui.tableView->setAlternatingRowColors(true);
	ui.tableView->setSortingEnabled(true);

	connect(ui.tableView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(onTableCellClicked(const QItemSelection&, const QItemSelection&)));
	connect(ui.tableView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onTableDoubleClicked(const QModelIndex&)));
	connect(ui.tableView->filterHeader(), &FilterTableHeader::filterChanged, this, &BDLS::updateFilter);
	//connect(ui.tableView->filterHeader(), &FilterTableHeader::addCondFormat, this, &TableBrowser::addCondFormatFromFilter);
	//connect(ui.tableView->filterHeader(), &FilterTableHeader::allCondFormatsCleared, this, &TableBrowser::clearAllCondFormats);
	//connect(ui.tableView->filterHeader(), &FilterTableHeader::condFormatsEdited, this, &TableBrowser::editCondFormats);
	//connect(ui.tableView, &ExtendedTableWidget::editCondFormats, this, &TableBrowser::editCondFormats);
	//connect(ui.tableView, &ExtendedTableWidget::dataAboutToBeEdited, this, &TableBrowser::dataAboutToBeEdited);

	//connect(ui.tableView, &ExtendedTableWidget::doubleClicked, this, &TableBrowser::selectionChangedByDoubleClick);
	//connect(ui.tableView->filterHeader(), &FilterTableHeader::sectionClicked, this, &TableBrowser::headerClicked);
	//connect(ui.tableView->filterHeader(), &QHeaderView::sectionDoubleClicked, ui.tableView, &QTableView::selectColumn);
	//connect(ui.tableView->verticalScrollBar(), &QScrollBar::valueChanged, this, &TableBrowser::updateRecordsetLabel);
	//connect(ui.tableView->horizontalHeader(), &QHeaderView::sectionResized, this, &TableBrowser::updateRecordsetLabel);
	//connect(ui.tableView->verticalHeader(), &QHeaderView::sectionResized, this, &TableBrowser::updateRecordsetLabel);
	//connect(ui.tableView->horizontalHeader(), &QHeaderView::sectionResized, this, &TableBrowser::updateColumnWidth);
	//connect(ui.tableView->horizontalHeader(), &QHeaderView::customContextMenuRequested, this, &TableBrowser::showDataColumnPopupMenu);
	//connect(ui.tableView->verticalHeader(), &QHeaderView::customContextMenuRequested, this, &TableBrowser::showRecordPopupMenu);
	//connect(ui.tableView, &ExtendedTableWidget::openFileFromDropEvent, this, &TableBrowser::requestFileOpen);
	//connect(ui.tableView, &ExtendedTableWidget::selectedRowsToBeDeleted, this, &TableBrowser::deleteRecord);

	createDockWindows();
	createActions();

	_widgetProgress = new widgetProgress(this);
	_widgetProgress->hide();

	//QMediaPlayer* player = new QMediaPlayer;
	//player->setVideoOutput(ui.pdfView);

	//ui.pdfView->show();

	//player->setMedia(QUrl::fromLocalFile("E:\\Library\\opencv-3.4.2\\sources\\samples\\data\\vtest.avi"));
	//player->play();

	QString m_strExcelTempFile = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
	m_strExcelTempFile += "/backup.xlsx";

	QString file_path = m.value("CURRENT_PATH").toString();
	if (QFile::exists(file_path))
	{
		m_strDBfilepath = file_path;

		_widgetLeftView->SetCurrentFile(file_path);
	}

	QString auto_save_time = m.value("AUTO_SAVE_TIME").toString();
	bool ok;
	int auto_save_time_i = auto_save_time.toInt(&ok);
	if (!ok)
		auto_save_time_i = 0;
	m_saveTimer = new QTimer(this);
	connect(m_saveTimer, SIGNAL(timeout()), this, SLOT(DoAutoSave()));
	if (auto_save_time_i > 0)
		m_saveTimer->start(auto_save_time_i * 1000);

	QString auto_save = m.value("AUTO_SAVE").toString();
	m_bAutoSave = (auto_save == "T") ? true : false;

	readSettings();
}

void BDLS::DoAutoSave()
{
}

void BDLS::createDockWindows()
{
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

	dockBottom = new QDockWidget(QString::fromLocal8Bit("검색결과"), this);
	_widgetBottomView = new widgetBottomView(dockBottom);
	dockBottom->setWidget(_widgetBottomView);
	addDockWidget(Qt::BottomDockWidgetArea, dockBottom);
	_widgetBottomView->m_pView = this;

	dockLeft = new QDockWidget(QString::fromLocal8Bit("관리"), this);
	dockLeft->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	_widgetLeftView = new widgetLeftView(dockLeft);
	dockLeft->setWidget(_widgetLeftView);
	addDockWidget(Qt::LeftDockWidgetArea, dockLeft);
	//viewMenu->addAction(dock->toggleViewAction());
	_widgetLeftView->m_pView = this;

	dockRight = new QDockWidget(QString::fromLocal8Bit("미리보기"), this);
	_widgetRightView = new widgetRightView(dockRight);
	dockRight->setWidget(_widgetRightView);
	addDockWidget(Qt::RightDockWidgetArea, dockRight);
	//viewMenu->addAction(dock->toggleViewAction());
	_widgetRightView->m_pView = this;
}

void BDLS::SelectFileFromTree(QString file_path)
{
	m_strCurrentSelectedItemPath = file_path;
	//if (m_bIsLogin)
	//{
		QFileInfo f_info(file_path);
		QString ext = f_info.suffix().toLower();

		if (ext == "pdf")
		{
			m_iCurrentSelectedItemType = 2;
			//  pdf view
			_widgetRightView->ViewPDF(file_path);
		}
		else if (ext == "xls" || ext == "xlsx")
		{
			OnOpenSingle();
		}
		else if (ext == "db3")
		{
			char strUtf8[512] = { 0, };
			m_strDBfilepath = file_path;
			m_strCurrentFolderPath = f_info.absolutePath();
			m.setValue("QSettings", file_path);
			InitFromDB();
		}
		else if (media_file_format.contains(ext))
		{
			m_iCurrentSelectedItemType = 3;
			_widgetRightView->ViewMovie(file_path);
		}
		else if (ext == "txt")
		{
			if (f_info.fileName() == "old_db.txt")
			{
				LoadOldDB(file_path);
			}
		}
		else
		{
			m_iCurrentSelectedItemType = 4;
			m_strCurrentFolderPath = file_path;
		}
	//}
}

void BDLS::LoadOldDB(QString file_path)
{
	//QProcess::execute("iconv", QStringList() << "-c" << "-f" << "euc-kr" << "-t" << "utf-8" << file_path << ">" << "old_db_utf.txt");

	QFile file(file_path);
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, "error", file.errorString());
		return;
	}
	QTextStream in(&file);
	int status = 0;
	QStringList header_list;
	QStringList temp_list;
	QList<QStringList> index_info;
	QMap<QString, QList<QStringList>> page_info;
	int col_size = 0;
	header_list.append("No");
	while (!in.atEnd())
	{
		QString line = in.readLine();
		if (line == "[headers]")
		{
			status = 1;
		}
		else if (line == "[index_info]")
		{
			status = 2;
		}
		else if (line == "[page_info]")
		{
			status = 4;
		}
		else
		{
			switch (status)
			{
			case 1:
			{
				QStringList fields = line.split(",");
				header_list.append(fields[1]);
			}
			break;
			case 2:
			{
				col_size = line.toInt();
				status = 3;
				QStringList new_list;
				index_info.append(new_list);
			}
			break;
			case 3:
			{
				index_info[index_info.count() - 1].append(line);
				col_size--;
				if (col_size == 0)
				{
					status = 2;
				}
			}
			break;
			case 4:
			{
				col_size = line.toInt();
				status = 5;
				temp_list.clear();
			}
			break;
			case 5:
			{
				temp_list.append(line);
				col_size--;
				if (col_size == 0)
				{
					page_info[temp_list[1]].append(temp_list);
					status = 4;
				}
			}
			break;
			}
		}
	}

	QString temp_string;
	bool db_file_exist = false;
	QString str_file_path = m_strCurrentFolderPath + "\\index2.db3";
	if (QFile::exists(str_file_path))
	{
		db_file_exist = true;
		QMessageBox::StandardButton reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("DB 파일이 존재합니다. 새로 저장하시겠습니까?"), QMessageBox::Yes | QMessageBox::No);
		if (reply != QMessageBox::Yes)
		{
			return;
		}
	}

	m_strDBfilepath = str_file_path;

	BeginProgress();
	int col_count = header_list.count();
	int file_name_index = col_count - 1;
	int row_count = index_info.count();
	int total = row_count;
	QString status_string;
	if (InitDB(m_strDBfilepath))
	{
		if (!db_file_exist)
		{
			db->exec("DROP TABLE IF EXISTS headers");
			db->exec("CREATE TABLE headers (id INTEGER PRIMARY KEY, value TEXT)");
			for (int j = 3; j < col_count; j++)
			{
				temp_string = QString("INSERT INTO headers VALUES (NULL, \"%1\")").arg(header_list[j]);
				//temp_string = m_Grid.QuickGetText(j, -1);
				//sprintf_s(input_query, "INSERT INTO headers VALUES (NULL, \"%s\")", temp_string);
				db->exec(temp_string);
			}
			db->exec("CREATE TABLE file_info (id INTEGER PRIMARY KEY, file_name TEXT, file_path TEXT, m_no TEXT)");
			db->exec("CREATE TABLE header_info (file_id INTEGER, header_id INTEGER, value TEXT, PRIMARY KEY(file_id, header_id))");
			db->exec("CREATE TABLE page_info (id INTEGER PRIMARY KEY, file_id INTEGER, page_no INTEGER, block_no INTEGER, block_text TEXT)");
			db->exec("CREATE TABLE hsah_tags (id INTEGER PRIMARY KEY, tags TEXT)");
			db->exec("CREATE TABLE file_to_hash (id INTEGER PRIMARY KEY, file_id INTEGER, tag_id INTEGER)");
			db->exec("CREATE TABLE reply_info (id INTEGER PRIMARY KEY, file_id INTEGER, parent_id INTEGER, user_id TEXT, value TEXT, date_time TEXT)");
			db->exec("CREATE TABLE play_info (id INTEGER PRIMARY KEY, file_id INTEGER, s_time INTEGER, s_title TEXT)");
			db->exec("CREATE TABLE user_info (id INTEGER PRIMARY KEY, user_id TEXT, user_pass TEXT, user_name TEXT, read_only INTEGER)");
			db->exec("CREATE TABLE user_file_info (id INTEGER PRIMARY KEY, user_id TEXT, file_id INTEGER)");
			db->exec("CREATE TABLE log_info (id INTEGER PRIMARY KEY, log_type TEXT, log_content TEXT, date_time TEXT)");
		}
		else
		{
			QStringList table_list = db->tables();
			if (!table_list.contains("file_info"))
			{
				db->exec("CREATE TABLE file_info (id INTEGER PRIMARY KEY, file_name TEXT, file_path TEXT, m_no TEXT)");
			}
			if (!table_list.contains("header_info"))
			{
				db->exec("CREATE TABLE header_info (file_id INTEGER, header_id INTEGER, value TEXT, PRIMARY KEY(file_id, header_id))");
			}
			if (!table_list.contains("page_info"))
			{
				db->exec("CREATE TABLE page_info (id INTEGER PRIMARY KEY, file_id INTEGER, page_no INTEGER, block_no INTEGER, block_text TEXT)");
			}
			if (!table_list.contains("hsah_tags"))
			{
				db->exec("CREATE TABLE hsah_tags (id INTEGER PRIMARY KEY, tags TEXT)");
			}
			if (!table_list.contains("file_to_hash"))
			{
				db->exec("CREATE TABLE file_to_hash (id INTEGER PRIMARY KEY, file_id INTEGER, tag_id INTEGER)");
			}
			if (!table_list.contains("reply_info"))
			{
				db->exec("CREATE TABLE reply_info (id INTEGER PRIMARY KEY, file_id INTEGER, parent_id INTEGER, user_id TEXT, value TEXT, date_time TEXT)");
			}
			if (!table_list.contains("play_info"))
			{
				db->exec("CREATE TABLE play_info (id INTEGER PRIMARY KEY, file_id INTEGER, s_time INTEGER, s_title TEXT)");
			}
			if (!table_list.contains("user_info"))
			{
				db->exec("CREATE TABLE user_info (id INTEGER PRIMARY KEY, user_id TEXT, user_pass TEXT, user_name TEXT, read_only INTEGER)");
			}
			if (!table_list.contains("user_file_info"))
			{
				db->exec("CREATE TABLE user_file_info (id INTEGER PRIMARY KEY, user_id TEXT, file_id INTEGER)");
			}
			if (!table_list.contains("log_info"))
			{
				db->exec("CREATE TABLE log_info (id INTEGER PRIMARY KEY, log_type TEXT, log_content TEXT, date_time TEXT)");
			}
		}
		//CreateDirectory(m_strCurrentFolderPath + "\\pdf_txt", NULL);

		QString managed_file_no("");

		QVariantList data;
		db->exec("SELECT max(m_no) FROM file_info", data);
		if (data.count() > 0)
		{
			//	존재할 경우
			auto map = data[0].toMap();
			if (!map["m_no"].isNull())
				managed_file_no = map["m_no"].toString();
		}

		for (int i = 0; i < row_count; i++)
		{
			QString file_name = index_info[i][file_name_index];
			QString file_name_only = file_name;
			file_name_only.chop(4);

			QString file_path = m_strDBfolderpath + "\\" + file_name;
			QString target_file_path = m_strDBfolderpath + "\\" + file_name_only + ".txt";

			QString cell_string = ("");
			QString cell_string1 = ("");
			//if (IsPDF(file_path))
			//{
			//	cell_string = "O";
			//	if (CheckEncrypted(file_path))
			//	{
			//		cell_string1 = "V";
			//	}
			//	m_lstGridText[i][2] = cell_string;
			//	m_lstGridText[i][1] = cell_string1;
			//	if (m_lstGridIndex[i] > -1)
			//	{
			//		m_Grid.QuickSetText(2, m_lstGridIndex[i], cell_string);
			//		m_Grid.QuickSetText(1, m_lstGridIndex[i], cell_string1);
			//	}
			//}

			status_string = QString::fromLocal8Bit("%1 행 저장 중").arg(i + 1);
			UpdateProgress(status_string, i + 1, total);

			int file_db_id = 0;
			//	file id 확인
			db->exec(QString("SELECT id FROM file_info WHERE file_path=\"%1\"").arg(file_path), data);
			if (data.count() > 0)
			{
				//	존재할 경우
				auto map = data[0].toMap();
				file_db_id = map["id"].toInt();
				for (int j = 3; j < col_count; j++)
				{
					QString header_name = index_info[i][j];
					temp_string = QString("UPDATE header_info SET value=\"%3\" WHERE file_id=%1 AND header_id=%2").arg(file_db_id).arg(j - 2).arg(header_name);
					db->exec(temp_string);
				}
			}
			else
			{
				//	존재하지 않을 경우
				//	insert file_info
				managed_file_no = NextFileMNO(managed_file_no);
				temp_string = QString("INSERT INTO file_info VALUES (NULL, \"%1\", \"%2\", \"%3\")").arg(file_name).arg(file_path).arg(managed_file_no);
				db->exec(temp_string);

				//	file id 확인
				db->exec(QString("SELECT id FROM file_info WHERE file_path=\"%1\"").arg(file_path), data);
				if (data.count() > 0)
				{
					//	존재할 경우
					auto map = data[0].toMap();
					file_db_id = map["id"].toInt();

					for (int j = 3; j < col_count; j++)
					{
						QString header_name = index_info[i][j];
						temp_string = QString("INSERT INTO header_info VALUES (%1, %2, \"%3\")").arg(file_db_id).arg(j - 2).arg(header_name);
						db->exec(temp_string);
					}
				}
				else
				{
					//	저장이 잘 안됐나?
				}
			}

			//	file id 확인
			db->exec(QString("SELECT page_no FROM page_info WHERE file_id=%1").arg(file_db_id), data);
			if (data.count() > 0)
			{
				//	존재할 경우
			}
			else
			{
				if (page_info.contains(file_name))
				{
					int block_count = page_info[file_name].count();
					for (int j = 0; j < block_count; j++)
					{
						status_string = QString("page[%1] block[%2s] 저장 중").arg(page_info[file_name][j][2]).arg(page_info[file_name][j][3]);
						UpdateProgress2(status_string, j + 1, block_count);

						temp_string = QString("INSERT INTO page_info VALUES (NULL, %1, %2, %3, \"%4\")")
							.arg(file_db_id)
							.arg(page_info[file_name][j][2])
							.arg(page_info[file_name][j][3])
							.arg(page_info[file_name][j][4]);
						db->exec(temp_string);
					}
				}
			}
		}
	}
	EndProgress();
}

bool BDLS::InitDB(QString db_file_path)
{
	if (db == NULL)
	{
		db = new db_manager(db_file_path);
	}
	QFileInfo f_info(db_file_path);
	m_strDBfolderpath = f_info.absolutePath();

	return db->Connect(db_file_path);
}

bool BDLS::DBConnected()
{
	if (db == NULL)
		return false;

	return db->Connected();
}

void BDLS::CloseDB()
{
	if (DBConnected())
	{
		db->Close();
	}
	m_strDBfilepath = "";
}

void BDLS::InitFromDB()
{
	QString temp_string;
	try
	{
		if (QFile::exists(m_strDBfilepath))
		{
			if (InitDB(m_strDBfilepath))
			{
				QStringList table_list = db->tables();
				if (!table_list.contains("file_info"))
				{
					db->exec("CREATE TABLE file_info (id INTEGER PRIMARY KEY, file_name TEXT, file_path TEXT, m_no TEXT)");
				}
				if (!table_list.contains("header_info"))
				{
					db->exec("CREATE TABLE header_info (file_id INTEGER, header_id INTEGER, value TEXT, PRIMARY KEY(file_id, header_id))");
				}
				if (!table_list.contains("page_info"))
				{
					db->exec("CREATE TABLE page_info (id INTEGER PRIMARY KEY, file_id INTEGER, page_no INTEGER, block_no INTEGER, block_text TEXT)");
				}
				if (!table_list.contains("hsah_tags"))
				{
					db->exec("CREATE TABLE hsah_tags (id INTEGER PRIMARY KEY, tags TEXT)");
				}
				if (!table_list.contains("file_to_hash"))
				{
					db->exec("CREATE TABLE file_to_hash (id INTEGER PRIMARY KEY, file_id INTEGER, tag_id INTEGER)");
				}
				if (!table_list.contains("reply_info"))
				{
					db->exec("CREATE TABLE reply_info (id INTEGER PRIMARY KEY, file_id INTEGER, parent_id INTEGER, user_id TEXT, value TEXT, date_time TEXT)");
				}
				if (!table_list.contains("play_info"))
				{
					db->exec("CREATE TABLE play_info (id INTEGER PRIMARY KEY, file_id INTEGER, s_time INTEGER, s_title TEXT)");
				}
				if (!table_list.contains("user_info"))
				{
					db->exec("CREATE TABLE user_info (id INTEGER PRIMARY KEY, user_id TEXT, user_pass TEXT, user_name TEXT, read_only INTEGER)");
				}
				if (!table_list.contains("user_file_info"))
				{
					db->exec("CREATE TABLE user_file_info (id INTEGER PRIMARY KEY, user_id TEXT, file_id INTEGER)");
				}
				if (!table_list.contains("log_info"))
				{
					db->exec("CREATE TABLE log_info (id INTEGER PRIMARY KEY, log_type TEXT, log_content TEXT, date_time TEXT)");
				}


				if (m_bIsLogin)
				{
					QStringList table_list = db->tables();
					if (table_list.contains("headers"))
					{
						ClearTable();

						// Compile a SQL query, containing one parameter (index 1)
						QVariantList data;
						db->exec("SELECT id, value FROM headers ORDER BY id", data);
						for (const auto& item : data)
						{
							auto map = item.toMap();
							//map["id"].toInt();
							title_list.append(map["value"].toString());
							map_title_to_index[map["value"].toString()] = map["id"].toInt();
						}

						if (title_list.size() > 0)
						{
							m_iCurrentSelectedItemType = 1;
							int row = 1;
							int col_size = title_list.size() + 5;	//	no, ?, !, 검색결과, 파일경로
							QString no;

							originModel->insertColumn(0);
							originModel->setHeaderData(0, Qt::Horizontal, "No");
							originModel->insertColumn(1);
							originModel->setHeaderData(1, Qt::Horizontal, "?");
							originModel->insertColumn(2);
							originModel->setHeaderData(2, Qt::Horizontal, "!");
							for (int i = 0; i < title_list.size(); i++)
							{
								originModel->insertColumn(i + 3);
								originModel->setHeaderData(i + 3, Qt::Horizontal, title_list[i]);
							}
							originModel->insertColumn(col_size - 2);
							originModel->setHeaderData(col_size - 2, Qt::Horizontal, QString::fromLocal8Bit("검색 결과"));

							//if (m_bIsAdmin)
							{
								originModel->insertColumn(col_size - 1);
								originModel->setHeaderData(col_size - 1, Qt::Horizontal, QString::fromLocal8Bit("파일 경로"));
							}

							if (m_UserLevel == ADMIN)
							{
								db->exec("SELECT id, file_name, file_path FROM file_info ORDER BY id", data);
							}
							else
							{
								QString query = QString("SELECT file_info.id, file_info.file_name, file_info.file_path FROM file_info INNER JOIN user_file_info on file_info.id = user_file_info.file_id WHERE user_file_info.user_id = \"%1\" ORDER BY file_info.id").arg(m_loginUserID);
								db->exec(query, data);
							}
							QStringList file_name_list;
							QStringList file_path_list;
							QList<int> file_id_list;
							for (const auto& item : data)
							{
								auto map = item.toMap();
								//map["id"].toInt();
								int file_id = map["id"].toInt();
								QString file_name = map["file_name"].toString();
								QString file_path = map["file_path"].toString();
								file_id_list.append(file_id);
								file_name_list.append(file_name);
								file_path_list.append(file_path);
								map_file_to_id[file_name] = file_id;
							}

							for (int i = 0; i < file_id_list.count(); i++)
							{
								originModel->insertRow(i);
								originModel->setData(originModel->index(i, 0), i + 1);
								originModel->setData(originModel->index(i, 0), file_id_list[i], Qt::AccessibleTextRole);

								db->exec(QString("SELECT file_id, header_id, value FROM header_info WHERE file_id=%1").arg(file_id_list[i]), data);
								for (const auto& item : data)
								{
									auto map = item.toMap();
									//map["id"].toInt();
									int header_id = map["header_id"].toInt();
									QString value = map["value"].toString();

									originModel->setData(originModel->index(i, header_id + 2), value);
								}
								originModel->setData(originModel->index(i, col_size - 1), file_name_list[i]);
							}

						}
						proxyModel->invalidate();
						for (int i = 0; i < proxyModel->columnCount(); ++i)
							ui.tableView->resizeColumnToContents(i);

						generateFilters();
						setSearchCombo();
						setTagList();
						_widgetLeftView->clearAll();
					}
					else
					{
					}
				}
			}
		}
	}
	catch (std::exception& e)
	{
		//std::cout << "SQLite exception: " << e.what() << std::endl;
		//temp_string.Format(_T("db exception : %S"), e.what());
		//AddOutput(_T("error"), temp_string, 0, 0);
	}
}

//void BDLS::SetItemData(int row, int col, QString value, QColor back_color, int span)
//{
//	ui.treeView->setSpan(row, col, 1, span);
//	Qui.treeViewItem* item = new Qui.treeViewItem();
//	item->setData(Qt::DisplayRole, value);
//	item->setTextAlignment(Qt::AlignCenter);
//	ui.treeView->setItem(row, col, item);
//
//	qDebug() << row << " , " << col << " , " << value << "\n";
//}
//void BDLS::SetItemData(int row, int col, int value, QColor back_color, int span)
//{
//	ui.treeView->setSpan(row, col, 1, span);
//	Qui.treeViewItem* item = new Qui.treeViewItem();
//	item->setData(Qt::DisplayRole, value);
//	item->setTextAlignment(Qt::AlignCenter);
//	ui.treeView->setItem(row, col, item);
//	qDebug() << row << " , " << col << " , " << value << "\n";
//}

void BDLS::ClearTable()
{
	int row_size = originModel->rowCount();
	if (row_size > 0)
	{
		originModel->removeRows(0, row_size);
	}
	int col_size = originModel->columnCount();
	if (col_size > 0)
	{
		originModel->removeColumns(0, col_size);
	}
	map_title_to_index.clear();
	title_list.clear();
	map_file_to_id.clear();
	m_iCurrentFileDBID = 0;
}

void BDLS::setSearchCombo()
{
	_widgetLeftView->setSearchCombo(title_list, map_title_to_index);
}

void BDLS::setTagList()
{
	_widgetLeftView->setTagList();
}

void BDLS::OnOpenSingle()
{
	if (m_UserLevel == ADMIN)
	{
		QFileInfo f_info(m_strCurrentSelectedItemPath);
		QString ext = f_info.suffix().toLower();
		QString folder_path = f_info.absolutePath();
		QString file_name = f_info.fileName();

		QStringList excel_file_list;
		//vector< int > grid_width;

		if (ext == "xls" || ext == "xlsx")
		{
			int data_row_count = originModel->rowCount();
			if (DBConnected() && data_row_count > 0)
			{
				//	db를 읽은 상태임
				QMessageBox::StandardButton reply;
				reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("현재 테이블에 추가하시겠습니까? [아니오]를 선택하시면 엑셀을 새로 로딩합니다."),
					QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
				if (reply == QMessageBox::Yes)
				{
					//	추가로 로딩
					if (m_strDBfolderpath != folder_path)
					{
						reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("현재 DB파일과 다른 폴더에 있는 엑셀파일입니다. 신규 파일 링크가 변경될 수 있습니다.계속 진행하시겠습니까 ? "), QMessageBox::Yes | QMessageBox::No);
						if (reply != QMessageBox::Yes)
						{
							//	폴더가 달라서 취소
							return;
						}
						else
						{
							//	다른 폴더 열었을 때 링크 맞추기
						}
					}
					//	추가로 읽기
					m_strCurrentExcelPath = m_strCurrentSelectedItemPath;

					m_iCurrentSelectedItemType = 1;

					char strUtf8[512] = { 0, };
					int row = 1;
					int col_size = 3;
					QString no;
					int grid_col_count = originModel->columnCount();
					int grid_row_count = originModel->rowCount();
					//try {
					QXlsx::Document xlsx(m_strCurrentExcelPath);
					if (xlsx.load())
					{
						QList<int> new_col_index;
						QString title_string;
						bool total_check_title = true;
						QXlsx::Cell* cell = xlsx.cellAt(row, col_size - 2);
						while (cell != NULL && cell->value().toString() != "")
						{
							cell = xlsx.cellAt(1, col_size - 2);
							QString cell_string = cell->value().toString();

							title_string = originModel->headerData(col_size, Qt::Horizontal).toString();
							if (title_string == cell_string)
							{
								new_col_index.push_back(col_size);
							}
							else
							{
								bool check_title = false;
								for (int col_index = 3; col_index < grid_col_count; col_index++)
								{
									if (cell_string == originModel->headerData(col_index, Qt::Horizontal).toString())
									{
										new_col_index.push_back(col_index);
										check_title = true;
										break;
									}
								}

								if (check_title == false)
								{
									total_check_title = false;
									new_col_index.push_back(-1);
								}
							}
							col_size++;
							cell = xlsx.cellAt(row, col_size - 2);
						}

						if (total_check_title == false)
						{
							reply = QMessageBox::question(this,
								QString::fromLocal8Bit("확인"),
								QString::fromLocal8Bit("동일하지 않은 항목이 존재합니다. 기존 항목과 동일하지 않은 항목은 무시됩니다. 계속 진행하시겠습니까?"),
								QMessageBox::Yes | QMessageBox::No);
							if (reply != QMessageBox::Yes)
							{
								//	폴더가 달라서 취소
								return;
							}
						}

						//col_size = m_lstGridText[0].size();

						row++;
						grid_row_count++;
						data_row_count++;
						cell = xlsx.cellAt(row, 1);
						while (cell != NULL && cell->value().toString() != "")
						{
							originModel->insertRow(0);
							//m_lstGridText.resize(data_row_count);
							//m_lstGridText[data_row_count - 1].resize(col_size);
							//m_lstGridShow.resize(data_row_count);
							//m_lstGridShow[data_row_count - 1].resize(col_size, true);
							//m_lstGridIndex.resize(data_row_count);
							//m_lstGridSelected.resize(data_row_count);
							//m_lstGridKey.resize(data_row_count);

							//no = QString::number(data_row_count);

							originModel->setData(originModel->index(0, 0), data_row_count);
							//SetItemData(grid_row_count - 1, 0, no);
							//m_lstGridText[data_row_count - 1][0] = no;
							//m_lstGridIndex[data_row_count - 1] = grid_row_count - 1;
							//m_lstGridKey[data_row_count - 1] = -1;

							for (int i = 3; i < col_size - 1; i++)
							{
								cell = xlsx.cellAt(row, i - 2);
								if (cell != NULL)
								{
									if (new_col_index[i - 3] > -1)
									{
										QString cell_string = cell->value().toString();
										originModel->setData(originModel->index(0, new_col_index[i - 3]), cell_string);
										//m_lstGridText[data_row_count - 1][new_col_index[i - 3]] = cell_string;
									}
								}
							}

							cell = xlsx.cellAt(row, 26);
							QString cell_string;
							if (cell != NULL)
							{
								cell_string = cell->value().toString();
							}
							//if (m_bIsAdmin)
							//{
								originModel->setData(originModel->index(0, col_size - 1), cell_string);
							//}
							//m_lstGridText[data_row_count - 1][col_size - 1] = cell_string;

							QString pdf_file_path = folder_path + "\\" + cell_string;
							cell_string = "";
							QString cell_string1 = "";
							//if (IsPDF(pdf_file_path))
							//{
							//	cell_string = "O";
							//	if (CheckEncrypted(pdf_file_path))
							//	{
							//		cell_string1 = "V";
							//	}
							//}
							//m_lstGridText[data_row_count - 1][2] = cell_string;
							originModel->setData(originModel->index(0, 2), cell_string);
							//m_Grid.QuickSetAlignment(2, grid_row_count - 1, UG_ALIGNCENTER);

							originModel->setData(originModel->index(0, 1), cell_string1);
							//m_lstGridText[data_row_count - 1][1] = cell_string1;
							//m_Grid.QuickSetAlignment(1, grid_row_count - 1, UG_ALIGNCENTER);

							//QString exist_file_path = GetExistingFilePath(folder_path, m_Grid.QuickGetText(2, row - 2), m_Grid.QuickGetText(1, row - 2));
							////	파일 경로
							//m_Grid.QuickSetText(col_size - 1, row - 2, exist_file_path);
							//m_lstGridText[row - 2][col_size - 1] = exist_file_path;
							row++;
							grid_row_count++;
							data_row_count++;
						}
					}
					//}
					//catch (exception const& e) {
					//	AfxMessageBox(QString(e.what()));
					//}
					//m_Grid.SetPaintMode(TRUE);
					//if (is_fitGrid)
					//{
					//	int col_no = m_Grid.GetNumberCols();
					//	for (int i = 0; i < col_no && i < grid_width.size(); i++)
					//	{
					//		m_Grid.SetColWidth(i, grid_width[i]);
					//	}
					//}
					//FitGrid();
					return;
				}
				else if (reply == QMessageBox::Cancel)
				{
					return;
				}
			}

			//	신규로 읽기
			m_strCurrentExcelPath = m_strCurrentSelectedItemPath;
			m_strCurrentFolderPath = folder_path;
			//	통합 파일이면 열기
			//if (file_name.Find("통합") > -1)
			//{
			//	is_total_mode = true;
			//}
			//else
			//{
			//	is_total_mode = false;
			//}

			m_iCurrentSelectedItemType = 1;

			//StopLoadingThread();
			//m_lstGridText.clear();
			//m_lstGridIndex.clear();
			//m_lstGridSelected.clear();
			//m_lstGridKey.clear();
			CloseDB();
			ClearTable();
			//m_Grid.SetPaintMode(FALSE);
			//if (is_fitGrid)
			//{
			//	int col_no = m_Grid.GetNumberCols();
			//	for (int i = 0; i < col_no; i++)
			//	{
			//		grid_width.push_back(m_Grid.GetColWidth(i));
			//	}
			//}
			int row = 1;
			int col_size = 3;
			QString no;
			QXlsx::Document xlsx(m_strCurrentExcelPath);
			if (xlsx.load())
			{
				QStringList header_label;
				header_label << "No" << "?" << "!";
				originModel->insertColumn(0);
				originModel->insertColumn(0);
				originModel->insertColumn(0);
				//SetItemData(row - 2, 1, "?");
				//SetItemData(row - 2, 2, "!");

				QXlsx::Cell* cell = xlsx.cellAt(row, col_size - 2);
				while (cell != NULL && cell->value().toString() != "")
				{
					//ui.treeView->setColumnCount(col_size + 1);
					//m_Grid.SetNumberCols(col_size + 1);
					header_label << cell->value().toString();
					originModel->insertColumn(0);
					//SetItemData(row - 2, col_size, cell->value().toString());
					col_size++;
					cell = xlsx.cellAt(row, col_size - 2);
				}
				header_label << QString::fromLocal8Bit("검색 결과");
				originModel->insertColumn(0);
				//ui.treeView->setColumnCount(col_size + 1);
				//SetItemData(row - 2, col_size, QString("검색 결과"));
				col_size++;

				//if (m_bIsAdmin)
				//{
					//ui.treeView->setColumnCount(col_size + 1);
				header_label << QString::fromLocal8Bit("파일 경로");
				//SetItemData(row - 2, col_size, QString("파일 경로"));
			//}
				originModel->insertColumn(0);
				col_size++;

				for (int i = 0; i < col_size; i++)
				{
					originModel->setHeaderData(i, Qt::Horizontal, header_label[i]);
				}

				//m_lstFilter.resize(col_size);

				row++;
				cell = xlsx.cellAt(row, 1);
				int row_index = 0;
				while (cell != NULL && cell->value().toString() != "")
				{
					originModel->insertRow(row_index);
					//ui.treeView->setRowCount(row - 1);
					//m_lstGridText.resize(row - 1);
					//m_lstGridText[row - 2].resize(col_size);
					//m_lstGridShow.resize(row - 1);
					//m_lstGridShow[row - 2].resize(col_size, true);
					//m_lstGridIndex.resize(row - 1);
					//m_lstGridSelected.resize(row - 1);
					//m_lstGridKey.resize(row - 1);
					//SetItemData(row - 2, 0, row - 1);
					originModel->setData(originModel->index(row_index, 0), row - 1);
					//m_lstGridText[row - 2][0] = no;
					//m_lstGridIndex[row - 2] = row - 2;
					//m_lstGridKey[row - 2] = -1;

					for (int i = 3; i < col_size - 2; i++)
					{
						cell = xlsx.cellAt(row, i - 2);
						if (cell != NULL)
						{
							//SetItemData(row - 2, i, cell->value().toString());
							originModel->setData(originModel->index(row_index, i), cell->value().toString());
							//m_lstGridText[row - 2][i] = cell_string;
						}
					}
					cell = xlsx.cellAt(row, 26);
					QString cell_string;
					if (cell != NULL)
					{
						cell_string = cell->value().toString();
					}
					//if (m_bIsAdmin)
					//{
						//SetItemData(row - 2, col_size - 1, cell_string);
					originModel->setData(originModel->index(row_index, col_size - 1), cell_string);
					//}
					//m_lstGridText[row - 2][col_size - 1] = cell_string;

					QString pdf_file_path = folder_path + "\\" + cell_string;
					cell_string = "";
					QString cell_string1 = "";
					//if (IsPDF(pdf_file_path))
					//{
					//	cell_string = "O";
					//	if (CheckEncrypted(pdf_file_path))
					//	{
					//		cell_string1 = "V";
					//	}
					//}
					//m_lstGridText[row - 2][2] = cell_string;
					//SetItemData(row - 2, 2, cell_string);
					//SetItemData(row - 2, 1, cell_string1);
					originModel->setData(originModel->index(row_index, 2), cell_string);
					originModel->setData(originModel->index(row_index, 1), cell_string1);
					//QString exist_file_path = GetExistingFilePath(folder_path, m_Grid.QuickGetText(2, row - 2), m_Grid.QuickGetText(1, row - 2));
					////	파일 경로
					//m_Grid.QuickSetText(col_size - 1, row - 2, exist_file_path);
					//m_lstGridText[row - 2][col_size - 1] = exist_file_path;
					row++;
					row_index++;
					cell = xlsx.cellAt(row, 1);
				}
			}

			proxyModel->invalidate();
			for (int i = 0; i < proxyModel->columnCount(); ++i)
				ui.tableView->resizeColumnToContents(i);
			generateFilters();
			//m_Grid.SetPaintMode(TRUE);
			//if (is_fitGrid)
			//{
			//	int col_no = m_Grid.GetNumberCols();
			//	for (int i = 0; i < col_no && i < grid_width.size(); i++)
			//	{
			//		m_Grid.SetColWidth(i, grid_width[i]);
			//	}
			//}
			//FitGrid();

		}
	}
}

void BDLS::SetCurrentFile(SEARCH_TYPE search_type, QString file_name, QString file_info1, QString file_info2, QString file_info3)
{
	QString file_path = m_strCurrentFolderPath + "\\" + file_name;
	if(DBConnected())
		file_path = m_strDBfolderpath + "\\" + file_name;
	m_iCurrentFileDBID = map_file_to_id[file_name];
	_widgetLeftView->UpdateMemo(search_type, file_info1, file_info2, file_info3);
	if (IsPDF(file_path))
	{
		m_strCurrentSelectedItemPath = file_path;
		m_iCurrentSelectedItemType = 2;
		_widgetRightView->ViewPDF(file_path, file_info1);
		//m_pFrame->m_wndProperties.DoPreview(file_path, 1, m_bViewThumbInPreview);
	}
	else if (IsMV(file_path))
	{
		m_strCurrentSelectedItemPath = file_path;
		m_iCurrentSelectedItemType = 3;
		_widgetRightView->ViewMovie(file_path, file_info1);
	}
}

void BDLS::onTableDoubleClicked(const QModelIndex& index)
{
	if (index.column() == 0)
	{
		int col_size = proxyModel->columnCount();
		QString file_name = proxyModel->data(proxyModel->index(index.row(), col_size - 1)).toString();
		QString file_path = m_strCurrentFolderPath + "\\" + file_name;
		if (DBConnected())
			file_path = m_strDBfolderpath + "\\" + file_name;

		if (QFile::exists(file_path))
		{
			QDesktopServices::openUrl(QUrl::fromLocalFile(file_path));
		}
	}
}

void BDLS::onTableCellClicked(const QItemSelection& selected, const QItemSelection& deselected)
{
	if (proxyModel)
	{
		if (selected.indexes().count() > 0)
		{
			QModelIndex index = selected.indexes()[0];
			int col_size = proxyModel->columnCount();
			QString file_name = proxyModel->data(proxyModel->index(index.row(), col_size - 1)).toString();
			QString file_path = m_strCurrentFolderPath + "\\" + file_name;
			if (DBConnected())
				file_path = m_strDBfolderpath + "\\" + file_name;
			if (file_path != m_strCurrentSelectedItemPath)
			{
				SetCurrentFile(NONE, file_name);
			}
		}
	}
	//if (updn == 0)
	//{
	//	int EnumNextBlock(int* startCol, long* startRow, int* endCol, long* endRow);
	//	int startCol, endCol;
	//	long startRow, endRow;
	//	if (m_Grid.EnumFirstBlock(&startCol, &startRow, &endCol, &endRow) == UG_SUCCESS)
	//	{
	//		if (startCol == endCol)
	//		{
	//			if (startRow != endRow)
	//			{
	//				QString cell_string(m_Grid.QuickGetText(m_Grid.GetCurrentCol(), m_Grid.GetCurrentRow()));
	//				auto_input_cell = cell_string;
	//				auto_input_from = min(startRow, endRow);
	//				auto_input_to = max(startRow, endRow);
	//				auto_input_col = startCol;
	//				PostMessage(WM_GRID_AUTO_INPUT, 0, 0);
	//				//QString temp_string;
	//				//CDlgAutoInput pDlg(cell_string, min(startRow, endRow), max(startRow, endRow), startCol);
	//				//if (pDlg.DoModal() == IDOK)
	//				//{

	//				//}
	//				//temp_string.Format(_T("%s 로 선택된 영역에 입력하시겠습니까?"), cell_string);
	//				//if (AfxMessageBox(temp_string, MB_YESNO) == IDYES)
	//				//{
	//				//	for (int i = min(startRow, endRow); i <= max(startRow, endRow); i++)
	//				//	{
	//				//		m_Grid.QuickSetText(startCol, i, cell_string);
	//				//	}
	//				//	m_Grid.RedrawAll();
	//				//}
	//			}
	//		}
	//	}
	//}
	//else
	//{
		//	output 창에서 파일 선택 이후, 동일한 항목을 선택했을 때 갱신하기 위해
		//	cellchange 에서 변경됨.
		//if (row >= 0)
		//{
		//	int col_size = ui.treeView->columnCount();
		//	Qui.treeViewItem* item = ui.treeView->item(row, column);
		//	if (item != NULL)
		//	{
		//		QString file_path = m_strCurrentFolderPath + "\\" + item->text();
		//		if (file_path != m_strCurrentSelectedItemPath)
		//		{
		//			if (IsPDF(file_path))
		//			{
		//				m_strCurrentSelectedItemPath = file_path;
		//				m_iCurrentSelectedItemType = 2;
		//				//m_pFrame->m_wndProperties.DoPreview(file_path, 1, m_bViewThumbInPreview);
		//			}
		//		}
		//	}
		//}
	//}
}

bool BDLS::IsPDF(QString file_path)
{
	if (QFile::exists(file_path))
	{
		QFileInfo info = QFileInfo(file_path);
		if (info.suffix().toLower() == "pdf")
		{
			return true;
		}
	}
	return false;
}

bool BDLS::IsMV(QString file_path)
{
	if (QFile::exists(file_path))
	{
		QFileInfo info = QFileInfo(file_path);
		if(media_file_format.contains(info.suffix().toLower()))
		{
			return true;
		}
	}
	return false;
}

void BDLS::createActions()
{
	ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

	connect(ui.actionLogin, &QAction::triggered, this, &BDLS::doLogin);
	ui.mainToolBar->addAction(ui.actionLogin);

	ui.mainToolBar->addSeparator();

	connect(ui.actionAddFolder, &QAction::triggered, this, &BDLS::doAddFolder);
	ui.mainToolBar->addAction(ui.actionAddFolder);
	ui.actionAddFolder->setEnabled(false);

	connect(ui.actionAddRow, &QAction::triggered, this, &BDLS::doAddRow);
	ui.mainToolBar->addAction(ui.actionAddRow);
	ui.actionAddRow->setEnabled(false);

	connect(ui.actionDelRow, &QAction::triggered, this, &BDLS::doDellRow);
	ui.mainToolBar->addAction(ui.actionDelRow);
	ui.actionDelRow->setEnabled(false);

	ui.mainToolBar->addSeparator();

	connect(ui.actionDBUpdate, &QAction::triggered, this, &BDLS::doDBUpdate);
	ui.mainToolBar->addAction(ui.actionDBUpdate);
	ui.actionDBUpdate->setEnabled(false);

	ui.mainToolBar->addSeparator();

	connect(dockLeft->toggleViewAction(), &QAction::triggered, this, &BDLS::toogleViewLeft);
	ui.mainToolBar->addAction(dockLeft->toggleViewAction());

	connect(dockRight->toggleViewAction(), &QAction::triggered, this, &BDLS::toogleViewRight);
	ui.mainToolBar->addAction(dockRight->toggleViewAction());

	connect(dockBottom->toggleViewAction(), &QAction::triggered, this, &BDLS::toogleViewBottom);
	ui.mainToolBar->addAction(dockBottom->toggleViewAction());
}

void BDLS::doLogin()
{
	widgetLogin login_dlg(this);
	login_dlg.setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	login_dlg.move(this->rect().center() - QPoint(login_dlg.width() / 2, login_dlg.height() / 2));
	if (login_dlg.exec() == QDialog::Accepted)
	{
		QString user_id = login_dlg.user_name;
		QString user_pass = login_dlg.user_pass;

		if (user_id == "admin")
		{
			if (user_pass == "ceohwang")
			{
				m_UserLevel = ADMIN;
				m_bIsLogin = true;
				m_loginUserID = user_id;
				m_loginUserPass = user_pass;
				m_loginUserName = "CEO";

				setWindowTitle(title_string + " > [admin]");

				ui.actionAddFolder->setEnabled(true);
				ui.actionAddRow->setEnabled(true);
				ui.actionDelRow->setEnabled(true);
				ui.actionDBUpdate->setEnabled(true);
				_widgetLeftView->ViewUser(true);

				SelectFileFromTree(m_strCurrentSelectedItemPath);
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("암호가 일치하지 않습니다."));
			}
		}
		else
		{
			ui.actionAddFolder->setEnabled(false);
			ui.actionAddRow->setEnabled(false);
			ui.actionDelRow->setEnabled(false);
			ui.actionDBUpdate->setEnabled(false);

			if (DBConnected())
			{
				QVariantList data;
				QString db_user_name;
				QString db_user_pass = "";
				int db_user_super;
				db->exec(QString("SELECT user_pass, user_name, read_only FROM user_info WHERE user_id=\"%1\"").arg(user_id), data);
				for (const auto& item : data)
				{
					auto map = item.toMap();
					db_user_name = map["user_name"].toString();
					db_user_pass = map["user_pass"].toString();
					db_user_super = map["read_only"].toInt();
				}

				if (db_user_pass == "")
				{
					QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("아이디가 존재하지 않습니다."));
				}
				else
				{
					if (db_user_pass != user_pass)
					{
						QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("암호가 일치하지 않습니다."));
					}
					else
					{
						m_loginUserID = user_id;
						m_loginUserPass = user_pass;
						m_loginUserName = db_user_name;

						m_bIsLogin = true;
						if (db_user_super == 1)
						{
							m_UserLevel = SUPER;
							_widgetLeftView->ViewUser(true);
							setWindowTitle(QString::fromLocal8Bit("%1 > [%2] - 관리자").arg(title_string).arg(user_id));
						}
						else
						{
							m_UserLevel = NORMAL;
							_widgetLeftView->ViewUser(false);
							setWindowTitle(QString::fromLocal8Bit("%1 > [%2] - 사용자").arg(title_string).arg(user_id));
						}

						if (m_bIsLogin)
						{
							SelectFileFromTree(m_strCurrentSelectedItemPath);
						}
					}
				}
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스에 연결되지 않았습니다."));
			}
		}
	}
}

void BDLS::doAddFolder()
{
	if (m_UserLevel == ADMIN)
	{
		QFileInfo f_info(m_strCurrentSelectedItemPath);
		if (f_info.isDir())
		{
			QMessageBox::StandardButton reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("[%1]\n폴더 하위 파일을 목록에 추가하시겠습니까?").arg(m_strCurrentSelectedItemPath), QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::Yes)
			{
				if (AddFolder(m_strCurrentSelectedItemPath))
				{
					proxyModel->invalidate();
					for (int i = 0; i < proxyModel->columnCount(); ++i)
						ui.tableView->resizeColumnToContents(i);

					//ui.tableView->scrollTo(proxyModel->mapFromSource(originModel->index(originModel->rowCount() - 1, 0)));
				}
			}
		}
		else
		{
			//QMessageBox::StandardButton reply = QMessageBox::question(this, QString("확인"), QString("[%1]\n폴더 하위 파일을 목록에 추가하시겠습니까?").arg(m_strCurrentSelectedItemPath), QMessageBox::Yes | QMessageBox::No);
			//if (reply == QMessageBox::Yes)
			//{
			if (IsPDF(m_strCurrentSelectedItemPath))
			{
				int new_index = originModel->rowCount();
				int col_size = originModel->columnCount();
				AddFile(new_index, col_size, m_strCurrentSelectedItemPath);

				proxyModel->invalidate();
				for (int i = 0; i < proxyModel->columnCount(); ++i)
					ui.tableView->resizeColumnToContents(i);

				//ui.tableView->scrollTo(proxyModel->mapFromSource(originModel->index(originModel->rowCount() - 1, 0)));
			}
			//}
		}
	}
}

void BDLS::doAddRow()
{
	if (m_UserLevel == ADMIN)
	{
		int new_index = originModel->rowCount();
		originModel->insertRow(new_index);
		originModel->setData(originModel->index(new_index, 0), new_index + 1);
		proxyModel->invalidate();
		//ui.tableView->scrollTo(proxyModel->mapFromSource(originModel->index(new_index, 0)));
	}
}

bool BDLS::AddFile(int new_index, int col_size, QString file_path)
{
	QDir dir(m_strDBfolderpath);
	QFileInfo f_info(file_path);

	originModel->insertRow(new_index);
	originModel->setData(originModel->index(new_index, 0), new_index + 1);
	originModel->setData(originModel->index(new_index, 3), f_info.completeBaseName());
	originModel->setData(originModel->index(new_index, col_size - 1), dir.relativeFilePath(file_path));

	return true;
}

bool BDLS::AddFolder(QString folder_path)
{
	bool add_list = false;
	QDir directory(folder_path);
	QStringList entry_list;
	entry_list << "*.pdf" << "*.PDF";
	for (int i = 0; i < media_file_format.length(); i++)
	{
		entry_list << ("*." + media_file_format[i]);
		entry_list << ("*." + media_file_format[i].toUpper());
	}
	QStringList pdfs = directory.entryList(entry_list, QDir::Files);
	int new_index = originModel->rowCount();
	int col_size = originModel->columnCount();
	foreach(QString filename, pdfs)
	{
		QString file_path = folder_path + "/" + filename;
		AddFile(new_index, col_size, file_path);
		new_index++;
		add_list = true;
	}

	QStringList folders = directory.entryList(QDir::NoDot | QDir::NoDotDot | QDir::Dirs);
	foreach(QString foldername, folders)
	{
		add_list = AddFolder(folder_path + "/" + foldername) || add_list;
	}

	return add_list;
}

void BDLS::doDellRow()
{
	if (proxyModel)
	{
		originModel->removeRow(proxyModel->mapToSource(ui.tableView->selectionModel()->currentIndex()).row());
		proxyModel->invalidate();
	}
}

QString BDLS::NextFileMNO(QString last_mno)
{
	QString m_no = "A000000";
	if (last_mno.isEmpty() || last_mno == "")
	{
	}
	else
	{
		last_mno = last_mno.toUpper();
		QChar c = last_mno.front();
		int no = last_mno.right(last_mno.length() - 1).toInt();
		no++;
		if (no > 999999)
		{
			if (c == 'Z')
				c = 'A';
			else
				c = QChar(c.toLatin1() + 1);

			no = 0;
		}
		m_no = QString(c) + QStringLiteral("%1").arg(no, 6, 10, QLatin1Char('0'));
	}
	return m_no;
}

void BDLS::doDBUpdate()
{
	int row_count = originModel->rowCount();
	int col_count = originModel->columnCount();
	//UpdateDataFromGrid();

	bool db_file_exist = false;
	if (row_count > 0)
	{
		if (!DBConnected())
		{
			QString str_file_path = m_strCurrentFolderPath + "\\index2.db3";
			if (QFile::exists(str_file_path))
			{
				db_file_exist = true;
				QMessageBox::StandardButton reply = QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("DB 파일이 존재합니다. 새로 저장하시겠습니까?"), QMessageBox::Yes | QMessageBox::No);
				if (reply != QMessageBox::Yes)
				{
					return;
				}
			}

			m_strDBfilepath = str_file_path;
			QFileInfo f_info(m_strDBfilepath);
			m_strDBfolderpath = f_info.absolutePath();
		}

		int file_name_index = col_count - 1;
		//if (m_bIsAdmin)
			col_count--;
		col_count--;

		bool update_pass_status = 
			(QMessageBox::question(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("파일 암호 설정 상태를 업데이트 하시겠습니까? 저장 시간이 늘어날 수 있습니다."),
				QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes);
		QString temp_string;
		QString temp_string1;
		try
		{
			BeginProgress();
			int total = row_count;
			QString status_string;
			if (InitDB(m_strDBfilepath))
			{
				if (!db_file_exist)
				{
					db->exec("DROP TABLE IF EXISTS headers");
					db->exec("CREATE TABLE headers (id INTEGER PRIMARY KEY, value TEXT)");
					for (int j = 3; j < col_count; j++)
					{
						temp_string = QString("INSERT INTO headers VALUES (NULL, \"%1\")").arg(originModel->headerData(j, Qt::Horizontal).toString());
						//temp_string = m_Grid.QuickGetText(j, -1);
						//sprintf_s(input_query, "INSERT INTO headers VALUES (NULL, \"%s\")", temp_string);
						db->exec(temp_string);
					}
					db->exec("CREATE TABLE file_info (id INTEGER PRIMARY KEY, file_name TEXT, file_path TEXT, m_no TEXT)");
					db->exec("CREATE TABLE header_info (file_id INTEGER, header_id INTEGER, value TEXT, PRIMARY KEY(file_id, header_id))");
					db->exec("CREATE TABLE page_info (id INTEGER PRIMARY KEY, file_id INTEGER, page_no INTEGER, block_no INTEGER, block_text TEXT)");
					db->exec("CREATE TABLE hsah_tags (id INTEGER PRIMARY KEY, tags TEXT)");
					db->exec("CREATE TABLE file_to_hash (id INTEGER PRIMARY KEY, file_id INTEGER, tag_id INTEGER)");
					db->exec("CREATE TABLE reply_info (id INTEGER PRIMARY KEY, file_id INTEGER, parent_id INTEGER, user_id TEXT, value TEXT, date_time TEXT)");
					db->exec("CREATE TABLE play_info (id INTEGER PRIMARY KEY, file_id INTEGER, s_time INTEGER, s_title TEXT)");
					db->exec("CREATE TABLE user_info (id INTEGER PRIMARY KEY, user_id TEXT, user_pass TEXT, user_name TEXT, read_only INTEGER)");
					db->exec("CREATE TABLE user_file_info (id INTEGER PRIMARY KEY, user_id TEXT, file_id INTEGER)");
					db->exec("CREATE TABLE log_info (id INTEGER PRIMARY KEY, log_type TEXT, log_content TEXT, date_time TEXT)");
				}
				//CreateDirectory(m_strCurrentFolderPath + "\\pdf_txt", NULL);

				QString managed_file_no("");

				QVariantList data;
				db->exec("SELECT max(m_no) FROM file_info", data);
				if (data.count() > 0)
				{
					//	존재할 경우
					auto map = data[0].toMap();
					if (!map["m_no"].isNull())
						managed_file_no = map["m_no"].toString();
				}

				for (int i = 0; i < row_count; i++)
				{
					QString file_name = originModel->data(originModel->index(i, file_name_index)).toString();
					QString file_name_only = file_name;
					file_name_only.chop(4);

					QString file_path = m_strDBfolderpath + "\\" + file_name;
					QString target_file_path = m_strDBfolderpath + "\\" + file_name_only + ".txt";

					QString cell_string = ("");
					QString cell_string1 = ("");
					//if (IsPDF(file_path))
					//{
					//	cell_string = "O";
					//	if (CheckEncrypted(file_path))
					//	{
					//		cell_string1 = "V";
					//	}
					//	m_lstGridText[i][2] = cell_string;
					//	m_lstGridText[i][1] = cell_string1;
					//	if (m_lstGridIndex[i] > -1)
					//	{
					//		m_Grid.QuickSetText(2, m_lstGridIndex[i], cell_string);
					//		m_Grid.QuickSetText(1, m_lstGridIndex[i], cell_string1);
					//	}
					//}

					status_string = QString::fromLocal8Bit("%1 행 저장 중").arg(i + 1);
					UpdateProgress2("", 0, 100, false);
					UpdateProgress(status_string, i + 1, total);

					int file_db_id = 0;
					//	file id 확인
					db->exec(QString("SELECT id FROM file_info WHERE file_path=\"%1\"").arg(file_path), data);
					if (data.count() > 0)
					{
						//	존재할 경우
						auto map = data[0].toMap();
						file_db_id = map["id"].toInt();
						for (int j = 3; j < col_count; j++)
						{
							QString header_name = originModel->data(originModel->index(i, j)).toString();
							temp_string = QString("UPDATE header_info SET value=\"%3\" WHERE file_id=%1 AND header_id=%2").arg(file_db_id).arg(j - 2).arg(header_name);
							db->exec(temp_string);
						}
					}
					else
					{
						//	존재하지 않을 경우
						//	insert file_info
						managed_file_no = NextFileMNO(managed_file_no);
						temp_string = QString("INSERT INTO file_info VALUES (NULL, \"%1\", \"%2\", \"%3\")").arg(file_name).arg(file_path).arg(managed_file_no);
						db->exec(temp_string);

						//	file id 확인
						db->exec(QString("SELECT id FROM file_info WHERE file_path=\"%1\"").arg(file_path), data);
						if (data.count() > 0)
						{
							//	존재할 경우
							auto map = data[0].toMap();
							file_db_id = map["id"].toInt();

							for (int j = 3; j < col_count; j++)
							{
								QString header_name = originModel->data(originModel->index(i, j)).toString();
								temp_string = QString("INSERT INTO header_info VALUES (%1, %2, \"%3\")").arg(file_db_id).arg(j - 2).arg(header_name);
								db->exec(temp_string);
							}
						}
						else
						{
							//	저장이 잘 안됐나?
						}
					}

					//	file id 확인
					db->exec(QString("SELECT page_no FROM page_info WHERE file_id=%1").arg(file_db_id), data);
					if (data.count() > 0)
					{
						//	존재할 경우
					}
					else
					{
						if ((!QFile::exists(target_file_path)) && QFile::exists(file_path))
						{
							//status_string.Format(_T("%d 행 저장 중 (텍스트 추출)"), i + 1);
							UpdateProgress2(QString::fromLocal8Bit("(텍스트 추출)"), 0, 100);

							QStringList arguments;
							arguments.append(file_path);
							arguments.append(target_file_path);

							int i_return = QProcess::execute("PdfTxtExtractor.exe", arguments);
							if (i_return == 0)
							{
							}
							else
							{
								/*QMessageBox::critical(this, QString("파일 생성 오류"), QString("PDF 파일 생성에 실패했습니다. 관리자에게 문의하십시요."));*/
								//	text 추출 오류
							}
						}
						if (QFile::exists(target_file_path))
						{
							QFile file(target_file_path);
							if (!file.open(QIODevice::ReadOnly)) {
								//	file.errorString()
							}
							else
							{
								QTextStream in(&file);
								in.setAutoDetectUnicode(true);

								int page_no, block_no;
								int page_index = 1;

								QStringList listOfLines = in.readAll().split("\n");

								int index = 0;
								while (index < listOfLines.count() - 1)
								{
									UpdateProgress2(QString::fromLocal8Bit("텍스트 저장"), index + 1, listOfLines.count());
									QString line = listOfLines[index]; index++;
									QString line_info = listOfLines[index]; index++;
									QStringList fields = line_info.split(",");
									if (fields.count() > 1)
									{
										QStringList page_info = fields[0].split(":");
										QStringList block_info = fields[1].split(":");

										page_no = page_info[1].toInt();
										block_no = block_info[1].toInt();
									}

									line = line.replace("'", "");
									line = line.replace("\n", " ");
									line = line.replace("\"", " ");

									temp_string = QString("INSERT INTO page_info VALUES (NULL, %1, %2, %3, \"%4\")")
										.arg(file_db_id)
										.arg(page_no)
										.arg(block_no)
										.arg(line);
									db->exec(temp_string);
								}

								//while (!in.atEnd())
								//{
								//	QString line = in.readLine();
								//	QString line_info = in.readLine();
								//	QStringList fields = line_info.split(",");
								//	if (fields.count() > 1)
								//	{
								//		QStringList page_info = fields[0].split(":");
								//		QStringList block_info = fields[1].split(":");

								//		page_no = page_info[1].toInt();
								//		block_no = block_info[1].toInt();
								//	}

								//	line = line.replace("'", "");
								//	line = line.replace("\n", " ");
								//	line = line.replace("\"", " ");

								//	temp_string = QString("INSERT INTO page_info VALUES (NULL, %1, %2, %3, \"%4\")")
								//		.arg(file_db_id)
								//		.arg(page_no)
								//		.arg(block_no)
								//		.arg(line);
								//	db->exec(temp_string);

								//	//int cur_file_pos = ftell(extrect_fp);
								//	//UpdateProgress2(cur_file_pos, total_file_size);
								//}
							}
						}
					}
				}
			}
			EndProgress();
			include_pass_status = true;
			//QString cell_string(utf_to_unicode(m_strDBfilepath).c_str());
			m.setValue("CURRENT_PATH", m_strDBfilepath);
			QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스에 저장되었습니다."));
		}
		catch (std::exception& e)
		{
			//temp_string.Format(_T("db exception : %S"), e.what());
			//AddOutput(_T("error"), temp_string, 0, 0);
			//EndProgress();
			QMessageBox::information(this, QString::fromLocal8Bit("확인"), QString::fromLocal8Bit("데이터베이스에 저장에 실패했습니다."));
		}
	}
}

void BDLS::closeEvent(QCloseEvent* event)
{
	writeSettings();
}

void BDLS::readSettings()
{
	QSettings settings("DIGIBOOK", QCoreApplication::applicationName());
	const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
	if (geometry.isEmpty()) {
		const QRect availableGeometry = screen()->availableGeometry();
		resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
		move((availableGeometry.width() - width()) / 2,
			(availableGeometry.height() - height()) / 2);
	}
	else {
		restoreGeometry(geometry);
	}
}

void BDLS::writeSettings()
{
	QSettings settings("DIGIBOOK", QCoreApplication::applicationName());
	settings.setValue("geometry", saveGeometry());
}

void BDLS::BeginProgress()
{
	if (_widgetProgress)
	{
		_widgetProgress->SetStatus1("");
		_widgetProgress->SetProgress1(0);
		_widgetProgress->SetStatus2("");
		_widgetProgress->SetProgress2(0);
		_widgetProgress->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
		_widgetProgress->move(this->rect().center() - QPoint(_widgetProgress->width() / 2, _widgetProgress->height() / 2));
		_widgetProgress->show();
		check_time.start();
		check_time_ms = check_time.elapsed();
	}
}

void BDLS::UpdateProgress(QString status, int pos, int total, bool update)
{
	if (_widgetProgress)
	{
		_widgetProgress->SetStatus1(status);
		_widgetProgress->SetProgress1(pos * 100 / total);
		if (update)
		{
			qint64 current_check_time = check_time.elapsed();
			if ((current_check_time - check_time_ms) > 1000)
			{
				qApp->processEvents();
				check_time_ms = current_check_time;
			}
		}
	}
}

void BDLS::UpdateProgress2(QString status, int pos, int total, bool update)
{
	if (_widgetProgress)
	{
		_widgetProgress->SetStatus2(status);
		_widgetProgress->SetProgress2(pos * 100 / total);
		if (update)
		{
			qint64 current_check_time = check_time.elapsed();
			if ((current_check_time - check_time_ms) > 1000)
			{
				qApp->processEvents();
				check_time_ms = current_check_time;
			}
		}
	}
}


void BDLS::EndProgress()
{
	if (_widgetProgress)
	{
		_widgetProgress->hide();
	}
}

void BDLS::generateFilters()
{
	// Generate a new row of filter line edits
	ui.tableView->generateFilters(static_cast<size_t>(proxyModel->columnCount()), 0);

	// Apply the stored filter strings to the new row of line edits
	// Set filters blocking signals for this since the filter is already applied to the browse table model
	//FilterTableHeader* filterHeader = qobject_cast<FilterTableHeader*>(ui.tableView->horizontalHeader());
	//bool oldState = filterHeader->blockSignals(true);
	//for (auto filterIt = settings.filterValues.cbegin(); filterIt != settings.filterValues.cend(); ++filterIt)
	//	ui.tableView->setFilter(sqlb::getFieldNumber(obj, filterIt->first) + 1, filterIt->second);
	//filterHeader->blockSignals(oldState);

	//ui.tableView->setEnabled(m_model->filterCount() > 0 || !ui->editGlobalFilter->text().isEmpty());
}

void BDLS::updateFilter(size_t column, const QString& value)
{
	// Set minimum width to the vertical header in order to avoid flickering while a filter is being updated.
	ui.tableView->verticalHeader()->setMinimumWidth(ui.tableView->verticalHeader()->width());

	// Update the filter in the model and its query
	const std::string column_name = proxyModel->headerData(static_cast<int>(column), Qt::Horizontal, Qt::EditRole).toString().toStdString();
	proxyModel->updateFilter(static_cast<int>(column), value);
}

void BDLS::AddFileList(QString user_id)
{
	if (DBConnected())
	{
		QModelIndexList setected_indexes = ui.tableView->selectionModel()->selectedIndexes();
		for (int i = 0; i < setected_indexes.count(); i++)
		{
			QString file_id = proxyModel->data(proxyModel->index(setected_indexes[i].row(), 0), Qt::AccessibleTextRole).toString();
			QString file_name = proxyModel->data(proxyModel->index(setected_indexes[i].row(), 3)).toString();
			if (file_id != "")
			{
				QVariantList data;
				db->exec(QString("SELECT file_id FROM user_file_info WHERE user_id=\"%1\" AND file_id=%2").arg(user_id).arg(file_id), data);
				if (data.count() > 0)
				{
					//	존재
				}
				else
				{
					QString temp_string = QString("INSERT INTO user_file_info VALUES (NULL, \"%1\", %2)").arg(user_id).arg(file_id);
					db->exec(temp_string);
				}
			}
			else
			{
				QString temp_string = QString("INSERT INTO log_info VALUES (NULL, \"%1\", \"%2\", datetime('now', 'localtime'))").arg("error").arg(file_name + "의 file_id가 존재하지 않습니다. 사용자 파일 추가에 실패했습니다.");
				db->exec(temp_string);
			}
		}
	}
}

//void BDLS::setWindowTitle(const QString& title)
//{
//	m_titleBar->setWindowTitle(title);
//}
//
//void BDLS::setWindowTitleHeight(int h)
//{
//	m_titleBar->setFixedHeight(h);
//}

void BDLS::setColor1()
{
	qApp->setPalette(style->standardPalette());
	m.setValue("THEME", "1");
}

void BDLS::setColor2()
{
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(53, 53, 53));
	palette.setColor(QPalette::WindowText, Qt::white);
	palette.setColor(QPalette::Base, QColor(15, 15, 15));
	palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	palette.setColor(QPalette::ToolTipBase, Qt::white);
	palette.setColor(QPalette::ToolTipText, Qt::white);
	palette.setColor(QPalette::Text, Qt::white);
	palette.setColor(QPalette::Button, QColor(53, 53, 53));
	palette.setColor(QPalette::ButtonText, Qt::white);
	palette.setColor(QPalette::BrightText, Qt::red);

	palette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
	palette.setColor(QPalette::HighlightedText, Qt::black);
	qApp->setPalette(palette);
	m.setValue("THEME", "2");
}

void BDLS::setColor3()
{
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(196, 218, 250));
	palette.setColor(QPalette::WindowText, QColor(0, 0, 0));
	palette.setColor(QPalette::Base, QColor(255, 255, 255));
	palette.setColor(QPalette::AlternateBase, QColor(225, 236, 252));
	palette.setColor(QPalette::ToolTipBase, QColor(255, 255, 220));
	palette.setColor(QPalette::ToolTipText, QColor(0, 0, 0));
	palette.setColor(QPalette::Text, QColor(0, 0, 0));
	palette.setColor(QPalette::Button, QColor(196, 218, 250));
	palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
	palette.setColor(QPalette::BrightText, QColor(255, 255, 255));
	qApp->setPalette(palette);
	m.setValue("THEME", "3");
}

void BDLS::toogleViewLeft()
{
}

void BDLS::toogleViewRight()
{
}

void BDLS::toogleViewBottom()
{
}