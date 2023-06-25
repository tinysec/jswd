const jswd = require("jswd");

const dbgeng = require("dbgeng");

const fmt = require("fmt");



function main(argv)
{
	let processors =   jswd.enumProcessor();

	let i = 0;

	for ( i = 0; i < processors.length; i++ )
	{
		fmt.printf(processors[i]);
	}

    return 0;
}
exports.main = main;

