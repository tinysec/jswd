
const jswd = require("jswd");

const dbgeng = require("dbgeng");

const fmt = require("fmt");



function main(argv)
{
	//debugger;
	
	// let reg = jswd.findRegister('es');

	fmt.printf( jswd.enumRegister() );

    return 0;
}
exports.main = main;

