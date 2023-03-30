# # quickjs
# cd quickjs && make

# # lv_binding_js
# cd lv_binding_js && git submodule update --init --recursive && npm install && npm audit fix && make dev-x86


# 编译lvgl


# 编译lv_drivers


# 编译quickjs
cp modified/quickjs/* depends/quickjs/
cd depends/quickjs/
make
gcc -shared -fPIC -o libquickjs.so .obj/quickjs.o .obj/libregexp.o .obj/libunicode.o .obj/cutils.o .obj/quickjs-libc.o .obj/libbf.o
cp libquickjs.so ../../lib/dynamic
cp libquickjs.a ../../lib/static
cd ../../



