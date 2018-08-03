#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>

#include <qdebug.h>
#include <string>


QString createDropTableQuery(const QString & table_name)
{
   return QString(
                   "if exists"
                   "(select *	from sys.tables	"
                   "where name = \'%1\'and schema_id = schema_id(\'dbo\')) "
                   "begin "
                     "drop table dbo.%1"
                   " end"
                 ).arg(table_name);
    //return 	"if exists(select *	from sys.tables	where name = \'"+ table_name + "\'and schema_id = schema_id(\'dbo\')) begin drop table dbo." + table_name +" end";
}

QString createCopyTableQuery(const QString &soruce_table , const QString &target_table)
{
    return QString("SELECT * INTO %2.dbo.v8users "
                   "FROM %1.dbo.v8users"
                   ).arg(soruce_table , target_table);

}




class MSSQLDB
{
    QSqlDatabase db_;
public:
    MSSQLDB()
    {
    }
    ~MSSQLDB()
    {
        close();
    }
    QStringList getAllTableNames(QSqlDatabase & db)
    {
        QString selectAllTables =
                    "SELECT name "
                    "FROM sys.Tables";

        if ( !db.isOpen())
            return QStringList();

        QStringList tableList;

        auto sql_query = db.exec(selectAllTables);
        while(sql_query.next())
        {
            tableList.append(sql_query.value(0).toString());
        }
        return tableList;
    }
    bool connect(const QString &  host , const QString &  databaseName,
                 const QString &  user,	const QString &  password )
    {
        //QString connectString = "DRIVER = { SQL Server };";
        //connectString.append("SERVERNODE=" + host + ";");
        //connectString.append("UID=" + user + ";");
        //connectString.append("PWD=" + password + ";");

        db_ = QSqlDatabase::addDatabase("QODBC");
        auto driverAndDatabase = QString("Driver={SQL Server};Database=%1;").arg(databaseName);
        db_.setDatabaseName(driverAndDatabase);
        db_.setHostName(host);
        db_.setUserName(user);
        db_.setPassword(password);

        return db_.open();
    }
    QSqlError lastError()
    {
        return db_.lastError();
    }
    void close()
    {
        if (db_.isOpen())
            db_.close();
    }

};



#endif // SQLQUERY_H
