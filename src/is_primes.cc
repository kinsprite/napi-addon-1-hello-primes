
#include <assert.h>
#include <node_api.h>

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
  PrimeIter(): n(0) {}
  PrimeIter(IntType n_): n(n_) {}
  PrimeIter(const PrimeIter &other): n(other.n) {}

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

  IntType dereference() const
  { return boost::math::prime(n); }

  IntType n;
};

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

  if (num < boost::math::prime(0)) {

  }

  if (num > boost::math::prime(boost::math::max_prime)) {

  }

  bool isTrue = std::binary_search(PrimeIter<uint32_t>(0), PrimeIter<uint32_t>(boost::math::max_prime + 1), num);

  status = napi_get_boolean(env, isTrue, &result);
  assert(status == napi_ok);
  return result;
}
