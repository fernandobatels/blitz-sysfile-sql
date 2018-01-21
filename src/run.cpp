/**
 * Blitz SysFile SQL
 *
 * Class to run commans from cli
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "result-status.h"
#include "result-data-group.h"
#include "result-data.h"
#include "interpreter.h"
#include "run.h"
#include <string>
#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace blitzsql::statement;
using namespace blitzsql::result;
using namespace blitzsql;

bool Run::execute(string sql) {

    Interpreter interpreter;

    interpreter.input(sql);

    if (!interpreter.prepare()) {
        cerr << "Fail on prepare" << endl;
        return false;
    }

    if (!interpreter.run()) {
        cerr << "Fail on execute" << endl;
        return false;
    }

    if (interpreter.isCommandSelect()) {
        int colI = 1;
        int colN = interpreter.getResultDataGroup()->getColsNames().size();

        for (string col : interpreter.getResultDataGroup()->getColsNames()) {

            cout << setw(30) << left << col;

            if (colI < colN)
                cout << " | ";

            colI++;
        }

        cout << endl;
        cout << setfill('-') << setw(30 * (colI - 1)) << "";
        cout << setfill(' ') << "" << endl;

        for (Data *data : interpreter.getResultDataGroup()->getResult()) {

            colI = 1;

            for (string col : interpreter.getResultDataGroup()->getColsNames()) {

                cout << setw(30) << left << data->get(col);

                if (colI < colN)
                    cout << " | ";

                colI++;
            }

            cout << endl;
        }

        cout << setfill('-') << setw(30 * (colI - 1)) << "" << endl;
        cout << setfill(' ') << "Rows: " << interpreter.getResultDataGroup()->getResult().size() << endl;
    }

    cout << setfill(' ') << "Status: " << interpreter.getResultStatus()->getMessage() << endl;

    return false;
}
