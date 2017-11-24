/**
 * Blitz SysFile SQL
 *
 * Main/Index file of server
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include <iostream>
#include <string.h>
#include "result-status.h"
#include "result-data.h"
#include "result-data-group.h"
#include "interpreter.h"

using namespace std;
using namespace blitzsql;

/**
 * Simple tests api
 */
void tests() 
{
    
    result::Status st = result::Status(true, "Test message");
    cout << st.isSuccess() << ": " << st.getMessage() << endl;

    result::DataGroup fis = result::DataGroup();
   
    result::Data fiTmp = result::Data();
    fiTmp.put("name", "test.txt");
    fiTmp.put("content", "This is a content");
    fis.add(&fiTmp);

    result::Data fiTmp2 = result::Data();
    fiTmp2.put("name", "test2.txt");
    fis.add(&fiTmp2);
    
    for (result::Data* fi : fis.getResult()) {
        cout << fi->get("name") << ": " << fi->get("content") << endl;
    }

    cout << "Test select:" << endl;

    statement::Interpreter interpreter;

    interpreter.input("select name,size from /tmp");
    interpreter.prepare();
    interpreter.run();

    for (result::Data* fi : interpreter.getResultDataGroup()->getResult()) {
        cout << fi->get("name") << ": " << fi->get("size") << endl;
    }
}

int main(int argc, char ** argv)
{
    
    if (argc > 1) {
        if (strcmp(argv[1], "-t") == 0) {
            cout << "Tests:" << endl;
            tests();
        }
    }

}
