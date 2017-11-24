/**
* Blitz SysFile SQL
*
* Model to result data
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __resultdata_h__
#define __resultdata_h__

#include <string>
#include <map>

using namespace std;

namespace blitzsql {

    namespace result {

        class Data {
            private:
                map<string, string> cols;
            public: 
                Data();
                /**
                 * Put val on result
                 */
                void put(string col, string val);
                /**
                 * Return val of col
                 */
                string get(string col);
        };

    };
};

#endif
