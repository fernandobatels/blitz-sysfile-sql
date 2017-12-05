/**
 * Blitz SysFile SQL
 *
 * Base class to commands like insert, update, delete and select
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */
#include <string>
#include <vector>
#include "result-status.h"
#include "interpreter-condition.h"
#include "interpreter-command.h"

using namespace std;
using namespace blitzsql::statement;

void BaseCommand::setSql(string sql) 
{
    this->sql = sql;
}

string BaseCommand::getSql()
{
    return this->sql;
}

void BaseCommand::setStatus(Status* st)
{
    this->statusResult = st;
}

Status* BaseCommand::getStatus()
{
    return this->statusResult;
}

void BaseCommand::setWhere(vector<Condition*> where)
{
    this->whereConditions = where;
}

vector<Condition*> BaseCommand::getWhere()
{
    return this->whereConditions;
}
