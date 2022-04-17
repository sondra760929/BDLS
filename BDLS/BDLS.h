#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BDLS.h"
#include <QtWidgets>
#include "widgetLeftView.h"
#include "widgetRightView.h"
#include "widgetBottomView.h"
#include "widgetLogin.h"
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <qsqlfield.h>
#include "MySortFilterProxyModel.h"
#include "db_manager.h"

class BDLS : public QMainWindow
{
    Q_OBJECT

public:
    BDLS(QWidget *parent = Q_NULLPTR);

    bool m_bIsAdmin = true;

    //QTableWidget* tableWidget;
    widgetLeftView* _widgetLeftView;
    widgetRightView* _widgetRightView;
    widgetBottomView* _widgetBottomView;
    QAbstractItemModel* originModel;
    MySortFilterProxyModel* proxyModel;

    QString m_strDBfilepath;
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

    void SelectFileFromTree(QString file_path);
    void InitFromDB();
    void OnOpenSingle();
    bool IsPDF(QString file_path);
    bool IsMV(QString file_path);
    void doLogin();
    void doAddRow();
    void doDellRow();
    void doDBUpdate();
    QString NextFileMNO(QString last_mno);
    void ClearTable();
    void setSearchCombo();
    void SetCurrentFile(QString file_name, QString file_info = "");
    void setTagList();
    QMap<QString, int> map_title_to_index;
    QMap<QString, int> map_file_to_id;
    int m_iCurrentFileDBID;

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
};
