#include "component.hpp"

#define NATIVE_COMPONENT "NativeComponents"

void NativeComponentInit (JSContext* ctx, JSValue ns) {
    JSValue component_obj = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, ns, NATIVE_COMPONENT, component_obj);

    /* FIXME 只初始化Button组件*/
    NativeButtonInit(ctx, component_obj);
    NativeLabelInit(ctx, component_obj);
};