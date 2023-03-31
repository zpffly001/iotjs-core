#include "button.hpp"

JSClassID NativeButtonClassID;
static JSValue curArg[10];
static JSContext *curCtx;
static JSValueConst thisVal;
static lv_obj_t *label;
static COMP_REF *th;
static Button *btn;
Button *GetInstance(JSValueConst this_val)
{
    th = (COMP_REF *)JS_GetOpaque(this_val, NativeButtonClassID);
    btn = (Button *)th->comp;
    return btn;
}

/**
 * @brief 设置坐标
 *
*/
static JSValue lvBtnSetPos(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    int x, y;
    JS_ToInt32(ctx, &x, argv[0]);
    JS_ToInt32(ctx, &y, argv[1]);
    Button *btn = GetInstance(this_val);
    lv_obj_set_pos(btn->instance, x, y);
    return JS_UNDEFINED;
}

/**
 * @brief 设置大小
 *
*/
static JSValue lvBtnSetSize(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    int length, width;
    JS_ToInt32(ctx, &length, argv[0]);
    JS_ToInt32(ctx, &width, argv[1]);
    Button *btn = GetInstance(this_val);
    lv_obj_set_size(btn->instance, length, width);
    return JS_UNDEFINED;
}

/**
 * @brief 点击时间对应的回调函数
 */
static void btnClickCallback(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);

    if(code == LV_EVENT_CLICKED) {
        JSValue *arg = (JSValue *)lv_event_get_user_data(e);
        int count;
        JS_ToInt32(curCtx, &count, arg[1]);
        JSValue param[10];
        memcpy(param, arg + 2, sizeof(JSValue) * count);
        JS_Call(curCtx, arg[0], thisVal, count, param);
    }
}

/**
 * @brief 点击事件
 *
*/
static JSValue lvBtnOnClick(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    int count;
    thisVal = this_val;
    JSValue func = argv[0];
    if (JS_IsUndefined(func) || (!JS_IsFunction(ctx, func)))
    {
        return JS_UNDEFINED;
    }
    JS_ToInt32(ctx, &count, argv[1]);
    /* 如果强行把arg[i] = argv[i + 2]等，会出现报错，须在堆中开辟内存*/
    JSValue *arg = (JSValue *)malloc(sizeof(JSValue) * (count + 2));
    arg[0] = func;
    arg[1] = argv[1];
    /* 把方法、方法形参数量这些参数放入arg中 */
    memcpy(arg + 2, argv + 2, sizeof(JSValue) * count);

    lv_obj_add_event_cb(GetInstance(this_val)->instance, btnClickCallback, LV_EVENT_ALL, arg);

    return JS_UNDEFINED;
}


static const JSCFunctionListEntry ComponentProtoFuncs[] = {
    JS_CFUNC_DEF("setPos", 2, lvBtnSetPos),
    JS_CFUNC_DEF("setSize", 2, lvBtnSetSize),
    JS_CFUNC_DEF("onClick", 5, lvBtnOnClick),
};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

static JSValue NativeButtonConstructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto;
    JSValue obj;
    JSValue arg;
    JSValue jsUid;
    const char* uid;

    COMP_REF *s;

    if (JS_IsObject(argv[0])) {
        arg = argv[0];
        jsUid = JS_GetPropertyStr(ctx, arg, "uid");
        if (JS_IsString(jsUid)) {
            uid = JS_ToCString(ctx, jsUid);
            JS_FreeValue(ctx, jsUid);
        }
    }

    if (JS_IsUndefined(new_target)) {
        proto = JS_GetClassProto(ctx, NativeButtonClassID);
    } else {
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
    }

    obj = JS_NewObjectProtoClass(ctx, proto, NativeButtonClassID);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    s = (COMP_REF*)js_mallocz(ctx, sizeof(*s));
    s->uid = uid;
    s->comp = new Button(uid, NULL);

    JS_FreeCString(ctx, uid);

    if (!s)
        goto fail;

    JS_SetOpaque(obj, s);
    LV_LOG_USER("Button %s created", uid);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static void NativeButtonFinalizer(JSRuntime *rt, JSValue val) {
    COMP_REF *th = (COMP_REF *)JS_GetOpaque(val, NativeButtonClassID);
    LV_LOG_USER("NativeButton %s release", th->uid);
    if (th) {
        delete static_cast<Button*>(th->comp);
        free(th);
    }
};

static JSClassDef NativeButtonClass = {
    "NativeButton",
    .finalizer = NativeButtonFinalizer,
};

void NativeButtonInit(JSContext* ctx, JSValue ns)
{
    curCtx = ctx;
    JS_NewClassID(&NativeButtonClassID);
    JS_NewClass(JS_GetRuntime(ctx), NativeButtonClassID, &NativeButtonClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
    /* 设置类的原型对象，将一个JS对象指定为该类的原型对象，从而定义该类的属性和方法 */
    JS_SetClassProto(ctx, NativeButtonClassID, proto);

    JSValue obj = JS_NewCFunction2(ctx, NativeButtonConstructor, "NativeButton", 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetPropertyFunctionList(ctx, obj, ComponentClassFuncs, countof(ComponentClassFuncs));
    /**
     * @brief 用于向JS对象中添加一个命名属性，并将该属性的值设置为指定的值
     * var bridge = globalThis.SJSJSBridge;
     * var NativeButton = bridge.NativeRender.NativeComponents.NativeButton;
     */
    JS_DefinePropertyValueStr(ctx, ns, "NativeButton", obj, JS_PROP_C_W_E);
}
