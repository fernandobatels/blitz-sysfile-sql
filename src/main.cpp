/**
 * Blitz SysFile SQL
 *
 * Main/Index file of server
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include <string.h>
#include <UnitTest++/UnitTest++.h>
#include "run.h"

using namespace std;

int main(int argc, char ** argv)
{
    
    if (argc > 1) {
        
        if (strcmp(argv[1], "-t") == 0) {
            return UnitTest::RunAllTests();
        }
        
        if (strcmp(argv[1], "-r") == 0 && argc > 2) {
            
            blitzsql::Run run = blitzsql::Run();

            return run.execute(argv[2]) ? 0 : 1;
        }

    }

}

TEST(Sanity)
{
    CHECK_EQUAL(1, 1);
}
