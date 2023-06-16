
const assert = require("assert");

const typing = require("typing");

const dbgeng = require("dbgeng");

const fmt = require('fmt');

const int = require('integer');

const Uint64 = int.Uint64;

class Module
{
    /***
     *
     * @param {Uint64} imageBase
     */
    constructor(imageBase) {

        assert( Uint64.isUint64(imageBase) );

        this.imageBase = imageBase;

        this.imageSize = 0;

        this.imageName = '';

        this.moduleName = '';

        this.loadedImageName = '';

        this.unloaded = false;

        this.timeDateStamp = 0;

        this.checksum = 0;

        this.flags = 0;

        this.symbolType = 0;
    }
}
exports.Module = Module;



function queryModule(index)
{
    let base = dbgeng.getModuleByIndex(index);

    let item = new Module(base);

    let names = dbgeng.getModuleNames( index , base);

    item.imageName = names.imageName;

    item.moduleName = names.moduleName;

    item.loadedImageName = names.loadedImageName;

    // module size
    let parameters = dbgeng.getModuleParameters(index)

    item.imageSize = parameters.imageSize;

    item.timeDateStamp = parameters.timeDateStamp;

    item.checksum = parameters.checksum;

    item.flags = parameters.flags;

    item.symbolType = parameters.symbolType;

    return item;
}


/**
 * enum all modules
 * @returns {*[]}
 */
function enumModule()
{
    let info = dbgeng.getNumberModules();

    let item = null;

    let items = [];

    let index = 0;

    for ( index = 0; index < info.loaded; index++ )
    {
        item = queryModule(index);

        item.unloaded = false;

        items.push( item );
    }

    for ( index = info.loaded; index < info.loaded + info.unloaded;  index++ )
    {
        item = queryModule(index);

        item.unloaded = true;

        items.push( item );
    }

    return items;
}
exports.enumModule = enumModule;

function findModule(name , start = 0)
{
    let info = dbgeng.getModuleByName(name , start);

    return queryModule(info.index);
}
exports.findModule = findModule;

function getModuleBase(name , start = 0)
{
    let item = findModule(name , start);

    return item.imageBase;
}
exports.getModuleBase = getModuleBase;