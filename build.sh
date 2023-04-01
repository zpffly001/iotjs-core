# 编译quickjs
cp modified/quickjs/* depends/quickjs/
cd depends/quickjs/
make
gcc -shared -fPIC -o libquickjs.so .obj/quickjs.o .obj/libregexp.o .obj/libunicode.o .obj/cutils.o .obj/quickjs-libc.o .obj/libbf.o
cp libquickjs.so ../../lib/dynamic
cp libquickjs.a ../../lib/static
cd ../../


# 编译lvgl
cp modified/lvgl/lv_conf_internal.h depends/lvgl/src
cd depends/lvgl/
git checkout release/v8.3
mkdir -p build && cd build && cmake ..
make
cp ./lib/liblvgl.a ../../../lib/static
cd ../../../


# 编译lv_drivers
cp modified/lv_drivers/* depends/lv_drivers/
cd depends/lv_drivers/
git checkout release/v8.2
mkdir -p build && cd build && cmake ..
make
cp ./lib/liblv_drivers.a ../../../lib/static
cd ../../../

cd ./src
g++ -fPIC -I./ -I../depends -o ../lib/obj/button.o -c ./native/components/button/button.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/button_native.o -c ./native/components/button/button_native.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/label.o -c ./native/components/label/label.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/label_native.o -c ./native/components/label/label_native.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/window.o -c ./native/components/window/window.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/component.o -c ./native/components/component.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/base.o -c ./native/core/basic/base.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/app.o -c ./native/app/app.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/simulator.o -c ./native/simulator/simulator.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/global.o -c ./global.cpp
g++ -fPIC -I./ -I../depends -o ../lib/obj/util.o -c ./util.c
g++ -fPIC -fpermissive  -I./ -I../depends -o ../lib/obj/main.o -c ./main.c
cd ..

# 编译dxjs
cd lib
g++ -std=c++11 -o ./dxjs ./obj/*.o ./static/liblvgl.a ./static/liblv_drivers.a ./static/libquickjs.a -lSDL2 -lm -ldl -lpthread
