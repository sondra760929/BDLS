﻿#include "BDLS.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

QString m_strKey = QString("HKEY_CURRENT_USER\\SOFTWARE\\DIGIBOOK\\PDFIndexExplorer\\Settings");
QSettings m(m_strKey, QSettings::Registry64Format);
QStringList media_file_format;
BDLS::BDLS(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

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

	ui.treeView->setModel(proxyModel);

	connect(ui.treeView->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(onTableCellClicked(const QItemSelection&, const QItemSelection&)));

	createDockWindows();
	createActions();

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
	QDockWidget* dock;

	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

	dock = new QDockWidget(tr("검색결과"), this);
	_widgetBottomView = new widgetBottomView(dock);
	dock->setWidget(_widgetBottomView);
	addDockWidget(Qt::BottomDockWidgetArea, dock);
	_widgetBottomView->m_pView = this;

	dock = new QDockWidget(tr("관리"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	_widgetLeftView = new widgetLeftView(dock);
	dock->setWidget(_widgetLeftView);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	//viewMenu->addAction(dock->toggleViewAction());
	_widgetLeftView->m_pView = this;

	dock = new QDockWidget(tr("미리보기"), this);
	_widgetRightView = new widgetRightView(dock);
	dock->setWidget(_widgetRightView);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	//viewMenu->addAction(dock->toggleViewAction());
	_widgetRightView->m_pView = this;
}

void BDLS::SelectFileFromTree(QString file_path)
{
	m_strCurrentSelectedItemPath = file_path;
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
	else
	{
		m_iCurrentSelectedItemType = 4;
		m_strCurrentFolderPath = file_path;
	}

}

void BDLS::InitFromDB()
{
	QString temp_string;
	try
	{
		if (QFile::exists(m_strDBfilepath))
		{
			db_manager db(m_strDBfilepath);
			if (db.Connected())
			{
				QStringList table_list = db.tables();
				if (table_list.contains("headers"))
				{
					ClearTable();

					QStringList header_list;
					// Compile a SQL query, containing one parameter (index 1)
					QVariantList data;
					db.exec("SELECT id, value FROM headers ORDER BY id", data);
					for (const auto& item : data)
					{
						auto map = item.toMap();
						//map["id"].toInt();
						header_list.append(map["value"].toString());
						map_title_to_index[map["value"].toString()] = map["id"].toInt();
					}

					if (header_list.size() > 0)
					{
						m_iCurrentSelectedItemType = 1;
						int row = 1;
						int col_size = header_list.size() + 5;	//	no, ?, !, 검색결과, 파일경로
						QString no;

						originModel->insertColumn(0);
						originModel->setHeaderData(0, Qt::Horizontal, "No");
						originModel->insertColumn(1);
						originModel->setHeaderData(1, Qt::Horizontal, "?");
						originModel->insertColumn(2);
						originModel->setHeaderData(2, Qt::Horizontal, "!");
						for (int i = 0; i < header_list.size(); i++)
						{
							originModel->insertColumn(i + 3);
							originModel->setHeaderData(i + 3, Qt::Horizontal, header_list[i]);
						}
						originModel->insertColumn(col_size - 2);
						originModel->setHeaderData(col_size - 2, Qt::Horizontal, "검색 결과");

						//if (m_bIsAdmin)
						{
							originModel->insertColumn(col_size - 1);
							originModel->setHeaderData(col_size - 1, Qt::Horizontal, "파일 경로");
						}

						db.exec("SELECT id, file_name, file_path FROM file_info ORDER BY id", data);
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

						for(int i=0; i<file_id_list.count(); i++)
						{
							originModel->insertRow(i);
							originModel->setData(originModel->index(i, 0), i + 1);

							db.exec(QString("SELECT file_id, header_id, value FROM header_info WHERE file_id=%1").arg(file_id_list[i]), data);
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
						ui.treeView->resizeColumnToContents(i);

					setSearchCombo();
					setTagList();
				}
				else
				{
					//AddOutput(_T("error"), _T("headers not exists"), 0, 0);
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
	map_file_to_id.clear();
	m_iCurrentFileDBID = 0;
}

void BDLS::setSearchCombo()
{
	_widgetLeftView->setSearchCombo(map_title_to_index);
}

void BDLS::setTagList()
{
	_widgetLeftView->setTagList();
}

void BDLS::OnOpenSingle()
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
		if (m_strDBfilepath != "" && data_row_count > 0)
		{
			//	db를 읽은 상태임
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, QString("확인"), QString("현재 테이블에 추가하시겠습니까? [아니오]를 선택하시면 엑셀을 새로 로딩합니다."),
				QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
			if (reply == QMessageBox::Yes)
			{
				//	추가로 로딩
				if (m_strCurrentFolderPath != folder_path)
				{
					reply = QMessageBox::question(this, QString("확인"), QString("현재 DB파일과 다른 폴더에 있는 엑셀파일입니다.기존 파일 링크가 해제될 수 있습니다.계속 진행하시겠습니까 ? "), QMessageBox::Yes | QMessageBox::No);
					if (reply != QMessageBox::Yes)
					{
						//	폴더가 달라서 취소
						return;
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
					while (cell != NULL && cell->readValue().toString() != "")
					{
						cell = xlsx.cellAt(1, col_size - 2);
						QString cell_string = cell->readValue().toString();

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
							QString("확인"), 
							QString("동일하지 않은 항목이 존재합니다. 기존 항목과 동일하지 않은 항목은 무시됩니다. 계속 진행하시겠습니까?"), 
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
					while (cell != NULL && cell->readValue().toString() != "")
					{
						originModel->insertRow(0);
						//m_lstGridText.resize(data_row_count);
						//m_lstGridText[data_row_count - 1].resize(col_size);
						//m_lstGridShow.resize(data_row_count);
						//m_lstGridShow[data_row_count - 1].resize(col_size, true);
						//m_lstGridIndex.resize(data_row_count);
						//m_lstGridSelected.resize(data_row_count);
						//m_lstGridKey.resize(data_row_count);

						no = QString::number(data_row_count);

						originModel->setData(originModel->index(0, 0), no);
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
									QString cell_string = cell->readValue().toString();
									originModel->setData(originModel->index(0, new_col_index[i - 3]), cell_string);
									//m_lstGridText[data_row_count - 1][new_col_index[i - 3]] = cell_string;
								}
							}
						}

						cell = xlsx.cellAt(row, 26);
						QString cell_string;
						if (cell != NULL)
						{
							cell_string = cell->readValue().toString();
						}
						if (m_bIsAdmin)
						{
							originModel->setData(originModel->index(0, col_size - 1), cell_string);
						}
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
		m_strDBfilepath = "";

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
			while (cell != NULL && cell->readValue().toString() != "")
			{
				//ui.treeView->setColumnCount(col_size + 1);
				//m_Grid.SetNumberCols(col_size + 1);
				header_label << cell->readValue().toString();
				originModel->insertColumn(0);
				//SetItemData(row - 2, col_size, cell->readValue().toString());
				col_size++;
				cell = xlsx.cellAt(row, col_size - 2);
			}
			header_label << QString("검색 결과");
			originModel->insertColumn(0);
			//ui.treeView->setColumnCount(col_size + 1);
			//SetItemData(row - 2, col_size, QString("검색 결과"));
			col_size++;

			//if (m_bIsAdmin)
			//{
				//ui.treeView->setColumnCount(col_size + 1);
				header_label << QString("파일 경로");
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
			while (cell != NULL && cell->readValue().toString() != "")
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
						//SetItemData(row - 2, i, cell->readValue().toString());
						originModel->setData(originModel->index(row_index, i), cell->readValue().toString());
						//m_lstGridText[row - 2][i] = cell_string;
					}
				}
				cell = xlsx.cellAt(row, 26);
				QString cell_string;
				if (cell != NULL)
				{
					cell_string = cell->readValue().toString();
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
			ui.treeView->resizeColumnToContents(i);
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

void BDLS::SetCurrentFile(QString file_name, QString file_info)
{
	QString file_path = m_strCurrentFolderPath + "\\" + file_name;
	m_iCurrentFileDBID = map_file_to_id[file_name];
	_widgetLeftView->UpdateMemo();
	if (IsPDF(file_path))
	{
		m_strCurrentSelectedItemPath = file_path;
		m_iCurrentSelectedItemType = 2;
		_widgetRightView->ViewPDF(file_path, file_info);
		//m_pFrame->m_wndProperties.DoPreview(file_path, 1, m_bViewThumbInPreview);
	}
	else if (IsMV(file_path))
	{
		m_strCurrentSelectedItemPath = file_path;
		m_iCurrentSelectedItemType = 3;
		_widgetRightView->ViewMovie(file_path, file_info);
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
			if (file_path != m_strCurrentSelectedItemPath)
			{
				SetCurrentFile(file_name);
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
	connect(ui.actionAddRow, &QAction::triggered, this, &BDLS::doAddRow);
	ui.mainToolBar->addAction(ui.actionAddRow);

	connect(ui.actionDelRow, &QAction::triggered, this, &BDLS::doDellRow);
	ui.mainToolBar->addAction(ui.actionDelRow);

	connect(ui.actionDBUpdate, &QAction::triggered, this, &BDLS::doDBUpdate);
	ui.mainToolBar->addAction(ui.actionDBUpdate);
}

void BDLS::doAddRow()
{

}

void BDLS::doDellRow()
{

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
		//if (m_strDBfilepath == "")
		//{
		QString str_file_path = m_strCurrentFolderPath + "\\index.db3";
		m_strDBfilepath = str_file_path;

		if (QFile::exists(str_file_path))
		{
			db_file_exist = true;
			//if (AfxMessageBox(_T("DB 파일이 존재합니다. 새로 저장하시겠습니까?"), MB_YESNO) == IDYES)
			//{
			//	char strUtf8[512] = { 0, };
			//	lpctstr_to_utf8(str_file_path, strUtf8);
			//	m_strDBfilepath = std::string(strUtf8);
			//}
			//else
			//{
			//	return;
			//}
		}
		//else
		//{
		//	char strUtf8[512] = { 0, };
		//	lpctstr_to_utf8(str_file_path, strUtf8);
		//	m_strDBfilepath = std::string(strUtf8);
		//}
	//}
	//else
	//{
	//	OnButtonUpdatedb();
	//	return;
	//}

		if (m_bIsAdmin)
			col_count--;
		col_count--;

		bool update_pass_status = 
			(QMessageBox::question(this, QString("확인"), QString("파일 암호 설정 상태를 업데이트 하시겠습니까? 저장 시간이 늘어날 수 있습니다."), 
				QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes);
		QString temp_string;
		QString temp_string1;
		try
		{
			//BeginProgress();
			int total = row_count;
			QString status_string;
			db_manager db(m_strDBfilepath);
			if (!db_file_exist)
			{
				db.exec("DROP TABLE IF EXISTS headers");
				db.exec("CREATE TABLE headers (id INTEGER PRIMARY KEY, value TEXT)");
				for (int j = 3; j < col_count; j++)
				{
					temp_string = QString("INSERT INTO headers VALUES (NULL, \"%1\")").arg(originModel->headerData(j, Qt::Horizontal).toString());
					//temp_string = m_Grid.QuickGetText(j, -1);
					//sprintf_s(input_query, "INSERT INTO headers VALUES (NULL, \"%s\")", temp_string);
					db.exec(temp_string);
				}
				db.exec("CREATE TABLE file_info (id INTEGER PRIMARY KEY, file_name TEXT, file_path TEXT, m_no TEXT)");
				db.exec("CREATE TABLE header_info (file_id INTEGER, header_id INTEGER, value TEXT, PRIMARY KEY(file_id, header_id))");
				db.exec("CREATE TABLE page_info (id INTEGER PRIMARY KEY, file_id INTEGER, page_no INTEGER, block_no INTEGER, block_text TEXT)");
				db.exec("CREATE TABLE hsah_tags (id INTEGER PRIMARY KEY, tags TEXT)");
				db.exec("CREATE TABLE file_to_hash (id INTEGER PRIMARY KEY, file_id INTEGER, tag_id INTEGER)");
				db.exec("CREATE TABLE reply_info (id INTEGER PRIMARY KEY, file_id INTEGER, parent_id INTEGER, value TEXT, date_time TEXT)");
				db.exec("CREATE TABLE play_info (id INTEGER PRIMARY KEY, file_id INTEGER, s_time INTEGER, s_title TEXT)");
				db.exec("CREATE TABLE user_info (id INTEGER PRIMARY KEY, user_id TEXT, user_pass TEXT, user_name TEXT, read_only INTEGER)");
			}
			//CreateDirectory(m_strCurrentFolderPath + "\\pdf_txt", NULL);

			QString managed_file_no("");

			QVariantList data;
			db.exec("SELECT max(m_no) FROM file_info", data);
			if (data.count() > 0)
			{
				//	존재할 경우
				auto map = data[0].toMap();
				if (!map["m_no"].isNull())
					managed_file_no = map["m_no"].toString();
			}

			for (int i = 0; i < row_count; i++)
			{
				QString file_name = originModel->data(originModel->index(i, col_count - 1)).toString();
				QString file_name_only = file_name;
				file_name_only.chop(4);

				QString file_path = m_strCurrentFolderPath + "\\" + file_name;
				QString target_file_path = m_strCurrentFolderPath + "\\" + file_name_only + ".txt";

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

				status_string = QString("%1 행 저장 중").arg(i + 1);
				//UpdateProgress(status_string, i + 1, total);

				int file_db_id = 0;
				//	file id 확인
				db.exec(QString("SELECT id FROM file_info WHERE file_path=\"%1\"").arg(file_path), data);
				if (data.count() > 0)
				{
					//	존재할 경우
					auto map = data[0].toMap();
					file_db_id = map["id"].toInt();
					for (int j = 3; j < col_count; j++)
					{
						QString header_name = originModel->data(originModel->index(i, j)).toString();
						temp_string = QString("UPDATE header_info SET value=\"%3\" WHERE file_id=%1 AND header_id=%2").arg(file_db_id).arg(j - 2).arg(header_name);
						db.exec(temp_string);
					}
				}
				else
				{
					//	존재하지 않을 경우
					//	insert file_info
					managed_file_no = NextFileMNO(managed_file_no);
					temp_string = QString("INSERT INTO file_info VALUES (NULL, \"%1\", \"%2\", \"%3\")").arg(file_name).arg(file_path).arg(managed_file_no);
					db.exec(temp_string);

					//	file id 확인
					db.exec(QString("SELECT id FROM file_info WHERE file_path=\"%1\"").arg(file_path), data);
					if (data.count() > 0)
					{
						//	존재할 경우
						auto map = data[0].toMap();
						file_db_id = map["id"].toInt();

						for (int j = 3; j < col_count; j++)
						{
							QString header_name = originModel->data(originModel->index(i, j)).toString();
							temp_string = QString("INSERT INTO header_info VALUES (%1, %2, \"%3\")").arg(file_db_id).arg(j-2).arg(header_name);
							db.exec(temp_string);
						}
					}
					else
					{
						//	저장이 잘 안됐나?
					}
				}

				//	file id 확인
				db.exec(QString("SELECT page_no FROM page_info WHERE file_id=%1").arg(file_db_id), data);
				if (data.count() > 0)
				{
					//	존재할 경우
				}
				else
				{
					if ((!QFile::exists(target_file_path)) && QFile::exists(file_path))
					{
						//status_string.Format(_T("%d 행 저장 중 (텍스트 추출)"), i + 1);
						//UpdateProgress(status_string, i + 1, total);

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
							int total_file_size = file.size();
							int page_no, block_no;
							int page_index = 1;

							while (!in.atEnd())
							{
								QString line = in.readLine();
								QString line_info = in.readLine();
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
								db.exec(temp_string);

								//int cur_file_pos = ftell(extrect_fp);
								//UpdateProgress2(cur_file_pos, total_file_size);
							}
						}
					}
				}
			}
			//EndProgress();
			include_pass_status = true;
			//QString cell_string(utf_to_unicode(m_strDBfilepath).c_str());
			m.setValue("CURRENT_PATH", m_strDBfilepath);
			QMessageBox::information(this, QString("확인"), QString("데이터베이스에 저장되었습니다."));
		}
		catch (std::exception& e)
		{
			//temp_string.Format(_T("db exception : %S"), e.what());
			//AddOutput(_T("error"), temp_string, 0, 0);
			//EndProgress();
			QMessageBox::information(this, QString("확인"), QString("데이터베이스에 저장에 실패했습니다."));
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