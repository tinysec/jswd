const _ = require('underscore');

let moduleExports = _.extend(
    require('jswd/module'),
    require('jswd/processor'),
    require('jswd/register'),
    require('jswd/symbol'),
    require('jswd/virtual'),
);

moduleExports.physical = require('jswd/physical');

module.exports = moduleExports;



