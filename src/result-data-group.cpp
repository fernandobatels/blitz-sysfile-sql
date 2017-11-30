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
#include <UnitTest++/UnitTest++.h>

using namespace std;
using namespace blitzsql::result;

DataGroup::DataGroup(vector<string> colsNames)
{
    this->results = {};
    this->colsNames = colsNames;
}

void DataGroup::add(Data* data)
{
    this->results.push_back(data);
}

vector<string> DataGroup::getColsNames()
{
    return this->colsNames;
}

vector<Data*> DataGroup::getResult()
{
    return this->results;
}

TEST(DataGroup)
{
    DataGroup fis = DataGroup({"name", "content"});
   
    Data fiTmp = Data();
    fiTmp.put("name", "test.txt");
    fiTmp.put("content", "This is a content");
    fis.add(&fiTmp);

    Data fiTmp2 = Data();
    fiTmp2.put("name", "test2.txt");
    fis.add(&fiTmp2);
   
   
    CHECK_EQUAL("test.txt", fis.getResult()[0]->get("name"));
    CHECK_EQUAL("This is a content", fis.getResult()[0]->get("content"));
  
    CHECK_EQUAL("test2.txt", fis.getResult()[1]->get("name"));
    CHECK_EQUAL("", fis.getResult()[1]->get("content"));

}
