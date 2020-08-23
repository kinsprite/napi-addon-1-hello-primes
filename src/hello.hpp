
#ifndef __HELLO_HPP_INCLUDED__
#define __HELLO_HPP_INCLUDED__

#include <node_api.h>
#include <string>

#ifdef __cplusplus
// extern "C" {
#endif

std::string value_to_string(napi_env env, napi_value value);

// generateNumbers(n: number, callback: (v: number) => void): void
napi_value GenerateNumbers(napi_env env, napi_callback_info info);

// short time job: joinStrings(arr: string[], sep: string): string
napi_value JoinStrings(napi_env env, napi_callback_info info);

// long time job: isPrime(n: number) => boolean
napi_value IsPrime(napi_env env, napi_callback_info info);

// long time job: isPrimeAsync(n: number).then((boolean) => void);
napi_value IsPrimeAsync(napi_env env, napi_callback_info info);


#ifdef __cplusplus
// }
#endif

#endif // !__HELLO_HPP_INCLUDED__
