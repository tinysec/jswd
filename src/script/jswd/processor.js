const dbgeng = require("dbgeng");

const reg = require('jswd/register');

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

		processor.registers = reg.enumRegister();

		processors.push( processor );
	}

	dbgeng.setCurrentThreadId(oldTid);

	return processors;
}
exports.enumProcessor = enumProcessor;


