#ifndef JSAPI_H
#define JSAPI_H

#include "quickjs/quickjs.h"
#include "djs.h"

BOOL GlobalObjectInit(JSContext *ctx);

JSValue GetGlobalObject(JSContext* ctx);

#endif