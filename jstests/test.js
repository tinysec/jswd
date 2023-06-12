const fmt = require("fmt");

const jswd = require("jswd");

const _ = require('underscore');

let int = require('integer').Uint64;

/**
 *
 * @param {Array<String>} argv
 */
function main(argv)
{
    fmt.printf("argv[0] is %s\n", argv[0]);

    fmt.printf( 'sizeof(nt!_UNICODE_STRING): %d\n' , jswd.sizeof('nt!_UNICODE_STRING') );

    fmt.printf( 'fieldOffset(nt!_UNICODE_STRING , Buffer): %d\n' , jswd.fieldOffset('nt!_UNICODE_STRING' , 'Buffer') );


    return 0;
}
exports.main = main;

