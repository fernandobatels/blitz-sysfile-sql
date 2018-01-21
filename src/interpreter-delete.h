/**
* Blitz SysFile SQL
*
* Class to run delete
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __interpreter_delete_h__
#define __interpreter_delete_h__

#include <string>
#include <vector>
#include "result-status.h"
#include "interpreter-condition.h"
#include "interpreter-command.h"

using namespace std;

namespace blitzsql {

    namespace statement {

        class Delete: public BaseCommand {
            private:
                string folder;
            public:
                Delete();
                bool prepare();
                bool execute();
        };

    };
};

#endif
