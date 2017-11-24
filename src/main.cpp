/**
 * Blitz SysFile SQL
 *
 * Main/Index file of server
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include <string.h>
#include <UnitTest++/UnitTest++.h>

using namespace std;

TEST(Sanity)
{
    CHECK_EQUAL(1, 1);
}


int main(int argc, char ** argv)
{
    
    if (argc > 1) {
        if (strcmp(argv[1], "-t") == 0) {
            return UnitTest::RunAllTests();
        }
    }

}
