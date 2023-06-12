const assert = require("assert");

const typing = require("typing");

const fmt = require('fmt');

const int = require('integer');

const Int64 = int.Int64;

const Uint64 = int.Uint64;


const maxStringLength = 65536;


function readFloat32BE(reader , address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getFloat32(0 , false);
}
exports.readFloat32BE = readFloat32BE;

function readFloat32LE(reader ,address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getFloat32(0 , true);
}
exports.readFloat32LE = readFloat32LE;



function readFloat64BE(reader ,address)
{
    let buffer = new ArrayBuffer(8);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getFloat64(0 , true);
}
exports.readFloat64BE = readFloat64BE;


function readFloat64LE(reader ,address)
{
    let buffer = new ArrayBuffer(8);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getFloat64(0 , true);
}
exports.readFloat64LE = readFloat64LE;

//--------------------------------for signed----------------------------------------------------------------


function readInt8(reader ,address)
{
    let buffer = new ArrayBuffer(1);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getInt8(0);
}
exports.readInt8 = readInt8;

function readInt16BE(reader ,address)
{
    let buffer = new ArrayBuffer(2);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getInt16(0 , false);
}
exports.readInt16BE = readInt16BE;

function readInt16LE(reader ,address)
{
    let buffer = new ArrayBuffer(2);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getInt16(0 , true);
}
exports.readInt16LE = readInt16LE;



function readInt32BE(reader ,address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getInt32(0 , false);
}
exports.readInt32BE = readInt32BE;


function readInt32LE(reader ,address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getInt32(0 , true);
}
exports.readInt32LE = readInt32LE;



function readInt64BE(reader ,address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    let value = null;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    value = new Int64(0);

    value.low = view.getInt32(0 , false);

    value.high = view.getInt32(4 , false);

    return value;
}
exports.readInt64BE = readInt64BE;

function readInt64LE(reader ,address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    let value = null;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    value = new Int64(0);

    value.high = view.getInt32(0 , true);

    value.low = view.getInt32(4 , true);

    return value;
}
exports.readInt64LE = readInt64LE;



//--------------------------------for unsigned----------------------------------------------------------------



function readUint8(reader ,address)
{
    let buffer = new ArrayBuffer(1);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getUint8(0);
}
exports.readUint8 = readUint8;

function readUint16BE(reader ,address)
{
    let buffer = new ArrayBuffer(2);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getUint16(0 , false);
}
exports.readUint16BE = readUint16BE;

function readUint16LE(reader ,address)
{
    let buffer = new ArrayBuffer(2);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getUint16(0 , true);
}
exports.readUint16LE = readUint16LE;



function readUint32BE(reader ,address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getUint32(0 , false);
}
exports.readUint32BE = readUint32BE;


function readUint32LE(reader ,address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    return view.getUint32(0 , true);
}
exports.readUint32LE = readUint32LE;



function readUint64BE(reader ,address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    let value = null;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    value = new Uint64(0);

    value.low = view.getUint32(0 , false);

    value.high = view.getUint32(4 , false);

    return value;
}
exports.readUint64BE = readUint64BE;

function readUint64LE(reader ,address)
{
    let buffer = new ArrayBuffer(4);

    let view = new DataView(buffer);

    let readed = 0;

    let value = null;

    readed = reader.read(address , buffer);
    if ( buffer.byteLength !== readed )
    {
        throw new Error(fmt.sprintf('read %s fail , readed %d bytes' , address , readed) )
    }

    value = new Uint64(0);

    value.high = view.getUint32(0 , true);

    value.low = view.getUint32(4 , true);

    return value;
}
exports.readUint64LE = readUint64LE;


//--------------------------------for string----------------------------------------------------------------


function readString(reader ,address , length)
{
    let bufferSize = maxStringLength;

    let buffer = null;

    let view = null;

    let i = 0;

    let textLength = 0;

    let bytesReaded = 0;

    let decoder = null;

    if ( arguments.length >= 2 )
    {
        assert( typing.isNumber(length) );

        if ( length < 0)
        {
            bufferSize = maxStringLength;
        }
        else
        {
            bufferSize = length;
        }
    }

    buffer = new ArrayBuffer(bufferSize);

    view = new DataView(view);

    bytesReaded = reader.read(address , buffer);

    if ( 0 === bytesReaded )
    {
        return '';
    }

    for ( i = 0; i < bytesReaded; i++ )
    {
        if ( '\0'.charCodeAt(0) === view.getUint8(i) )
        {
            break;
        }

        textLength++;
    }

    decoder = new TextDecoder('utf-8');

    return decoder.decode( buffer.slice(0 , textLength) );
}
exports.readString = readString;

function readWideString(reader ,address , length)
{
    let bufferSize = maxStringLength;

    let buffer = null;

    let view = null;

    let i = 0;

    let textLength = 0;

    let bytesReaded = 0;

    let decoder = null;

    if ( arguments.length >= 2 )
    {
        assert( typing.isNumber(length) );

        if ( length < 0)
        {
            bufferSize = maxStringLength;
        }
        else
        {
            bufferSize = length;
        }
    }

    buffer = new ArrayBuffer(bufferSize);

    view = new DataView(view);

    bytesReaded = reader.read(address , buffer);

    if ( 0 === bytesReaded )
    {
        return '';
    }

    for ( i = 0; i < bytesReaded; i += 2 )
    {
        if ( '\0'.charCodeAt(0) === view.getUint8(i) && '\0'.charCodeAt(0) === view.getUint8(i+i) )
        {
            break;
        }

        textLength += 2;
    }

    decoder = new TextDecoder('utf-16');

    return decoder.decode( buffer.slice(0 , textLength) );
}
exports.readWideString = readWideString;


