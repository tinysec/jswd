
const assert = require("assert");

const jswd = require("jswd");

const dbgeng = require("dbgeng");

const fmt = require("fmt");

const typing = require("typing");


function main(argv)
{
    //fmt.printf( getSegment('fs') );

    fmt.printf( '0x%X' , jswd.getSegment('es') );

    return 0;
}
exports.main = main;

