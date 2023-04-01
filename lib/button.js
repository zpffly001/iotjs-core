var bridge = globalThis.SJSJSBridge;
var myNativeButton = bridge.NativeRender.NativeComponents.NativeButton;
var myNativeLabel = bridge.NativeRender.NativeComponents.NativeLabel;
var nButton1, nButton2, nlabel1, nlabel2
var count = 0;

/**
 * 点击事件
 */
function click1(button, length, width){
    console.log("length: ", length)
    console.log("width: ", width)
    count++;
    if(count % 2 == 0){
        button.setSize(length * 2, width * 2)
    }else{
        button.setSize(length, width)
    }
}

/***************************NativeButton1*******************************/
nButton1 = new myNativeButton({ uid:"11" });
// 设置Button坐标
nButton1.setPos(150, 150)
// 设置Button的大小
nButton1.setSize(200, 100)

// 添加标签
nlabel1 = new myNativeLabel({uid:"111"}, nButton1)
// 设置文字
nlabel1.setText("NativeButton1")
// 直接屏幕居中
nlabel1.center()

// 设置点击事件
nButton1.onClick(click1, 3, nButton1, 100, 50)

/***************************NativeButton2*******************************/
nButton2 = new myNativeButton({ uid:"22" });
nButton2.setPos(10, 10)
nButton2.setSize(200, 100)


nlabel2 = new myNativeLabel({uid:"222"}, nButton2)
nlabel2.setText("NativeButton2")
nlabel2.center()

nButton2.onClick(click1, 3, nButton2, 100, 50)




















// /* 给对象绑定属性 */
// static int button_init(JSContext* ctx, JSModuleDef* module)
// {
//     /* variable */
//     JSValue proto, obj;
//     /* 初始化类ID */
//     JS_NewClassID(&NativeButtonClassID);
//     /* 创建mqttClass类 */
//     JS_NewClass(JS_GetRuntime(ctx), NativeButtonClassID, &NativeButtonClass);
//     /* 创建类的原型对象 */
//     proto = JS_NewObject(ctx);
//     /* 给对象设置方法 */
//     JS_SetPropertyFunctionList(ctx, proto, ComponentProtoFuncs, countof(ComponentProtoFuncs));
//     /* 把原型类和当前mqttClass类进行绑定 */
//     JS_SetClassProto(ctx, NativeButtonClassID, proto);
//     /* 准备类名 */
//     obj = JS_NewCFunction2(ctx, NativeButtonConstructor, "NativeButton", 1, JS_CFUNC_constructor, 0);
//     JS_SetModuleExport(ctx, module, "NativeButton", obj);
//     return 0;
// }


// /* 模块导出 */
// JSModuleDef *js_init_module(JSContext *ctx, const char *module_name) {
//     JSModuleDef *m;
//     m = JS_NewCModule(ctx, module_name, button_init);
//     if (!m) return NULL;
//     JS_AddModuleExport(ctx, m, "NativeButton");
//     return m;
// }

// cd /home/zpf/software/lv_sim_vscode_sdl/main/src/render/native/components
// gcc -fPIC -I../../ -I../../../ -I../../../../../quickjs -I../../../../../lvgl -I../../../../../lvgl/src/core -o ./button/button_native.o -c button/button_native.cpp
// gcc -shared -o button/button_native.so button/button_native.o


