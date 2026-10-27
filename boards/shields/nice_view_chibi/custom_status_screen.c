/* SPDX-License-Identifier: MIT */

#include <lvgl.h>
#include <zmk/display/status_screen.h>

LV_IMG_DECLARE(sleepy_chibi);

lv_obj_t *zmk_display_status_screen(void) {
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_remove_style_all(screen);
    lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    /*
     * nice!view exposes a native 160x68 framebuffer. The bitmap is already
     * rotated clockwise, matching the upstream shield's portrait orientation.
     * A static image avoids a canvas buffer, runtime rotation, and animation.
     */
    lv_obj_t *portrait = lv_img_create(screen);
    lv_img_set_src(portrait, &sleepy_chibi);
    lv_obj_set_pos(portrait, 0, 0);

    return screen;
}
