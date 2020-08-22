
#include <assert.h>
#include <node_api.h>

#include <utility>
#include <vector>
#include <string>

#include <boost/algorithm/string/join.hpp>

#include "hello.hpp"

// short time job: join(arr: string[], sep: string)
napi_value JoinStrings(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value result;

  // Input args
  size_t argc = 2;
  napi_value argv[2];

  status = napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
  assert(status == napi_ok);

  std::vector<std::string> vec;
  std::string sep{"|"};

  if (argc) {
    uint32_t length = 0;
    status = napi_get_array_length(env, argv[0], &length);
    assert(status == napi_ok);
    vec.reserve(length);

    for (uint32_t i = 0; i < length; i++) {
      napi_value e;
      status = napi_get_element(env, argv[0], i, &e);
      assert(status == napi_ok);

      vec.push_back(value_to_string(env, e));
    }
  }

  if (argc > 1) {
    sep = value_to_string(env, argv[1]);
  }

  // Join the strings
  auto joined = boost::join(vec, sep);
  status = napi_create_string_utf8(env, joined.c_str(), joined.size(), &result);
  assert(status == napi_ok);
  return result;
}
