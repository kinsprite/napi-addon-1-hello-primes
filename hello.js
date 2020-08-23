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

[
  1,
  2,
  39194 + 0xFFFF,
  114713,
  116447,
  39194 + 0xFFFF + 6644668
].forEach((n) => {
  console.log(n, "is prime:", addon.isPrime(n));
});
