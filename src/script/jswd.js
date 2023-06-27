const _ = require('underscore');

const dbgeng = require('dbgeng');

let moduleExports = _.extend(
    require('jswd/module'),
    require('jswd/processor'),
    require('jswd/register'),
    require('jswd/segment'),
    require('jswd/symbol'),
    require('jswd/virtual'),
);

moduleExports.physical = require('jswd/physical');


// forward

moduleExports.writeDumpFile = dbgeng.writeDumpFile;

moduleExports.isKernelDebuggerEnabled = dbgeng.isKernelDebuggerEnabled;

moduleExports.assemble = dbgeng.assemble;

moduleExports.callExtension = dbgeng.callExtension;

moduleExports.disassemble = dbgeng.disassemble;

moduleExports.execute = dbgeng.execute;

moduleExports.getPageSize = dbgeng.getPageSize;

moduleExports.isPointer64Bit = dbgeng.isPointer64Bit;

moduleExports.readMsr = dbgeng.readMsr;

moduleExports.writeMsr = dbgeng.writeMsr;







// exports
module.exports = moduleExports;



