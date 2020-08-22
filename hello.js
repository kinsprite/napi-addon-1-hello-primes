const addon = require('bindings')('hello');

// console.log(addon.hello()); // 'world'
// console.log(addon);
console.log(addon.joinStrings(['a', 'b', 'c'], '|'));

let nums = "";

addon.generateNumbers(100, (n) => {
  if (nums.length) {
    nums += ',';
  }

  nums += n;
});

console.log(nums);

console.log(addon.isPrime(5))
console.log(addon.isPrime(121))
