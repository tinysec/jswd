const assert = require("assert");

const typing = require("typing");

const dbgeng = require("dbgeng");

const fmt = require('fmt');

const int = require('integer');

const Uint64 = int.Uint64;


class Register
{
    constructor(index) {

        this.index = index;

        this.name = '';

        this.bits = 0;

        this.type = 0;
    }

    get value()
    {
        return dbgeng.getRegisterValue(this.index);
    }

    set value(newValue)
    {
        let argValue = 0;

        if ( this.bits <= 8 )
        {
            if ( typing.isNumber(newValue) )
            {
                argValue = newValue & 0xff;
            }
            else if ( Uint64.isUint64(newValue) )
            {
                argValue = newValue.and( 0xff).toNumber();
            }
            else if ( typing.isUint8Array(newValue) )
            {
                argValue = newValue;
            }
            else
            {
                assert( typing.isString(newValue) );

                argValue = new Uint64(newValue).and(0xff).toNumber();
            }
        }
        else if ( this.bits <= 16 )
        {
            if ( typing.isNumber(newValue) )
            {
                argValue = newValue & 0xffff;
            }
            else if ( Uint64.isUint64(newValue) )
            {
                argValue = newValue.and( 0xffff).toNumber();
            }
            else if ( typing.isUint8Array(newValue) )
            {
                argValue = newValue;
            }
            else
            {
                assert( typing.isString(newValue) );

                argValue = new Uint64(newValue).and(0xffff).toNumber();
            }
        }
        else if ( this.bits <= 32 )
        {
            if ( typing.isNumber(newValue) )
            {
                argValue = newValue & 0xffffffff;
            }
            else if ( Uint64.isUint64(newValue) )
            {
                argValue = newValue.and( 0xffffffff).toNumber();
            }
            else if ( typing.isUint8Array(newValue) )
            {
                argValue = newValue;
            }
            else
            {
                assert( typing.isString(newValue) );

                argValue = new Uint64(newValue).and(0xffffffff).toNumber();
            }
        }
        else if ( this.bits <= 64 )
        {
            if ( typing.isNumber(newValue) )
            {
                argValue = newValue;
            }
            else if ( Uint64.isUint64(newValue) )
            {
                argValue = newValue;
            }
            else if ( typing.isUint8Array(newValue) )
            {
                argValue = newValue;
            }
            else
            {
                assert( typing.isString(newValue) );

                argValue = new Uint64(newValue);
            }
        }
        else if ( this.bits <= 128 )
        {
            if ( typing.isNumber(newValue) )
            {
                argValue = newValue;
            }
            else if ( Uint64.isUint64(newValue) )
            {
                argValue = newValue;
            }
            else if ( typing.isUint8Array(newValue) )
            {
                argValue = newValue;
            }
            else
            {
                assert( typing.isString(newValue) );

                argValue = new Uint64(newValue);
            }
        }

        return dbgeng.setRegisterValue(this.index , this.type , argValue );
    }
}
exports.Register = Register;

function findRegister(nameOrIndex)
{
    let index = 0;

    let desc = null;

    let item = null;

    let child = false;

    if ( typing.isString(nameOrIndex) )
    {
        index = dbgeng.getRegisterIndex(nameOrIndex);
    }
    else
    {
        assert( typing.isNumber(nameOrIndex) );

        index = nameOrIndex;
    }

    desc = dbgeng.getRegisterDescription(index);

    item = new Register(index);

    item.name = desc.name;

    item.type = desc.type;

    //item.value = dbgeng.getRegisterValue(item.index);

    child = ( 0 !== ( desc.flags & dbgeng.DEBUG_REGISTER_SUB_REGISTER) );

    if ( child )
    {
        item.bits = desc.subregLength;
    }

    if ( dbgeng.DEBUG_VALUE_INT8 === desc.type )
    {
        if ( !child )
        {
            item.bits = 8;
        }
    }
    else if ( dbgeng.DEBUG_VALUE_INT16 === desc.type )
    {
        if ( !child )
        {
            item.bits = 16;
        }
    }
    else if ( dbgeng.DEBUG_VALUE_INT32 === desc.type )
    {
        if ( !child )
        {
            item.bits = 32;
        }
    }
    else if ( dbgeng.DEBUG_VALUE_INT64 === desc.type )
    {
        if ( !child )
        {
            item.bits = 64;
        }
    }
    else if ( dbgeng.DEBUG_VALUE_FLOAT32 === desc.type )
    {
        if ( !child )
        {
            item.bits = 32;
        }
    }
    else if ( dbgeng.DEBUG_VALUE_FLOAT64 === desc.type )
    {
         if ( !child )
         {
             item.bits = 64;
         }
    }
    else if ( dbgeng.DEBUG_VALUE_FLOAT80 === desc.type )
    {
        if ( !child )
        {
            item.bits = 80;
        }
    }
    else if ( dbgeng.DEBUG_VALUE_FLOAT82 === desc.type )
    {
        if ( !child )
        {
            item.bits = 82;
        }
    }
    else if ( dbgeng.DEBUG_VALUE_FLOAT128 === desc.type )
    {
        if ( !child )
        {
            item.bits = 128;
        }
    }
    else if ( dbgeng.DEBUG_VALUE_VECTOR64 === desc.type )
    {
        if ( !child )
        {
            item.bits = 64;
        }
    }
    else if ( dbgeng.DEBUG_VALUE_VECTOR128 === desc.type )
    {
        if ( !child )
        {
            item.bits = 128;
        }
    }

    return item;
}
exports.findRegister = findRegister;


function enumRegister()
{
    let count = 0;

    let index = 0;

    let item = null;

    let items = [];

    count = dbgeng.getNumberRegisters();

    for ( index = 0; index < count; index++)
    {
        item = findRegister(index);

        items.push(item);
    }

    return items;
}
exports.enumRegister = enumRegister;


function readRegister(name)
{
    let item = findRegister(name);

    return item.value;
}
exports.readRegister = readRegister;


function writeRegister( name , value )
{
    let reg = findRegister(name);

    return reg.value = value;
}
exports.writeRegister = writeRegister;


