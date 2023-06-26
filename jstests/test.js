
const assert = require("assert");

const jswd = require("jswd");

const dbgeng = require("dbgeng");

const fmt = require("fmt");

const typing = require("typing");

function main(argv)
{
    let gdtr = jswd.readReg('gdtr');

    let gdtl = jswd.readReg('gdtl');

    fmt.printf('gdtr = 0x%X\n' , gdtr);

    fmt.printf('gdtl = 0x%X\n' , gdtl);

    return 0;
}
exports.main = main;

