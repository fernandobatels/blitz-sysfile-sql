/**
 * Blitz SysFile SQL
 *
 * Model to result status
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "result-status.h"
#include <string>
#include <UnitTest++/UnitTest++.h>

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

TEST(Status)
{

 
    blitzsql::result::Status st = blitzsql::result::Status(true, "Test message");

    CHECK_EQUAL(true, st.isSuccess());
    CHECK_EQUAL("Test message", st.getMessage());


}


