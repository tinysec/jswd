const fmt = require("fmt");


const jswd = require("jswd");

fmt.printf( "execute: %s\n" , jswd.execute("!dt -h") );



/**
 *
 * @param {Array<String>} argv
 */
function main(argv)
{
    fmt.printf("[+] i am from jswd!\n");

    fmt.printf("argv[0] is %s\n", argv[0]);

    return 0;
}
exports.main = main;

