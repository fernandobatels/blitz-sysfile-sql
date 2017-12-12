/**
 * Blitz SysFile SQL
 *
 * Class to run insert
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "interpreter-insert.h"
#include "result-status.h"
#include "interpreter-command.h"
#include <string>
#include <iostream>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/find.hpp>

using namespace std;
using namespace blitzsql::statement;
using namespace blitzsql::result;
using namespace boost::algorithm;

Insert::Insert()
{
    this->cols = {};
    this->folder = "";
}

bool Insert::prepare()
{
    
    string sql = this->getSql();
   



 
    // The table/folder
    int posInto = ifind_first(sql, " into ").begin() - sql.begin() + 6;

    this->folder = sql.substr(posInto, sql.find_first_of('(') - posInto);

    replace_all(this->folder, "'", "");

    if (this->folder == "") 
        return false;

    if ((this->folder.find_last_of("/") + 1) != this->folder.size()) {
        this->folder += "/";
    }

    this->setSql(sql);

    return true;
}

bool Insert::execute()
{


    return false;
}
