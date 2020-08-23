
#include <assert.h>
#include <node_api.h>

#include <cstdio>
#include <utility>
#include <vector>
#include <string>

#include <algorithm>
#include <boost/math/special_functions/prime.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include "hello.hpp"

template <typename IntType>
class PrimeIter
  : public boost::iterator_facade<
        PrimeIter<IntType>
      , IntType
      , boost::random_access_traversal_tag
      , IntType
    >
{
public:
  PrimeIter(): n(0), primesExt(nullptr) {}
  PrimeIter(IntType n_, const std::vector<IntType> *pExt = nullptr): n(n_), primesExt(pExt) {}
  PrimeIter(const PrimeIter &other) = default;

private:
  friend class boost::iterator_core_access;
  template <class> friend class PrimeIter;

  template <class OtherValue>
  bool equal(PrimeIter<OtherValue> const& other) const {
    return this->n == other.n;
  }

  void increment() { n++; }

  void decrement() { n--; }

  void advance(int n_) {
    n += n_;
  }

  template <class OtherValue>
  int distance_to(PrimeIter<OtherValue> const& other) const {
    return n - other.n;
  }

  IntType dereference() const {
    IntType bpMax = boost::math::max_prime;

    if (n <= bpMax) {
      return boost::math::prime(n);
    }

    if (primesExt && n - bpMax <= primesExt->size()) {
      return (*primesExt)[n - bpMax - 1];
    }

    return 0;
  }

  IntType n;
  const std::vector<IntType> *primesExt;
};

std::vector<uint32_t> GeneratePrimesExt(uint32_t extCount = 1000) {
  std::vector<uint32_t> primesExt;
  primesExt.reserve(extCount);

  uint32_t maxN = boost::math::max_prime + extCount;

  for (uint32_t i = boost::math::prime(boost::math::max_prime) + 1, n = boost::math::max_prime + 1;
    n <= maxN;
    i++) {
    bool isPrimeNum = true;

    for (uint32_t inner = 0; inner < n; inner++) {
      uint32_t innerPrime = *PrimeIter<uint32_t>(inner, &primesExt);
      if (i % innerPrime == 0) {
        isPrimeNum = false;
        break;
      }
    }

    if (isPrimeNum) {
      primesExt.push_back(i);
      n++;
      // std::printf("%d\n", i);
    }
  }

  return std::move(primesExt);
}

// long time job: isPrime(n: number)
napi_value IsPrime(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;

  // Input args
  size_t argc = 1;
  napi_value argv[1];

  status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
  assert(status == napi_ok);

  int64_t num = 0;
  status = napi_get_value_int64(env, argv[0], &num);
  assert(status == napi_ok);

  bool isTrue = false;

  if (num < boost::math::prime(0)) {

  } else if (num <= boost::math::prime(boost::math::max_prime)) {
    isTrue = std::binary_search(PrimeIter<uint32_t>(0), PrimeIter<uint32_t>(boost::math::max_prime + 1), num);
  } else {
    // Generate Primes ext
    static auto primesExt = GeneratePrimesExt();
    uint32_t maxPrimes = primesExt[primesExt.size() - 1];

    if (num > maxPrimes) {
      std::fprintf(stderr, "Input number (%d) is large than max prime supported (%d)\n", num, maxPrimes);
    }

    isTrue = std::binary_search(primesExt.begin(), primesExt.end(), num);
  }

  status = napi_get_boolean(env, isTrue, &result);
  assert(status == napi_ok);
  return result;
}
