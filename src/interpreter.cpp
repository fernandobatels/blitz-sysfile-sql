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

using namespace std;
using namespace blitzsql::statement;
using namespace blitzsql::result;

void Interpreter::input(string sql)
{
    this->sql = sql;
}

void Interpreter::prepare()
{
    if (this->sql.find("select") == 0) {
        
        this->isSelect = true;

        /**
         * Cols/data we look for
         */
        stringstream ss(this->sql.substr(7, this->sql.find(" from ") - 7));
        string item;
        this->cols = {};
    
        while (getline(ss, item, ',')) {
            this->cols.push_back(item);
        }

        // The table/folder
        this->folder = this->sql.substr(this->sql.find(" from ") + 6);
    
        if ((this->folder.find_last_of("/") + 1) != this->folder.size()) {
            this->folder += "/";
        }
    }
}

void Interpreter::run()
{
    if (this->isSelect) {

        DIR *dir;

        struct dirent *f;
        dir = opendir(this->folder.c_str());
    
        if (dir != NULL) {
            
            this->dataGroupResult = new DataGroup();

            bool useName = find(this->cols.begin(), this->cols.end(), "name") != this->cols.end();
            bool useSize = find(this->cols.begin(), this->cols.end(), "size") != this->cols.end();


            while (f = readdir(dir)) {

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

        }

        closedir(dir);
    }


}


Status* Interpreter::getResultStatus() 
{
    return this->statusResult;
}

DataGroup* Interpreter::getResultDataGroup()
{
    return this->dataGroupResult;
}
