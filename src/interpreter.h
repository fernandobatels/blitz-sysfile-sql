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
#include <vector>
#include "result-data-group.h"
#include "result-status.h"

using namespace std;
using namespace blitzsql::result;

namespace blitzsql {

    namespace statement {

        class Interpreter {
            private:
                string sql;
                vector<string> cols; 
                string folder;
                bool isSelect;
                DataGroup *dataGroupResult;
                Status *statusResult;
            public: 
                /**
                 * Input sql to interpreter
                 */
                void input(string sql);
                /**
                 * Prepare the sql
                 */
                bool prepare();
                /**
                 * Run sql
                 */
                bool run();
                /**
                 * Get status result
                 */
                Status* getResultStatus();
                /**
                 * Get data group result
                 */
                DataGroup* getResultDataGroup();
                
        };

    };
};

#endif
