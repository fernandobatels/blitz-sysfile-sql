/**
 * Blitz SysFile SQL
 *
 * Model to result status
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "result-status.h"
#include <string>

using namespace std;
using namespace blitzsql::result;

Status::Status(bool isSuccess, string message)
{
    this->success = isSuccess;
    this->message = message;
}

bool Status::isSuccess()
{
    return this->success;
}

string Status::getMessage()
{
    return this->message;
}

