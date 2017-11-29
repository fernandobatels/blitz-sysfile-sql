/**
 * Blitz SysFile SQL
 *
 * Model to conditions of where
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "interpreter-condition.h"
#include <string>

using namespace std;
using namespace blitzsql::statement;

Condition::Condition(string col, string val)
{
    this->col = col;
    this->val = val;
    this->isEqual = true;//Default
}

string Condition::getCol()
{
    return this->col;
}

bool Condition::check(string valToCheck)
{

    if (this->isEqual) {
        if (this->val == valToCheck) {
            return true;
        }
    }

    return false;
}
