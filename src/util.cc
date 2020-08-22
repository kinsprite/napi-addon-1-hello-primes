#include <assert.h>
#include <node_api.h>

#include <utility>
#include <string>

#include "hello.hpp"

std::string value_to_string(napi_env env, napi_value value) {
  napi_status status;
  size_t strLen = 0;
  status = napi_get_value_string_utf8(env, value, nullptr, 0, &strLen);
  assert(status == napi_ok);

  std::string str;
  // buffer includes '\0'
  str.resize(strLen + 1);

  status = napi_get_value_string_utf8(env, value,
    const_cast<std::string::value_type *>(str.data()), str.size(), &strLen);
  assert(status == napi_ok);
  str.resize(strLen);
  return std::move(str);
}
