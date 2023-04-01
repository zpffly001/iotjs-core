
#include "util.h"


static void DumpObj(JSContext *ctx, FILE *f, JSValueConst val) {
    const char *str = JS_ToCString(ctx, val);
    if (str) {
        fprintf(f, "%s\n", str);
        JS_FreeCString(ctx, str);
    } else {
        fprintf(f, "[exception]\n");
    }
};

void DJSDumpErrorWithThisval(JSContext *ctx, JSValueConst exception_val) {
    int is_error = JS_IsError(ctx, exception_val);
    DumpObj(ctx, stderr, exception_val);
    if (is_error) {
        JSValue val = JS_GetPropertyStr(ctx, exception_val, "stack");
        if (!JS_IsUndefined(val))
            DumpObj(ctx, stderr, val);
        JS_FreeValue(ctx, val);
    }
};

void DJSDumpError(JSContext *ctx) {
    JSValue exception_val = JS_GetException(ctx);
    DJSDumpErrorWithThisval(ctx, exception_val);
    JS_FreeValue(ctx, exception_val);
};

