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
#include "interpreter-condition.h"
#include "interpreter-command.h"

using namespace std;
using namespace blitzsql::result;

namespace blitzsql {

    namespace statement {

        class Interpreter {
            private:
                string sql;
                bool isSelect;
                BaseCommand* command;
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
                /**
                 * Return if is insert
                 */
                bool isCommandSelect();

        };

    };
};

#endif
