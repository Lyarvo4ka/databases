#include <QCoreApplication>

#include "sqlquery.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MSSQLDB sourceDB;
    if (!sourceDB.connect("WIN-BD5OT7T92EA\\MSSQL_2008", "db2010", "sa", "Admin123"))
    {
        auto errText = sourceDB.lastError().text().toStdWString();
    }
    else
        qDebug() << "db2010 Connect OK";

    MSSQLDB targetDB;
    if (!targetDB.connect("WIN-BD5OT7T92EA\\MSSQL_2008", "db2010_backup", "sa", "Admin123"))
    {
        auto errText = targetDB.lastError().text().toStdWString();
    }
    else
        qDebug() << "db2010_backup Connect OK";

    return a.exec();
}
