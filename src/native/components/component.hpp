#pragma once

#include "native/core/common/common.hpp"
#include "native/core/basic/base.hpp"

typedef struct COMP_REF {
    void* comp;
    const char* uid;
} COMP_REF;

lv_obj_t* GetWindowInstance ();

void WindowInit ();

void NativeComponentInit (JSContext* ctx, JSValue ns);

void NativeButtonInit (JSContext* ctx, JSValue ns);

void NativeLabelInit (JSContext* ctx, JSValue ns);