/**
* Blitz SysFile SQL
*
* Base class to commands like insert, update, delete and select
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __interpreter_command_h__
#define __interpreter_command_h__

#include <string>
#include <vector>
#include "result-status.h"
#include "interpreter-condition.h"

using namespace std;
using namespace blitzsql::result;

namespace blitzsql {

    namespace statement {

        class BaseCommand {
            private:
                string sql;
                Status *statusResult;
                vector<Condition*> whereConditions;
            protected:
               /**
                 * Get sql 
                 */
                string getSql();
                /**
                 * Set status result
                 */
                void setStatus(Status *result);
                /**
                 * Set where condition used
                 */
                void setWhere(vector<Condition*> where);
                /**
                 * Set where condition used
                 */
                vector<Condition*> getWhere(); 
        public:
                /**
                 * Set sql to prepare and execute
                 */
                void setSql(string sql);
                /**
                 * Get status result
                 */
                Status *getStatus();
                /**
                 * Prepare statement
                 */
                virtual bool prepare() = 0;
                /**
                 * Execute prepared statement
                 */
                virtual bool execute() = 0;
                
        };

    };
};

#endif
