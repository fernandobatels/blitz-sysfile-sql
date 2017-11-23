/**
 * Blitz SysFile SQL
 *
 * Model to result file
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "result-file.h"
#include <string>

using namespace std;
using namespace blitzsql::result;

File::File(string name, string content)
{
    this->name = name;
    this->content = content;
}

File::File(string name)
{
    this->name = name;
}

string File::getName()
{
    return this->name;
}

string File::getContent()
{
    return this->content;
}

