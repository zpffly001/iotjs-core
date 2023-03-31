g++ -fPIC -fpermissive -I../../ -I../../../ -I../../quickjs -I../../lvgl -I../../lv_drivers -I./render -I./ -I./render/native/bootstrap -I./render/native/components -I../../lvgl/src/core -o build/main.o -c main.c

gcc -fPIC -I../../ -I../../../ -I../../quickjs -I../../lvgl -I../../lv_drivers -I./render -I./ -I./render/native/bootstrap -I./render/native/components -I../../lvgl/src/core -o build/jsapi.o -c jsapi.c

gcc -fPIC -I../../ -I../../../ -I../../quickjs -I../../lvgl -I../../lv_drivers -I./render -I./ -I./render/native/bootstrap -I./render/native/components -I../../lvgl/src/core -o build/util.o -c util.c