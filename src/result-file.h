/**
* Blitz SysFile SQL
*
* Model to result file
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __resultfile_h__
#define __resultfile_h__

#include <string>

using namespace std;

namespace blitzsql {

    namespace result {

        class File {
            private:
                string name;
                string content;
            public: 
                File(string name, string content);
                File(string name);
                /**
                 * Return name of file
                 */
                string getName();
                /**
                 * Return content of file
                 */
                string getContent();

        };

    };
};

#endif
