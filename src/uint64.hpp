#pragma once
#include <map>

#include <v8.h>
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include <string>
#include <cstring>
#include <memory>
#include <cstdlib>

namespace NodeHDF5 {

  class Uint64 : public node::ObjectWrap {
    friend class File;
    friend class Group;
    friend class Filters;
    friend class Attributes;
    friend class PacketTable;

  protected:
  public:
    static void Initialize(v8::Local<v8::Object> exports);
    static v8::Local<v8::Object> Instantiate(unsigned long long value);
    static v8::Local<v8::Object> Instantiate(std::string value = "0");
    static v8::Local<v8::Object> Instantiate(v8::Local<v8::Object> parent, unsigned long long value = 0);
    static v8::Local<v8::Object> Instantiate(v8::Local<v8::Object> parent, std::string value = "0");
    unsigned long long Value() {
      return value;
    };

    static void toString(const v8::FunctionCallbackInfo<v8::Value>& args);
    void setValue(long long value){this->value=value;};

  protected:
    Uint64()
        : Uint64(0){

          };

    Uint64(unsigned long long l) {
      value = l;
    };

    ~Uint64(){};

  private:
    static v8::Persistent<v8::Function> Constructor;

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args) {
      v8::Isolate* isolate = args.GetIsolate();
      v8::Local<v8::Context> context = isolate->GetCurrentContext();
      // Xdm value object
      Uint64* xp;
      if (args.Length() < 1)
        xp = new Uint64(-1);
      else if((args.Length() == 1 || args.Length() == 2) && args[args.Length() - 1]->IsString()){
        std::string value = args[args.Length() - 1]->IsUndefined() ? std::string("0") : std::string(*v8::String::Utf8Value(isolate, args[args.Length() - 1]->ToString(context).ToLocalChecked()));
        char *end;
        xp = new Uint64((unsigned long long)std::strtoll(value.c_str(), &end, 10));
          
      }
      else {

        xp = new Uint64((unsigned long long)args[args.Length() - 1]->Int32Value(context).ToChecked());
      }

//      xp->value = 0;
      // extend target object
      xp->Wrap(args.This());
    };

  protected:
    unsigned long long value = 0;
  };
}
