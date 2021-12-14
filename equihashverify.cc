#include <nan.h>
#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>
#include <stdexcept>
#include "crypto/equihash.h"
#include <vector>

using namespace node;
using namespace v8;
using namespace std;

#define THROW_ERROR_EXCEPTION(x) Nan::ThrowError(x)

const char* ToCString(const Nan::Utf8String& value) {
  return *value ? *value : "<string conversion failed>";
}

NAN_METHOD(verify) {

    if (info.Length() < 5)
        return THROW_ERROR_EXCEPTION("hasher-equihash.verify - 5 arguments expected");
    if (!info[3]->IsInt32() || !info[4]->IsInt32())
        return THROW_ERROR_EXCEPTION("hasher-equihash.verify - Fourth and fifth parameters should be equihash parameters (n, k)");

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    Isolate *argsIsolate = info.GetIsolate();
    Local<Context> context = argsIsolate->GetCurrentContext();
    Local<Object> header = info[0]->ToObject(context).ToLocalChecked();
    Local<Object> solution = info[1]->ToObject(context).ToLocalChecked();

    if (!node::Buffer::HasInstance(header) || !node::Buffer::HasInstance(solution)) {
        return THROW_ERROR_EXCEPTION("hasher-equihash.verify - First two arguments should be buffer objects");
    }

    if (!info[2]->IsString()) {
        return THROW_ERROR_EXCEPTION("hasher-equihash.verify - Third argument should be the personalization string");
    }

    const char *hdr = node::Buffer::Data(header);
    if (node::Buffer::Length(header) != 140) {
        info.GetReturnValue().Set(false);
        return;
    }

    const char *soln = node::Buffer::Data(solution);
    vector<unsigned char> vecSolution(soln, soln + node::Buffer::Length(solution));
    Nan::Utf8String str(info[2]);
    const char* personalizationString = ToCString(str);

    unsigned int N = info[3].As<Uint32>()->Value();
    unsigned int K = info[4].As<Uint32>()->Value();

    crypto_generichash_blake2b_state state;
    EhInitialiseState(N, K, state, personalizationString);
    crypto_generichash_blake2b_update(&state, (const unsigned char*)hdr, 140);

    bool isValid;
    EhIsValidSolution(N, K, state, vecSolution, isValid);
    info.GetReturnValue().Set(isValid);
}

NAN_MODULE_INIT(init) {
    Nan::Set(target, Nan::New("verify").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(verify)).ToLocalChecked());
}

NODE_MODULE(hashermtp, init)
