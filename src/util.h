
#ifndef DJS_UTIL1_H
#define DJS_UTIL1_H

#include "djs.h"



void DJSDumpError(JSContext *ctx);

void DJSDumpErrorWithThisval(JSContext *ctx, JSValueConst exception_val);

#endif