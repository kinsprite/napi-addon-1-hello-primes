

#include <assert.h>
#include <node_api.h>

#include <random>

#include "hello.hpp"

// generateNumbers(n: number, callback: (v: number) => void)
napi_value GenerateNumbers(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 2;
  napi_value args[2];
  status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
  assert(status == napi_ok);
  assert(argc >= 2);

  uint32_t n = 0;
  status = napi_get_value_uint32(env, args[0], &n);
  assert(status == napi_ok);

  napi_value global;
  status = napi_get_global(env, &global);
  assert(status == napi_ok);

  napi_value cb = args[1];

  std::random_device r;
  // Choose a random mean between 1 and n
  std::default_random_engine e(r());
  std::uniform_int_distribution<uint32_t> uniform_dist(1, n);

  for (uint32_t i = 0; i < n; i++) {
    auto mean  = uniform_dist(e);
    napi_value argv[1];

    status = napi_create_uint32(env, mean, argv);
    assert(status == napi_ok);

    status = napi_call_function(env, global, cb, 1, argv, nullptr);
    assert(status == napi_ok);
  }

  return nullptr;
}
