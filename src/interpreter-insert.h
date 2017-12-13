/**
* Blitz SysFile SQL
*
* Class to run insert
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __interpreter_insert_h__
#define __interpreter_insert_h__

#include <string>
#include "result-status.h"
#include "interpreter-command.h"

using namespace std;

namespace blitzsql {

    namespace statement {

        class Insert: public BaseCommand {
            private:
                string valName; 
                string folder;
            public:
                bool prepare();
                bool execute();
        };

    };
};

#endif
