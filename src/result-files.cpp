/**
 * Blitz SysFile SQL
 *
 * Model to resulted files
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "result-files.h"
#include "result-file.h"
#include <string>
#include <vector>

using namespace std;
using namespace blitzsql::result;

Files::Files()
{
    this->files = {};
}

void Files::add(File* file)
{
    this->files.push_back(file);
}

vector<File*> Files::getFiles()
{
    return this->files;
}

