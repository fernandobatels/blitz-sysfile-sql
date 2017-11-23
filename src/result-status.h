/**
* Blitz SysFile SQL
*
* Model to result status
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __resultstatus_h__
#define __resultstatus_h__

#include <string>

using namespace std;

namespace blitzsql {

    namespace result {

        class Status{
            private:
                string message;
                bool success;
            public: 
                Status(bool isSuccess, string message);
                /**
                 * Return if result is success
                 */
                bool isSuccess();
                /**
                 * Return status message
                 */
                string getMessage();

        };

    };
};

#endif
