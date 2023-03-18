# quickjs
cd quickjs && make

# lv_binding_js
cd lv_binding_js && git submodule update --init --recursive && npm install && npm audit fix && make dev-x86