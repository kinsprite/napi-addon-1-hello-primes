
#include <assert.h>
#include <node_api.h>

#include "hello.hpp"


#define DECLARE_NAPI_METHOD(name, func) \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor descArr[] = {
    DECLARE_NAPI_METHOD("generateNumbers", GenerateNumbers),
    DECLARE_NAPI_METHOD("joinStrings", JoinStrings),
    DECLARE_NAPI_METHOD("isPrime", IsPrime),
    DECLARE_NAPI_METHOD("isPrimeAsync", IsPrimeAsync),
  };
  status = napi_define_properties(env, exports, sizeof(descArr)/sizeof(descArr[0]), descArr);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
