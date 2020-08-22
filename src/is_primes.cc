
#include <assert.h>
#include <node_api.h>

#include <utility>
#include <vector>
#include <string>

#include <boost/math/special_functions/prime.hpp>

#include "hello.hpp"

// long time job: isPrime(n: number)
napi_value IsPrimes(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;

  // Input args
  size_t argc = 1;
  napi_value argv[1];

  status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
  assert(status == napi_ok);

  int64_t num = 0;
  status = napi_get_value_int64(env, argv[0], &num);

  if (num < boost::math::prime(0)) {

  }

  if (num > boost::math::prime(boost::math::max_prime)) {

  }

  return result;
}
