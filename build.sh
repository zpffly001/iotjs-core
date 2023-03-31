# # 编译quickjs
# cp modified/quickjs/* depends/quickjs/
# cd depends/quickjs/
# make
# gcc -shared -fPIC -o libquickjs.so .obj/quickjs.o .obj/libregexp.o .obj/libunicode.o .obj/cutils.o .obj/quickjs-libc.o .obj/libbf.o
# cp libquickjs.so ../../lib/dynamic
# cp libquickjs.a ../../lib/static
# cd ../../


# # 编译lvgl
# cd depends/lvgl/
# git checkout release/v8.3
# mkdir -p build && cd build && cmake ..
# make
# cp ./lib/liblvgl.a ../../../lib/static
# cd ../../../


# 编译lv_drivers
cd depends/lv_drivers/
git checkout release/v8.2
mkdir -p build && cd build && cmake ..
make
cp ./lib/liblv_drivers.a ../../../lib/static
cd ../../../



