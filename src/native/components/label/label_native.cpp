#include "label.hpp"
#include "native/components/button/button.hpp"

/* multiple definition of `curCtx'; ./components/button_native.o:(.bss+0xa0): first defined here */
static JSValue curArg[10];
static JSContext *curCtx;
static JSValueConst thisVal;
static JSClassID NativeLabelClassID;
extern JSClassID NativeButtonClassID;
static lv_obj_t *label;
static COMP_REF *th;
static Label *lab;
static Label *GetInstance(JSValueConst this_val)
{
    th = (COMP_REF *)JS_GetOpaque(this_val, NativeLabelClassID);
    lab = (Label *)th->comp;
    return lab;
}

/**
 * @brief 设置文字
 *
*/
static JSValue lvLabSetText(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    std::string text;
    text = JS_ToCString(ctx, argv[0]);
    printf("text: %s\n", text.c_str());
    Label *lab = GetInstance(this_val);
    lv_label_set_text(lab->instance, text.c_str());
    return JS_UNDEFINED;
}

/**
 * @brief 直接屏幕居中
 *
*/
static JSValue lvLabCenter(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv)
{
    Label *lab = GetInstance(this_val);
    lv_obj_center(lab->instance);
    return JS_UNDEFINED;
}


static const JSCFunctionListEntry ComponentProtoFuncs[] = {
    JS_CFUNC_DEF("setText", 1, lvLabSetText),
    JS_CFUNC_DEF("center", 0, lvLabCenter),
};

static const JSCFunctionListEntry ComponentClassFuncs[] = {
};

static JSValue NativeLabelConstructor(JSContext *ctx, JSValueConst new_target, int argc, JSValueConst *argv)
{
    JSValue proto;
    JSValue obj;
    JSValue arg;
    JSValue jsUid;
    lv_obj_t *parent;
    Button *btn;
    COMP_REF *th;
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

    if (JS_IsObject(argv[1])) {
        th = (COMP_REF *)JS_GetOpaque(argv[1], NativeButtonClassID);
        printf("Parent Button Uid: %s\n", th->uid);
        btn = static_cast<Button *>(th->comp);
        parent = btn->instance;
    }


    if (JS_IsUndefined(new_target)) {
        proto = JS_GetClassProto(ctx, NativeLabelClassID);
    } else {
        proto = JS_GetPropertyStr(ctx, new_target, "prototype");
        if (JS_IsException(proto))
            goto fail;
    }

    obj = JS_NewObjectProtoClass(ctx, proto, NativeLabelClassID);
    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    s = (COMP_REF*)js_mallocz(ctx, sizeof(*s));
    s->uid = uid;
    s->comp = new Label(uid, parent);

    JS_FreeCString(ctx, uid);

    if (!s)
        goto fail;

    JS_SetOpaque(obj, s);
    LV_LOG_USER("Label %s created", uid);
    return obj;
 fail:
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}

static void NativeLabelFinalizer(JSRuntime *rt, JSValue val) {
    COMP_REF *th = (COMP_REF *)JS_GetOpaque(val, NativeLabelClassID);
    LV_LOG_USER("NativeLabel %s release", th->uid);
    if (th) {
        delete static_cast<Label*>(th->comp);
        free(th);
    }
};

static JSClassDef NativeLabelClass = {
    "NativeLabel",
    .finalizer = NativeLabelFinalizer,
};

void NativeLabelInit(JSContext* ctx, JSValue ns)
{
    curCtx = ctx;
    JS_NewClassID(&NativeLabelClassID);
    JS_NewClass(JS_GetRuntime(ctx), NativeLabelClassID, &NativeLabelClass);
    JSValue proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
    /* 设置类的原型对象，将一个JS对象指定为该类的原型对象，从而定义该类的属性和方法 */
    JS_SetClassProto(ctx, NativeLabelClassID, proto);

    JSValue obj = JS_NewCFunction2(ctx, NativeLabelConstructor, "NativeLabel", 1, JS_CFUNC_constructor, 0);
    JS_SetConstructor(ctx, obj, proto);
    JS_SetPropertyFunctionList(ctx, obj, ComponentClassFuncs, countof(ComponentClassFuncs));
    /**
     * @brief 用于向JS对象中添加一个命名属性，并将该属性的值设置为指定的值
     * var bridge = globalThis.SJSJSBridge;
     * var NativeLabel = bridge.NativeRender.NativeComponents.NativeLabel;
     */
    JS_DefinePropertyValueStr(ctx, ns, "NativeLabel", obj, JS_PROP_C_W_E);
}
