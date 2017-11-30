/**
* Blitz SysFile SQL
*
* Class to run commans from cli
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __run_h__
#define __run_h__

#include <string>

using namespace std;

namespace blitzsql {

    class Run {
        public: 
            /**
             * Execute command and show on output the results
             */
            bool execute(string sql);

    };

};

#endif
