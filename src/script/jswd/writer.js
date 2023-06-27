const assert = require("assert");

const typing = require("typing");

const fmt = require('fmt');

const maxStringLength = 65536;


/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeFloat32BE(writer , address , value)
{
    assert( typing.isNumber(value) );

    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    view.setFloat32(0 , value , false);

    return writer.write(address , buffer);
}
exports.writeFloat32BE = writeFloat32BE;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeFloat32LE(writer ,address , value)
{
    assert( typing.isNumber(value) );

    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    view.setFloat32(0 , value , true);

    return writer.write(address , buffer);
}
exports.writeFloat32LE = writeFloat32LE;


/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeFloat64BE(writer ,address , value)
{
    assert( typing.isNumber(value) );

    let buffer = new ArrayBuffer(8);

    let view = new DataView(buffer);

    view.setFloat64(0 , value , false);

    return writer.write(address , buffer);
}
exports.writeFloat64BE = writeFloat64BE;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeFloat64LE(writer ,address , value)
{
    assert( typing.isNumber(value) );

    let buffer = new ArrayBuffer(8);

    let view = new DataView(buffer);

    view.setFloat64( 0 , value , true);

    return writer.write(address , buffer);
}
exports.writeFloat64LE = writeFloat64LE;

//--------------------------------for signed----------------------------------------------------------------

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeInt8(writer ,address , value)
{
    assert( typing.isNumber(value) );

    let buffer = new ArrayBuffer(1);

    let view = new DataView(buffer);

    view.setInt8(0 , value);

    return writer.write(address , buffer);
}
exports.writeInt8 = writeInt8;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeInt16BE(writer ,address , value)
{
    assert( typing.isNumber(value) );

    let buffer = new ArrayBuffer(2);

    let view = new DataView(buffer);

    view.setInt16( 0 , value , false);

    return writer.write(address , buffer);
}
exports.writeInt16BE = writeInt16BE;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeInt16LE(writer ,address, value)
{
    assert( typing.isNumber(value) );

    let buffer = new ArrayBuffer(2);

    let view = new DataView(buffer);

    view.setInt16( 0 , value , true);

    return writer.write(address , buffer);
}
exports.writeInt16LE = writeInt16LE;


/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeInt32BE(writer ,address, value)
{
    assert( typing.isNumber(value) );

    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    view.setInt32( 0 , value , false);

    return writer.write(address , buffer);
}
exports.writeInt32BE = writeInt32BE;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeInt32LE(writer ,address, value)
{
    assert( typing.isNumber(value) );

    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    view.setInt32( 0 , value , true);

    return  writer.write(address , buffer);
}
exports.writeInt32LE = writeInt32LE;


/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Int64} value
 * @returns {Number}
 */
function writeInt64BE(writer ,address , value)
{
    let argValue = 0;

    if ( Int64.isInt64(value) )
    {
        argValue = value;
    }
    else
    {
        argValue = new Int64(value);
    }

    let buffer = new ArrayBuffer(8);

    let view = new DataView(buffer);

    view.setInt32( 4 , argValue.low , false );

    view.setInt32( 0 , argValue.high , false );

    return writer.write(address , buffer);
}
exports.writeInt64BE = writeInt64BE;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Int64} value
 * @returns {Number}
 */
function writeInt64LE(writer ,address, value )
{
    let argValue = 0;

    if ( Int64.isInt64(value) )
    {
        argValue = value;
    }
    else
    {
        argValue = new Int64(value);
    }

    let buffer = new ArrayBuffer(8);

    let view = new DataView(buffer);

    view.setInt32( 0 , argValue.low , true );

    view.setInt32( 4 , argValue.high , true );

    return writer.write(address , buffer);
}
exports.writeInt64LE = writeInt64LE;



//--------------------------------for unsigned----------------------------------------------------------------


/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeUint8(writer ,address , value)
{
    let buffer = new ArrayBuffer(1);

    let view = new DataView(buffer);

    view.setUint8(0 , value);

    return writer.write(address , buffer);
}
exports.writeUint8 = writeUint8;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeUint16BE(writer ,address, value)
{
    let buffer = new ArrayBuffer(2);

    let view = new DataView(buffer);

    view.setUint16(0 , value , false);

    return writer.write(address , buffer);
}
exports.writeUint16BE = writeUint16BE;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeUint16LE(writer ,address, value)
{
    let buffer = new ArrayBuffer(2);

    let view = new DataView(buffer);

    view.setUint16(0 , value , true);

    return writer.write(address , buffer);
}
exports.writeUint16LE = writeUint16LE;


/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeUint32BE(writer ,address, value)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    view.setUint32(0 , value , false);

    return writer.write(address , buffer);
}
exports.writeUint32BE = writeUint32BE;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Number} value
 * @returns {Number}
 */
function writeUint32LE(writer ,address, value )
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    view.setUint32(0 , value , true);

    return writer.write(address , buffer);
}
exports.writeUint32LE = writeUint32LE;


/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Uint64} value
 * @returns {Number}
 */
function writeUint64BE(writer ,address , value)
{
    let argValue = 0;

    if ( Uint64.isUint64(value) )
    {
        argValue = value;
    }
    else
    {
        argValue = new Uint64(value);
    }

    let buffer = new ArrayBuffer(8);

    let view = new DataView(buffer);

    view.setUint32( 4 , argValue.low, false );

    view.setUint32( 0 , argValue.high, false );

    return writer.write(address , buffer);
}
exports.writeUint64BE = writeUint64BE;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {Uint64} value
 * @returns {Number}
 */
function writeUint64LE(writer ,address, value)
{
    let argValue = 0;

    if ( Uint64.isUint64(value) )
    {
        argValue = value;
    }
    else
    {
        argValue = new Uint64(value);
    }

    let buffer = new ArrayBuffer(8);

    let view = new DataView(buffer);

    view.setUint32( 0 , argValue.low, true );

    view.setUint32( 4 , argValue.high, true );

    return writer.write(address , buffer);
}
exports.writeUint64LE = writeUint64LE;


//--------------------------------for string----------------------------------------------------------------


/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {String} value
 * @returns {Number}
 */
function writeString(writer , address , value)
{
    let encoder = null;

    let data = null;

    encoder = new TextEncoder('utf8');

    data = encoder.encode(value);

    return writer.write(address , data.buffer);
}
exports.writeString = writeString;

/**
 *
 * @param {Writer} writer
 * @param {Uint64} address
 * @param {String} value
 * @returns {Number}
 */
function writeWideString(writer ,address , value)
{
     let encoder = null;

    let data = null;

    encoder = new TextEncoder('utf16');

    data = encoder.encode(value);

    return writer.write(address , data.buffer);
}
exports.writeWideString = writeWideString;


