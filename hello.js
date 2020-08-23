const addon = require('bindings')('hello');

console.log(addon);

function run() {
  console.log('----- JoinStrings -----');
  console.log(addon.joinStrings([ 'a', 'b', 'c' ], '1'));

  console.log('----- GenerateNumbers -----');
  let nums = '';

  addon.generateNumbers(100, (n) => {
    if (nums.length) {
      nums += ',';
    }

    nums += n;
  });

  console.log(nums);

  console.log('----- IsPrime -----');

  const checkedPrimes = [ 1, 2, 39194 + 0xffff, 114713, 116447, 39194 + 0xffff + 6644668 ];

  checkedPrimes.forEach((n) => {
    console.log(n, 'is prime:', addon.isPrime(n));
  });

  console.log('----- IsPrimeAsync -----');

  checkedPrimes.forEach((n) => {
    addon.isPrimeAsync(n).then((result) => {
      console.log(n, 'is prime:', result);
    });
  });
}

run();
