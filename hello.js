var addon = require('bindings')('hello');

// console.log(addon.hello()); // 'world'
// console.log(addon);
console.log(addon.joinStrings(['a', 'b', 'c'], '|'));
addon.generateNumbers(10, console.log);
