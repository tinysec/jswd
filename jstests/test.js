
const assert = require("assert");

const jswd = require("jswd");

const dbgeng = require("dbgeng");

const fmt = require("fmt");

const typing = require("typing");


function main(argv)
{
    fmt.printf( jswd.fieldOffset('_UNICODE_STRING' , 'Buffer') );


    return 0;
}
exports.main = main;

