const jswd = require("jswd");

const dbgeng = require("dbgeng");

const fmt = require("fmt");



function main(argv)
{
	let reg = jswd.findRegister('es');

	fmt.printf(reg);

    return 0;
}
exports.main = main;

