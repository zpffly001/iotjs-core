#pragma once

#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl.h"


void hal_init(void);

static void* buf;

static void (*flush_cb)(struct _lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

static lv_coord_t hor_res;
static lv_coord_t ver_res;

using read_cb = void (*)(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

static read_cb read_cb1;
static read_cb read_cb2;
static read_cb read_cb3;