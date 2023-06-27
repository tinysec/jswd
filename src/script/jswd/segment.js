const assert = require("assert");

const typing = require("typing");

const dbgeng = require("dbgeng");

const fmt = require('fmt');

const reg = require('jswd/register');

const virtual = require('jswd/virtual');


class Segment
{
    constructor(value) {

        this.value = value;

        // base [24 : 32)
        const baseHigh = value.slice( 56, 63).toNumber();

        // G ,
        this.granularity =  value.getBit(55) ;

        // D/B , default operation size , 0 = 16bit , 1 = 32bit
        this.db =  value.getBit(54) ;

        // L , 64-bit code segment
        this.l =  value.getBit(53) ;

        // AVL  , available for use by system software
        this.avl =  value.getBit(52) ;

        // [16 : 20)
        const limitHigh = value.slice( 48, 52).toNumber();

        // P,
        this.present = value.getBit( 47) ;

        // DPL , descriptor privilege level
        this.dpl = value.slice( 45, 47).toNumber();

        // S , 0 = system , 1 = code or data
        this.system = value.getBit( 44);

        // segment type
        this.type = value.slice( 40, 44).toNumber();

        // base [16 : 24)
        const baseMid = value.slice( 32, 39).toNumber();

        // base [0 : 16)
        const baseLow = value.slice( 16, 32).toNumber();

        // limit [0:16)
        const limitLow = value.slice( 0, 16).toNumber();

        //
        this.base =  ( baseHigh << 24 ) | ( baseMid << 16 )  | baseLow;

        this.limit =  ( limitHigh << 16 )  | limitLow;
    }
}
exports.Segment = Segment;

/**
 * get segment value
 * @param {String|Number} nameOrSelector
 * @returns {Uint64}
 */
function getSegment(nameOrSelector)
{
    let selector = 0;

    if ( typing.isString(nameOrSelector) )
    {
        selector = reg.getRegister(nameOrSelector);

        assert( typing.isNumber(selector) );
    }
    else
    {
        assert( typing.isNumber(nameOrSelector) );

        selector = nameOrSelector;
    }

    let gdtr = reg.getRegister('gdtr');

    assert( Uint64.isUint64(gdtr) );

    let index = selector >> 3;

    let offset = index * 8;

    let address = new Uint64( gdtr.add(offset) );

    return virtual.readUint64LE( address );
}
exports.getSegment = getSegment;
exports.getSeg = getSegment;


