/**
 * Blitz SysFile SQL
 *
 * Interpreter of comands
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "interpreter.h"
#include <string>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include "result-data-group.h"
#include "result-data.h"
#include "result-status.h"
#include <algorithm>
#include <fstream>
#include <UnitTest++/UnitTest++.h>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/find.hpp>

using namespace std;
using namespace blitzsql::statement;
using namespace blitzsql::result;
using namespace boost::algorithm;

void Interpreter::input(string sql)
{
    this->sql = sql;
}

bool Interpreter::prepare()
{
    //Reset all atributes
    this->isSelect = false;
    this->cols = {};
    this->folder = "";
    this->limitRows = -1;
    this->whereConditions = {};

    trim(this->sql);

    /**
     * If start with 'select' is a select :)
     */
    if (istarts_with(this->sql, "select ")) {
        
        this->isSelect = true;
        
        /**
         * Limit of data
         */
        if (icontains(this->sql, " first ")) {
            vector<string> first;
            
            split(first, this->sql, is_any_of(" "));

            if (first.size() < 3)
                return false;

            this->limitRows = stoi(first[2]);
        
            ireplace_all(this->sql, " first " + first[2], "");

            first.clear();
        }

        /**
         * Cols/data we look for
         */
        stringstream ss(this->sql.substr(7, this->sql.find(" from ") - 7));
        string item;
    
        while (getline(ss, item, ',')) {
            trim(item);
            this->cols.push_back(item);
        }

        if (this->cols.size() == 0) 
            return false;

        //Where
        if (icontains(this->sql, " where ")) {
            
            string where = this->sql.substr(ifind_first(this->sql, " where ").begin() - this->sql.begin() + 7);
            
            //In the moment only work with one condition :(
            
            string colW = where.substr(0, where.find("="));
            replace_all(colW, "'", "");
            trim(colW);

            string valW = where.substr(where.find("=") + 1);
            replace_all(valW, "'", "");
            trim(valW);

            this->whereConditions.push_back(new Condition(colW, valW));

            ireplace_all(this->sql, " where " + where, "");

        }

        // The table/folder
        this->folder = this->sql.substr(this->sql.find(" from ") + 6);

        replace_all(this->folder, "'", "");

        if (this->folder == "") 
            return false;

        if ((this->folder.find_last_of("/") + 1) != this->folder.size()) {
            this->folder += "/";
        }

        return true;
    }

    return false;
}

bool Interpreter::run()
{
    if (this->isSelect) {

        DIR *dir;

        struct dirent *f;
        dir = opendir(this->folder.c_str());
    
        if (dir != NULL) {
            
            this->dataGroupResult = new DataGroup(this->cols);

            bool useName = find(this->cols.begin(), this->cols.end(), "name") != this->cols.end();
            bool useSize = find(this->cols.begin(), this->cols.end(), "size") != this->cols.end();
            bool withWhere = this->whereConditions.size() > 0;
            int numRow = 1;

            while ((f = readdir(dir)) != NULL) {
                
                if (strcmp(f->d_name, ".") == 0|| strcmp(f->d_name, "..") == 0) 
                    continue;

                Data* tmp = new Data();

                if (useName) 
                    tmp->put("name", f->d_name);

                if (useSize) {
                    ifstream in(this->folder + f->d_name, ifstream::binary | ifstream::ate );
                    tmp->put("size", to_string(in.tellg()));
                    in.close();
                } 

                if (withWhere) {
                    bool canContinue = false;
                    
                    for (Condition *condition : this->whereConditions) {
                        if (!condition->check(tmp->get(condition->getCol()))) {
                            canContinue = true;
                            break;
                        }
                    }

                    if (canContinue)
                        continue;
                }

                this->dataGroupResult->add(tmp);

                if (numRow == this->limitRows and this->limitRows > 0)
                    break;

                numRow++;
            }
            
            closedir(dir);
            return true;
        }

        closedir(dir);
    }

    return false;
}

Status* Interpreter::getResultStatus() 
{
    return this->statusResult;
}

DataGroup* Interpreter::getResultDataGroup()
{
    return this->dataGroupResult;
}



/**
 * Simple selects
 */
TEST(InterpreterSimpleSelect)
{
    Interpreter interpreter;

    interpreter.input("select name,size from /tmp");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("name").empty());
    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("size").empty());

    interpreter.input("SELECT name, size from /tmp");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("name").empty());
    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("size").empty());
    
    interpreter.input(" select name,  size from '/tmp'");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("name").empty());
    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("size").empty());
}

/**
 * Select with limit rows
 */
TEST(InterpreterLimitRowsSelect)
{
    Interpreter interpreter;

    interpreter.input("select first 2 name from '/tmp'");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(interpreter.getResultDataGroup()->getResult().size() == 2);
}

/**
 * Select with where
 */
TEST(InterpreterWhereSelect)
{
    Interpreter interpreter;

    interpreter.input("select name, size from '/tmp' where name = 'test.txt'");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(interpreter.getResultDataGroup()->getResult().size() == 1);
    CHECK(interpreter.getResultDataGroup()->getResult()[0]->get("size") == "4");
}
