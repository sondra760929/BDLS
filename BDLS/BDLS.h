#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BDLS.h"
#include <QtWidgets>
#include "widgetLeftView.h"
#include "widgetRightView.h"
#include "widgetBottomView.h"
#include "widgetLogin.h"
#include <QtDebug>
#include "MySortFilterProxyModel.h"
#include "db_manager.h"
#include "widgetProgress.h"
#include "TitleBar.h"

enum USER_LEVEL
{
    NORMAL,
    SUPER,
    ADMIN
};

class BDLS : public QMainWindow
{
    Q_OBJECT

public:
    BDLS(QWidget *parent = Q_NULLPTR);

    void setWindowTitle(const QString& title);
    void setWindowTitleHeight(int h);
    TitleBar* m_titleBar;//Title Block

    USER_LEVEL m_UserLevel = NORMAL;
    bool m_bIsLogin = false;
    QString m_loginUserID = "";
    QString m_loginUserPass = "";
    QString m_loginUserName = "";

    //QTableWidget* tableWidget;
    widgetLeftView* _widgetLeftView;
    widgetRightView* _widgetRightView;
    widgetBottomView* _widgetBottomView;
    QAbstractItemModel* originModel;
    MySortFilterProxyModel* proxyModel;
    QDockWidget* dockLeft;
    QDockWidget* dockRight;
    QDockWidget* dockBottom;

    void CheckAndCreateTable();

    void toogleViewLeft();
    void toogleViewRight();
    void toogleViewBottom();
    void setSelectBySearch(int file_id);
    void resetSelectBySearch();

    void generateFilters();
    void updateFilter(size_t column, const QString& value);

    QString m_strDBfilepath;
    QString m_strDBfolderpath;
    QString m_strCurrentSelectedItemPath;
    QString m_strCurrentFolderPath;
    QString m_strCurrentExcelPath;
    //void SetItemData(int row, int col, QString value, QColor back_color = Qt::white, int span = 1);
    //void SetItemData(int row, int col, int value, QColor back_color = Qt::white, int span = 1);
    bool m_bAutoSave;
    int m_iCurrentSelectedItemType;

    QTimer* m_saveTimer;

    db_manager* db;
    bool InitDB(QString db_file_path);
    bool DBConnected();
    bool include_pass_status;
    void CloseDB();
    QElapsedTimer check_time;
    qint64 check_time_ms;

    void SelectFileFromTree(QString file_path);
    void InitFromDB();
    void OnOpenSingle();
    bool IsPDF(QString file_path);
    bool IsMV(QString file_path);
    void doLogin();
    void doAddFolder();
    void doAddRow();
    void doDellRow();
    void doDBUpdate();
    QString NextFileMNO(QString last_mno);
    void ClearTable();
    void setSearchCombo();
    void SetCurrentFile(SEARCH_TYPE search_type, QString file_name, QString file_info1 = "", QString file_info2 = "", QString file_info3 = "", QString file_info4 = "");
    void setTagList();
    QMap<QString, int> map_title_to_index;
    QList<QString> title_list;
    QMap<QString, int> map_file_to_id;
    int m_iCurrentFileDBID;
    bool AddFolder(QString folder_path);
    bool AddFile(int new_index, int col_size, QString file_path);
    widgetProgress* _widgetProgress;
    void BeginProgress();
    void UpdateProgress(QString status, int pos, int total, bool update = true);
    void UpdateProgress2(QString status, int pos, int total, bool update = true);
    void EndProgress();
    void LoadOldDB(QString file_path);

    void AddFileList(QString user_id);

    void setColor1();
    void setColor2();
    void setColor3();
    QStyle* style;

    QString title_string;

    void readSettings();
    void writeSettings();
protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::BDLSClass ui;
    void createDockWindows();
    void createActions();

private slots:
    void DoAutoSave();
    void onTableCellClicked(const QItemSelection& selected, const QItemSelection& deselected);
    void onTableDoubleClicked(const QModelIndex& index);
};
