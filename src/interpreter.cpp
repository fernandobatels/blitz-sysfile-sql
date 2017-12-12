/**
 * Blitz SysFile SQL
 *
 * Interpreter of comands
 *
 * @author Fernando Batels <luisfbatels@gmail.com>
 */

#include "interpreter.h"
#include "interpreter-command.h"
#include "interpreter-select.h"
#include "interpreter-insert.h"
#include <string>
#include <iostream>
#include "result-data-group.h"
#include "result-status.h"
#include <UnitTest++/UnitTest++.h>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;
using namespace blitzsql::statement;
using namespace blitzsql::result;
using namespace boost::algorithm;

void Interpreter::input(string sql)
{
    this->sql = sql;
}

bool Interpreter::prepare()
{
    //Reset all atributes
    this->isSelect = false;

    trim(this->sql);

    /**
     * If start with 'select' is a select :)
     */
    if (istarts_with(this->sql, "select ")) {
        
        this->isSelect = true;

        this->command = new Select();
    
    } else if (istarts_with(this->sql, "insert ")) {
        
        this->command = new Insert();

    }
    
    this->command->setSql(this->sql);

    return this->command->prepare();
}

bool Interpreter::run()
{
    return this->command->execute();
}

Status* Interpreter::getResultStatus() 
{
    return this->command->getStatus();
}

DataGroup* Interpreter::getResultDataGroup()
{
    if (this->isSelect) {
        return ((Select*) this->command)->getData();
    }
    
    return {};
}



/**
 * Simple selects
 */
TEST(InterpreterSimpleSelect)
{
    Interpreter interpreter;

    interpreter.input("select name,size from /tmp");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("name").empty());
    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("size").empty());

    interpreter.input("SELECT name, size from /tmp");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("name").empty());
    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("size").empty());
    
    interpreter.input(" select name,  size from '/tmp'");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("name").empty());
    CHECK(!interpreter.getResultDataGroup()->getResult()[0]->get("size").empty());
}

/**
 * Select with limit rows
 */
TEST(InterpreterLimitRowsSelect)
{
    Interpreter interpreter;

    interpreter.input("select first 2 name from '/tmp'");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(interpreter.getResultDataGroup()->getResult().size() == 2);
}

/**
 * Select with where
 */
TEST(InterpreterWhereSelect)
{
    Interpreter interpreter;

    interpreter.input("select name, size from '/tmp' where name = 'test.txt'");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(interpreter.getResultDataGroup()->getResult().size() == 1);
    CHECK(interpreter.getResultDataGroup()->getResult()[0]->get("size") == "4");
}

/**
 * Insert without content
 */
TEST(InterpreterInsertWithoutContent)
{
    Interpreter interpreter;

    interpreter.input("insert into '/tmp'(name) values ('test-insert.txt')");
    CHECK(interpreter.prepare());
    CHECK(interpreter.run());

    CHECK(interpreter.getResultStatus()->isSuccess());
}
