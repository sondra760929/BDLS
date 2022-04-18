#pragma once

#include <QWidget>
#include "ui_widgetLeftView.h"
#include <qtreeview.h>
#include <QFileSystemModel>
#include <QtWidgets>
#include "SearchControls.h"
#include "widgetMemo.h"

class BDLS;
class widgetMemo;
class widgetLeftView : public QWidget
{
	Q_OBJECT

public:
	widgetLeftView(QWidget *parent = Q_NULLPTR);
	~widgetLeftView();

	QTreeView* fileTree;
	QFileSystemModel model;
	BDLS* m_pView;

	QMap<QString, int> header_to_index;
	QList< SearchControls*> search_list;
	QList< SearchControls*> memo_list;

	QList< widgetMemo* > memo_control_list;
	void SetCurrentFile(QString file_path);
	void setSearchCombo(QMap<QString, int>& map_h_to_i);
	void OnMemoClicked(widgetMemo* pmemo);
	void clearMemoSelection();
	void UpdateMemo();
	void AddMemoControl(MemoData* new_memo, MemoData* parent_memo = NULL);
	void clearMemo();
	void setTagList();
	void clearTags();
	void refreshMVList();
	void clearMVs();
	void setMVPos(int secs);
	void ViewUser(bool show);
	void setUserList();

private:
	Ui::widgetLeftView ui;
	QBoxLayout* searchViewLayout;
	QPushButton* btn_add;
	QPushButton* btn_dell;
	QPushButton* btn_memo_add;
	QPushButton* btn_memo_dell;
	QListView* tagSearchList;
	QLineEdit* tagSearchEdit;
	QListWidget* mvSearchList;
	QLineEdit* mvSearchEdit;

	QBoxLayout* noteViewLayout;
	QPushButton* noteParent;
	int parent_memo_id;
	QTextEdit* memoText;
	QWidget* memoList;
	QMap<int, MemoData*> memoDatas;

	QListView* tagList;
	QCompleter* completer = NULL;
	QLineEdit* tagEdit = NULL;
	QStringList tags;
	QStringListModel* fileTagModel = NULL;
	QMap<int, QString> tagDatas;

	QMap<int, QString> searchTagDatas;
	QMap<QString, int> searchTagToIndex;
	QStringListModel* searchTagModel = NULL;
	QCompleter* search_completer = NULL;

	QTimeEdit* mvTime;
	QLineEdit* mvText;
	QListWidget* mvList;
	QMap<int, QString> timeToMemo;
	QMap<QString, int> fileTagData;

	QMap<QString, int> serchVMDatas;

	QBoxLayout* userViewLayout;
	QTableWidget* userTable;

private slots:
	void onCurrentChanged(const QItemSelection& current, const QItemSelection& prev);
	void onSearchAdd();
	void onSearchDell();
	void onSearchMemoAdd();
	void onSearchMemoDell();
	void onSearchTagAdd();
	void onSearchMVAdd();
	void doSearch1();
	void doSearch2();
	void doSearch3();
	void doSearch4();
	void doAddMemo();
	void doAddTag();
	void doAddMV();
	void doNewMemo();
	void onSearchTagClicked(const QModelIndex& index);
	void onSearchMVClicked(QListWidgetItem* item);
	void onFileTagClicked(const QModelIndex& index);
	void onFileMVClicked(QListWidgetItem* current, QListWidgetItem* previous);
	void onFileMVDClicked(QListWidgetItem* item);
	void doAddUser();
	void doDelUser();
	void doUpdateUser();
};
