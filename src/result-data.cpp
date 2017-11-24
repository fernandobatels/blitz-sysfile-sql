/**
 * Blitz SysFile SQL
 *
 * Model to result data
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "result-data.h"
#include <string>

using namespace std;
using namespace blitzsql::result;

Data::Data()
{
    this->cols = {};
}

string Data::get(string col)
{
    return this->cols[col];
}

void Data::put(string col, string val)
{
    this->cols.insert(pair<string, string>(col, val));
}

