/**
 * Blitz SysFile SQL
 *
 * Class to run select
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "interpreter-select.h"
#include "result-data-group.h"
#include "result-status.h"
#include "interpreter-condition.h"
#include "interpreter-command.h"
#include <string>
#include <sstream>
#include <dirent.h>
#include "result-data.h"
#include <algorithm>
#include <fstream>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/find.hpp>


using namespace std;
using namespace blitzsql::statement;
using namespace blitzsql::result;
using namespace boost::algorithm;


Select::Select()
{
    this->cols = {};
    this->folder = "";
    this->limitRows = -1;
    this->dataGroupResult = {};
}

DataGroup *Select::getData()
{
    return this->dataGroupResult;
}

bool Select::prepare()
{
 
    string sql = this->getSql();
    
    /**
     * Limit of data
     */
    if (icontains(sql, " first ")) {
        vector<string> first;

        split(first, sql, is_any_of(" "));

        if (first.size() < 3) {
            this->setStatus(new Status(false, "No first paramters detecteds!"));
            return false;
        }

        this->limitRows = stoi(first[2]);
    
        ireplace_all(sql, " first " + first[2], "");

        first.clear();
    }

    /**
     * Cols/data we look for
     */
    stringstream ss(sql.substr(7, sql.find(" from ") - 7));
    string item;

    while (getline(ss, item, ',')) {
        trim(item);
        this->cols.push_back(item);
    }

    if (this->cols.size() == 0) { 
        this->setStatus(new Status(false, "No columns detecteds!"));
        return false;
    }

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

bool Select::execute()
{

    DIR *dir;

    struct dirent *f;
    dir = opendir(this->folder.c_str());

    if (dir != NULL) {
        
        this->dataGroupResult = new DataGroup(this->cols);

        bool useName = find(this->cols.begin(), this->cols.end(), "name") != this->cols.end();
        bool useSize = find(this->cols.begin(), this->cols.end(), "size") != this->cols.end();
        bool withWhere = this->getWhere().size() > 0;

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

                for (Condition *condition : this->getWhere()) {
                    
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
    
        this->setStatus(new Status(false, "Select executed with success!"));
        return true;

    }

    closedir(dir);

    this->setStatus(new Status(false, "Problem on open folder"));
    return false;
}
