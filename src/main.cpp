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
#include "result-file.h"
#include "result-files.h"
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

    result::Files fis = result::Files();

    fis.add(new result::File("test.txt", "This is a content"));
    fis.add(new result::File("test2.txt"));

    for (result::File* fi : fis.getFiles()) {
        cout << fi->getName() << ": " << fi->getContent() << endl;
    }

    statement::Interpreter interpreter;

    interpreter.input("select name, content from /tmp");
    interpreter.prepare();
    interpreter.run();

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
