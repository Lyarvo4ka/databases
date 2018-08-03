#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "../databaselib/sqlquery.h"

using namespace testing;

TEST(sqlquery, testDropTable)
{
    auto actual = createQueryDropTable("table_name");
    QString expected = "if exists(select *	from sys.tables	where name = \'table_name\'and schema_id = schema_id(\'dbo\')) begin drop table dbo.table_name end";

    ASSERT_STREQ(expected.toStdString().c_str(), actual.toStdString().c_str());
    auto wrong_string = createQueryDropTable("wrong_name");
    ASSERT_STRNE(expected.toStdString().c_str(), wrong_string.toStdString().c_str());

}


TEST(sqlquery, testCopyTable)
{
    QString sourceTable = "source_table";
    QString targetTable = "target_table";
    auto actual = createCopyTableQuery(sourceTable,targetTable);

    QString expected = "SELECT * INTO target_table.dbo.v8users FROM source_table.dbo.v8users";

    ASSERT_STREQ(expected.toStdString().c_str(), actual.toStdString().c_str());
}
