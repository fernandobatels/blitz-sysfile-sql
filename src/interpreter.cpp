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
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>

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

    trim(this->sql);

    if ((ifind_first(this->sql, "select").begin() - this->sql.begin()) == 0) {
        
        this->isSelect = true;

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
            
            this->dataGroupResult = new DataGroup();

            bool useName = find(this->cols.begin(), this->cols.end(), "name") != this->cols.end();
            bool useSize = find(this->cols.begin(), this->cols.end(), "size") != this->cols.end();


            while ((f = readdir(dir)) != NULL) {

                Data* tmp = new Data();

                if (useName) 
                    tmp->put("name", f->d_name);

                if (useSize) {
                    ifstream in(this->folder + f->d_name, ifstream::binary | ifstream::ate );
                    tmp->put("size", to_string(in.tellg()));
                    in.close();
                } 
                this->dataGroupResult->add(tmp);
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

TEST(Interpreter)
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
