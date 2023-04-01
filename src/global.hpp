#ifndef JSAPI_H
#define JSAPI_H

extern "C" {
    #include "quickjs/quickjs.h"
    #include "djs.h"
};

BOOL GlobalObjectInit(JSContext *ctx);

JSValue GetGlobalObject(JSContext* ctx);

#endif