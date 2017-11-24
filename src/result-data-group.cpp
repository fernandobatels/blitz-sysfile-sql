/**
 * Blitz SysFile SQL
 *
 * Model to resulted data
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "result-data-group.h"
#include "result-data.h"
#include <string>
#include <vector>

using namespace std;
using namespace blitzsql::result;

DataGroup::DataGroup()
{
    this->results = {};
}

void DataGroup::add(Data* data)
{
    this->results.push_back(data);
}

vector<Data*> DataGroup::getResult()
{
    return this->results;
}

