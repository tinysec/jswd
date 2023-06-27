const _ = require('underscore');

const typing = require("typing");

const dbgeng = require("dbgeng");

const readerExports = require('jswd/reader');

const writerExports = require('jswd/writer');


class Reader
{
    constructor()
    {

    }

    read(address , buffer)
    {
        return dbgeng.readVirtual(address , buffer);
    }
}

class Writer
{
    constructor()
    {

    }

    write(address , buffer)
    {
        return dbgeng.writeVirtual(address , buffer);
    }
}


let name = '';

let routine = null;

let reader = new Reader();

let writer = new Writer();

// for reader
for ( name  in  readerExports )
{
    routine = readerExports[name];

    if ( typing.isFunction(routine) )
    {
        exports[name] = routine.bind(this , reader);
    }
}

// for writer
for ( name  in  writerExports )
{
    routine = writerExports[name];

    if ( typing.isFunction(routine) )
    {
        exports[name] = routine.bind(this , writer);
    }
}