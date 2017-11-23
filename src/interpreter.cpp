/**
 * Blitz SysFile SQL
 *
* Interpreter of comands
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "interpreter.h"
#include <string>

using namespace std;
using namespace blitzsql::statement;

void Interpreter::input(string sql)
{
    this->sql = sql;
}

void Interpreter::prepare()
{

}

void Interpreter::run()
{

}
