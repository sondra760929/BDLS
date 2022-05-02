#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <qsqlfield.h>

enum SEARCH_TYPE
{
    NONE,
    CONTENT,
    MEMO,
    HASHTAG
};


class db_manager {
public:
    db_manager(const QString& path)
    {
        Connect(path);
    }

    ~db_manager()
    {
        if (is_connected)
            my_db.close();
    }

    void Close()
    {
        if (is_connected)
        {
            my_db.close();
            is_connected = false;
        }
    }

    bool Connect(QString path)
    {
        if (is_connected)
        {
            if (path.toLower() != db_path.toLower())
            {
                //  다른 경로로 연결 시도
                Close();

                my_db.setDatabaseName(path);

                if (my_db.open()) {
                    is_connected = true;
                    db_path = path;
                    qDebug() << "success DB connection.\n";
                }
                else {
                    is_connected = false;
                    qDebug() << "fail DB connection.\n";
                }
            }
        }
        else
        {
            my_db = QSqlDatabase::addDatabase("QSQLITE");
            my_db.setDatabaseName(path);

            if (my_db.open()) {
                is_connected = true;
                db_path = path;
                qDebug() << "success DB connection.\n";
            }
            else {
                is_connected = false;
                qDebug() << "fail DB connection.\n";
            }
        }

        return is_connected;
    }

    bool Connected() { return is_connected; }

    QStringList tables() { return my_db.tables(); }

    void exec(const QString& q)
    {
        QSqlQuery query(q, my_db);
    }

    void exec(const QString& q, QVariantList& data)
    {
        data.clear();

        QSqlQuery query(q, my_db);
        while (query.next()) {
            QSqlRecord record = query.record();
            int count = record.count();
            QVariantMap map;
            for (int i = 0; i < count; ++i) {
                map[record.field(i).name()] = record.value(i);
            }
            data.push_back(map);
        }
    }

private:
    QSqlDatabase my_db;
    bool is_connected = false;
    QString db_path = "";
};
