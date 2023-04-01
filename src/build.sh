cd /home/zpf/software/iotjs-core/src

gcc -fPIC -I./ -I../depends -o ../lib/obj/button.o -c ./native/components/button/button.cpp
gcc -fPIC -I./ -I../depends -o ../lib/obj/button_native.o -c ./native/components/button/button_native.cpp

gcc -fPIC -I./ -I../depends -o ../lib/obj/label.o -c ./native/components/label/label.cpp
gcc -fPIC -I./ -I../depends -o ../lib/obj/label_native.o -c ./native/components/label/label_native.cpp

gcc -fPIC -I./ -I../depends -o ../lib/obj/window.o -c ./native/components/window/window.cpp

gcc -fPIC -I./ -I../depends -o ../lib/obj/component.o -c ./native/components/component.cpp

gcc -fPIC -I./ -I../depends -o ../lib/obj/base.o -c ./native/core/basic/base.cpp

gcc -fPIC -I./ -I../depends -o ../lib/obj/app.o -c ./native/app/app.cpp

gcc -fPIC -I./ -I../depends -o ../lib/obj/simulator.o -c ./native/simulator/simulator.cpp

gcc -fPIC -I./ -I../depends -o ../lib/obj/global.o -c ./global.c

gcc -fPIC -I./ -I../depends -o ../lib/obj/util.o -c ./util.c

g++ -fPIC -fpermissive  -I./ -I../depends -o ../lib/obj/main.o -c ./main.c



# G++ 命令编译
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
