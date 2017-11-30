/**
* Blitz SysFile SQL
*
* Model to resulted data
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __resultdatagroup_h__
#define __resultdatagroup_h__

#include <string>
#include <vector>
#include "result-data.h"

using namespace std;

namespace blitzsql {

    namespace result {

        class DataGroup {
            private:
                vector<Data*> results;
                vector<string> colsNames;
            public: 
                DataGroup(vector<string> colsNames);
                /**
                 * Add new data do result
                 */
                void add(Data* data);
                /**
                 * Get data resulteds
                 */
                vector<Data*> getResult();
                /**
                 * Get collumns names
                 */
                vector<string> getColsNames();
        };

    };
};

#endif
