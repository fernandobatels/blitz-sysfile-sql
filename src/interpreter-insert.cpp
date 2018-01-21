/**
 * Blitz SysFile SQL
 *
 * Class to run insert
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "interpreter-insert.h"
#include "interpreter.h"
#include "result-status.h"
#include "interpreter-command.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <UnitTest++/UnitTest++.h>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace blitzsql::statement;
using namespace blitzsql::result;
using namespace boost::algorithm;
using namespace boost::filesystem;

bool Insert::prepare()
{

    string sql = this->getSql();

    // Cols
    int posStartCols = sql.find_first_of('(') + 1;
    stringstream ss(sql.substr(posStartCols, sql.find_first_of(')') - posStartCols));
    string item;
    int lineIndex = 0;
    bool withCols = false;
    int lineIndexColName = -1;
    int lineIndexColContent = -1;


    while (getline(ss, item, ',')) {
        trim(item);

        if (item == "name")
            lineIndexColName = lineIndex;

        if (item == "content")
            lineIndexColContent = lineIndex;

        withCols = true;
        lineIndex += 1;
    }

    if (!withCols) {
        this->setStatus(new Status(false, "No columns detecteds!"));
        return false;
    }

    if (lineIndexColName == -1) {
        this->setStatus(new Status(false, "Col name not detected!"));
        return false;
    }

    // Values
    int posStartVals = sql.find_last_of('(') + 1;
    bool withVals = false;
    ss = stringstream(sql.substr(posStartVals, sql.find_last_of(')') - posStartVals));
    lineIndex = 0;

    while (getline(ss, item, ',')) {
        replace_all(item, "'", "");
        trim(item);

        if (lineIndex == lineIndexColName)
            this->name = item;

        if (lineIndex == lineIndexColContent)
            this->content = item;

        withVals = true;
        lineIndex += 1;
    }

    if (!withVals) {
        this->setStatus(new Status(false, "No values detecteds!"));
        return false;
    }

    // The table/folder
    int posInto = ifind_first(sql, " into ").begin() - sql.begin() + 6;

    this->folder = sql.substr(posInto, sql.find_first_of('(') - posInto);

    replace_all(this->folder, "'", "");

    if (this->folder == "") {
        this->setStatus(new Status(false, "No folder detecteds!"));
        return false;
    }

    if ((this->folder.find_last_of("/") + 1) != this->folder.size()) {
        this->folder += "/";
    }

    return true;
}

bool Insert::execute()
{

    if (!exists(this->folder)) {
        this->setStatus(new Status(false, "Destination folder no exists!"));
        return false;
    }

    if (!is_directory(this->folder)) {
        this->setStatus(new Status(false, "Destination folder is a file!"));
        return false;
    }

    if (exists(this->folder + this->name)) {
        this->setStatus(new Status(false, "File exists on destination folder!!"));
        return false;
    }

    std::fstream newFile(this->folder + this->name, ios_base::out);
    newFile << this->content;
    newFile.close();

    this->setStatus(new Status(true, "Insert executed with success"));

    return true;
}

/**
 * Insert without content
 */
TEST(InterpreterInsertWithoutContent)
{
    remove("/tmp/test-insert.txt");

    Interpreter interpreter;

    interpreter.input("insert into '/tmp'(name) values ('test-insert.txt')");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());
    CHECK(interpreter.getResultStatus()->isSuccess());

    // Duplicated file
    interpreter.input("insert into '/tmp'(name) values ('test-insert.txt')");
    CHECK(interpreter.prepare());
    CHECK(!interpreter.run());
    CHECK(!interpreter.getResultStatus()->isSuccess());

}

/**
 * Insert with null content
 */
TEST(InterpreterInsertWithNullContent)
{
    remove("/tmp/test-insert-null.txt");

    Interpreter interpreter;

    interpreter.input("insert into '/tmp'(name, content) values ('test-insert-null.txt', null)");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());
    CHECK(interpreter.getResultStatus()->isSuccess());

}

/**
 * Insert with content
 */
TEST(InterpreterInsertWithContent)
{
    remove("/tmp/test-insert-content.txt");

    Interpreter interpreter;

    interpreter.input("insert into '/tmp'(name, content) values ('test-insert-content.txt', 'Hello')");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());
    CHECK(interpreter.getResultStatus()->isSuccess());

}


/**
 * Insert without valid folder
 */
TEST(InterpreterInsertWithoutValidDestinationFolder)
{
    Interpreter interpreter;

    interpreter.input("insert into '/tmp/not-exist-folder'(name) values ('test-insert.txt')");
    CHECK(interpreter.prepare());
    CHECK(!interpreter.run());
    CHECK(!interpreter.getResultStatus()->isSuccess());

    interpreter.input("insert into '/tmp/test.txt'(name) values ('test-insert.txt')");
    CHECK(interpreter.prepare());
    CHECK(!interpreter.run());
    CHECK(!interpreter.getResultStatus()->isSuccess());
}
