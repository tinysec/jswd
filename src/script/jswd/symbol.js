const assert = require("assert");

const typing = require("typing");

const fmt = require('fmt');

const int = require('integer');

const Int64 = int.Int64;

const Uint64 = int.Uint64;

const dbgeng = require("dbgeng");


// symbol to address
exports.resolve = dbgeng.getOffsetByName;

// address to symbol
exports.symbolize = dbgeng.getNameByOffset;


/**
 *
 * @param {String} name
 * @returns {Number}
 */
function sizeof(name)
{
    let info = dbgeng.getSymbolTypeId( name);

    return dbgeng.getTypeSize(info.imageBase , info.typeId);
}
exports.sizeof = sizeof;


/**
 *
 * @param {String} type
 * @param {String} field
 * @returns {Number}
 */
function fieldOffset( type , field)
{
    let info = dbgeng.getSymbolTypeId( type);

    return dbgeng.getFieldOffset( info.imageBase , info.typeId , field);
}
exports.fieldOffset = fieldOffset;

