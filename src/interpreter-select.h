/**
* Blitz SysFile SQL
*
* Class to run select
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __interpreter_select_h__
#define __interpreter_select_h__

#include <string>
#include <vector>
#include "result-data-group.h"
#include "result-status.h"
#include "interpreter-condition.h"
#include "interpreter-command.h"

using namespace std;

namespace blitzsql {

    namespace statement {

        class Select: public BaseCommand {
            private:
                vector<string> cols; 
                string folder;
                int limitRows;
                DataGroup *dataGroupResult;
            public:
                Select();
                bool prepare();
                bool execute();
                /**
                 * Get rows resulteds
                 */
                DataGroup *getData();
        };

    };
};

#endif
