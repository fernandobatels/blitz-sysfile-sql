/**
* Blitz SysFile SQL
*
* Interpreter of comands
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __interpreter_h__
#define __interpreter_h__

#include <string>

using namespace std;

namespace blitzsql {

    namespace statement {

        class Interpreter {
            private:
                string sql;
            public: 
                /**
                 * Input sql to interpreter
                 */
                void input(string sql);
                /**
                 * Prepare the sql
                 */
                void prepare();
                /**
                 * Run sql
                 */
                void run();

                
        };

    };
};

#endif
