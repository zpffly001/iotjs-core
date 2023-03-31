#ifndef DJS_H
#define DJS_H

#include "quickjs/quickjs.h"
#include "quickjs/quickjs-libc.h"
#include "quickjs/cutils.h"
#include "lvgl/src/core/lv_theme.h"

/* 初始化lvgl各种组件如：button chart */
void NativeAppInit (JSContext* ctx);

lv_theme_t *GetLvTheme();


#define DJS_UVCONST(x) JS_PROP_INT32_DEF(#x, UV_ ## x, JS_PROP_ENUMERABLE)
#define DJS_CONST(x) JS_PROP_INT32_DEF(#x, x, JS_PROP_ENUMERABLE)
#define DJS_CONST2(name, val) JS_PROP_INT32_DEF(name, val, JS_PROP_ENUMERABLE)
#define DJS_CFUNC_DEF(name, length, func1) { name, JS_PROP_C_W_E, JS_DEF_CFUNC, 0, .u = { .func = { length, JS_CFUNC_generic, { .generic = func1 } } } }
#define DJS_CFUNC_MAGIC_DEF(name, length, func1, magic) { name, JS_PROP_C_W_E, JS_DEF_CFUNC, magic, .u = { .func = { length, JS_CFUNC_generic_magic, { .generic_magic = func1 } } } }
#define DJS_CGETSET_DEF(name, fgetter, fsetter) { name, JS_PROP_C_W_E, JS_DEF_CGETSET, 0, .u = { .getset = { .get = { .getter = fgetter }, .set = { .setter = fsetter } } } }
#define DJS_OBJECT_DEF(name, val, len) JS_OBJECT_DEF(name, val, len, JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE)

#endif