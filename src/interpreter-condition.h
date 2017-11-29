/**
* Blitz SysFile SQL
*
* Model to conditions of where
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __interpreter_condition_h__
#define __interpreter_condition_h__

#include <string>

using namespace std;

namespace blitzsql {

    namespace statement {

        class Condition {
            private:
                string col;
                bool isEqual;
                string val;
            public:
                Condition(string col, string val);
                /**
                 * Return name col
                 */
                string getCol();
                /**
                 * Check if condition is ok
                 */
                bool check(string valToCheck);
        };

    };
};

#endif
