const jswd = require("jswd");

const dbgeng = require("dbgeng");

const fmt = require("fmt");

class Processor
{

	constructor(id)
	{
		this.id = id;

		this.registers = [];
	}
}


function enumProcessor()
{
	let count = dbgeng.getNumberProcessors();

	let i = 0;

	let processor = null;

	let oldTid = dbgeng.getCurrentThreadId();

	let tid = 0;

	let processors = [];

	for ( i = 0; i < count; i++ )
	{
		processor = new Processor(i);

		tid = dbgeng.getThreadIdByProcessor(i);

		dbgeng.setCurrentThreadId(tid);

		processor.registers = jswd.enumRegister();

		processors.push( processor );
	}

	dbgeng.setCurrentThreadId(oldTid);

	return processors;
}

function main(argv)
{
	let processors =   enumProcessor();

	let i = 0;

	for ( i = 0; i < processors.length; i++ )
	{
		fmt.printf(processors[i]);
	}

    return 0;
}
exports.main = main;

