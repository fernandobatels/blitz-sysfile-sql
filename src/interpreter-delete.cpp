/**
 * Blitz SysFile SQL
 *
 * Class to run delete
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "interpreter-delete.h"
#include "interpreter.h"
#include "result-status.h"
#include "interpreter-condition.h"
#include "interpreter-command.h"
#include <string>
#include <fstream>
#include "result-data.h"
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <UnitTest++/UnitTest++.h>

using namespace std;
using namespace blitzsql::statement;
using namespace blitzsql::result;
using namespace boost::algorithm;
using namespace boost::filesystem;


Delete::Delete()
{
    this->folder = "";
}

bool Delete::prepare()
{

    string sql = this->getSql();

    //Where
    if (icontains(sql, " where ")) {

        string where = sql.substr(ifind_first(sql, " where ").begin() - sql.begin() + 7);

        //In the moment only work with one condition :(

        string colW = where.substr(0, where.find("="));
        replace_all(colW, "'", "");
        trim(colW);

        string valW = where.substr(where.find("=") + 1);
        replace_all(valW, "'", "");
        trim(valW);

        vector<Condition*> whereConditions = {};
        whereConditions.push_back(new Condition(colW, valW));
        this->setWhere(whereConditions);

        ireplace_all(sql, " where " + where, "");

    }

    // The table/folder
    this->folder = sql.substr(sql.find(" from ") + 6);

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

bool Delete::execute()
{
    path p(this->folder);

    if (!exists(p)) {
        this->setStatus(new Status(false, "Folder not exists!"));
        return false;
    }

    if (!is_directory(p)) {
        this->setStatus(new Status(false, "Folder is not a directory!"));
        return false;
    }

    //With where
    if (this->getWhere().size() > 0) {

        for (directory_entry& f: directory_iterator(p)) {

            bool canContinue = true;

            for (Condition *condition : this->getWhere()) {

                //Yes, this work only with name file/folder
                if (condition->getCol() == "name") {
                    if (condition->check(f.path().filename().generic_string())) {
                        canContinue = false;
                        break;
                    }
                }

            }

            if (canContinue)
                continue;

            remove(f);
        }

    } else {

        for (directory_entry& f: directory_iterator(p)) {
           remove(f);
        }

    }

    this->setStatus(new Status(true, "Delete executed with success!"));
    return true;
}

/**
 * Simple deletes
 */
TEST(InterpreterSimpleDelete)
{

    remove("/tmp/cleanthis");
    create_directory("/tmp/cleanthis");

    std::fstream newFile("/tmp/cleanthis/a.txt", ios_base::out);
    newFile << "1234";
    newFile.close();

    newFile = std::fstream("/tmp/cleanthis/b.txt", ios_base::out);
    newFile << "1234";
    newFile.close();

    Interpreter interpreter;

    interpreter.input("delete from /tmp/cleanthis");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(!exists(path("/tmp/cleanthis/a.txt")));
    CHECK(!exists(path("/tmp/cleanthis/b.txt")));
}

/**
 * Delete with where
 */
TEST(InterpreterWhereDelete)
{
    std::fstream newFile("/tmp/testd.txt", ios_base::out);
    newFile << "1234";
    newFile.close();

    Interpreter interpreter;

    interpreter.input("delete from '/tmp' where name = 'testd.txt'");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(!exists(path("/tmp/testd.txt")));
}

