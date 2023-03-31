#include "app.hpp"

#define APP "APP"

void NativeAppInit (JSContext* ctx) {
    JSValue globalObject = GetGlobalObject(ctx);

    JSValue obj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, globalObject, APP, obj);
    JS_FreeValue(ctx, globalObject);

    /* 初始化组件 */
    NativeComponentInit(ctx, obj);

    lv_init();
};