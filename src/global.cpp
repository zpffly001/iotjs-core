#include "global.hpp"

#define NativeObject "NativeObject"

JSValue GetGlobalObject (JSContext* ctx) {
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue nativeObject = JS_GetPropertyStr(ctx, globalObj, NativeObject);
    JS_FreeValue(ctx, globalObj);
    return nativeObject;
}

BOOL GlobalObjectInit (JSContext *ctx) {
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSAtom global_obj_atom = JS_NewAtom(ctx, NativeObject);
    JSValue nativeObject = JS_NewObjectProto(ctx, JS_NULL);
    /* 当前jsBridge设置为context中的全局对象，属性名为JSBRIDGE */
    JS_SetProperty(ctx, globalObj, global_obj_atom, nativeObject);
    JS_FreeValue(ctx, globalObj);
    JS_FreeAtom(ctx, global_obj_atom);
    return 0;
}