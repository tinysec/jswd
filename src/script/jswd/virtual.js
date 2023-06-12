const _ = require('underscore');

const typing = require("typing");

const dbgeng = require("dbgeng");

const readerExports = require('jswd/reader');

let name = '';

let routine = null;


class Reader
{
    constructor() {


    }

    read(address , buffer)
    {
        return dbgeng.readVirtual(address , buffer);
    }
}

let virtualReader = new Reader();

for ( name  in  readerExports )
{
    routine = readerExports[name];

    if ( typing.isFunction(routine) )
    {
        exports[name] = routine.bind(this , virtualReader);
    }


}

