/**
* Blitz SysFile SQL
*
* Model to resulted files
*
* @author Fernando Batels <luisfbatels@gmail.com>
*/

#ifndef __resultfiles_h__
#define __resultfiles_h__

#include <string>
#include <vector>
#include "result-file.h"

using namespace std;

namespace blitzsql {

    namespace result {

        class Files {
            private:
                vector<File*> files;
            public: 
                Files();
                /**
                 * Add new file do result
                 */
                void add(File* file);
                /**
                 * Ger file resulteds
                 */
                vector<File*> getFiles();

        };

    };
};

#endif
