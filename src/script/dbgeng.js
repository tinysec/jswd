
const assert = require("assert");

const typing = require("typing");

const binding = require("binding");

/**
 * execute a command and return the output
 * @param {String} command
 * @param {Object} [options]
 * @returns {string}
 */
function execute(command , options)
{
    assert( typing.isString(command) && ( 0 !== command.length) );

    if ( arguments.length >= 2 )
    {
        if ( typing.isObject(options) && ( options ) )
        {
            options = optionsOrCaptured;
        }
    }

    return binding.dbgeng.execute(command , options);
}
exports.execute = execute;

/**
 * get the page size for the effective processor mode.
 * @returns {Number}
 */
function getPageSize()
{
    return binding.dbgeng.getPageSize();
}
exports.getPageSize = getPageSize;